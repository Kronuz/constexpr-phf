# Architecture

Internal design of `phf.hh`. This is a CHD-style ("compress, hash, displace") minimal
perfect hash for a fixed set of integer keys, built entirely at compile time.

## Data layout

A built `phf<ItemType, NumItems>` holds:

- `std::size_t _size` — the number of keys actually assigned.
- `bool _premix` — which build path placed the keys: `false` = the fast division-free
  multiply-shift, `true` = the robust pre-mixed path. The lookup reads this to stay in sync
  with how the table was built. Exposed read-only through `premixed()`.
- `bucket_type _buckets[buckets_size]` — the displacement table. Each `bucket_type` is two
  `uint32_t` fields, `mul` and `off`.
- `index_type _index[index_size + 1]` — the slot table. Each `index_type` holds the original
  `item` and its `pos` (its index in the input array), with `pos` defaulting to `npos`.

Sizes derived at compile time from `NumItems`:

- `buckets_size = 1 << log2(NumItems + 1)` — a power of two, so bucket selection is a bitmask.
  `log2` here counts bits, so `log2(9) = 4` and a set of 8 keys gets 16 buckets.
- `index_bits = log2(NumItems + NumItems / 4)`, `index_size = 1 << index_bits` — the smallest
  power of two giving roughly 25 percent headroom over `NumItems`.
- `item_bits = sizeof(ItemType) * 8`, `shift = item_bits - index_bits` — the high-bits shift
  used by the multiply-shift reduction.

`_index` has `index_size + 1` slots; slot 0 is never used as a result (every offset the builder
writes starts at 1). This keeps `pos == npos` distinguishable from a real slot and lets a
singleton bucket store an explicit 1-based offset.

`static_assert`s enforce: at least one element, `index_size` fits in `ItemType`,
`index_size >= NumItems`, a non-empty bucket table, and an integral `ItemType`.

## The lookup formula

`_lookup` is the whole runtime cost:

```cpp
const auto& bucket = _buckets[item & (buckets_size - 1)];
const auto& elem   = _index[(((_premix ? mixk(item) : item) * bucket.mul) >> shift) + bucket.off];
```

`item & (buckets_size - 1)` selects a bucket (a mask, since `buckets_size` is a power of two).
The bucket carries a multiplier `mul` and an offset `off`. The index slot is
`((k * mul) >> shift) + off`, where `k` is the key (fast path) or `mixk(key)` (robust path):

- **Multi-key buckets:** the builder found a `mul` such that every key in the bucket lands in a
  distinct free slot, and `off` is 1. The multiply-and-shift spreads the colliding keys apart.
- **Singleton buckets:** `mul` is 0, so `(k * 0) >> shift == 0`, and `off` is the explicit slot
  the builder assigned. The key is placed directly.

This is a **multiply-shift** hash: multiply by a constant, keep the top `index_bits` bits by
shifting right. It replaces the classic `(item * mul) % prime` (a division). Dropping the modulo
is the speedup, and it is largest on x86, where integer division is many cycles.

The public accessors are thin wrappers over `_lookup`, sharing the one formula:

- `count` returns `elem.item == item` (0 or 1).
- `find` returns `elem.pos` if the slot's item matches, else `npos`.
- `at` / `operator[]` return `elem.pos` on match and throw `std::out_of_range` otherwise.
- `lookup` returns `elem.pos` with no membership check.

The membership check matters: `_lookup` always reads some slot, so for a non-key you get whatever
sits there. The `elem.item == item` comparison is what makes a non-key report absent. `lookup`
omits it deliberately; only `count`, `find`, and `at` are safe for unverified input.

## The pre-mix (`mixk`) and why the robust path exists

Multiply-shift has a blind spot: for keys that are distinct powers of two, `item * mul` is a
pure left shift, so a small multiplier never pushes entropy into the top `index_bits` window and
every key collides. Multiplication alone cannot fix this (composing multiplies stays a shift),
so the robust path first runs each key through a cheap **non-linear** mix, one xorshift-multiply:

```cpp
// 32-bit keys:
h ^= h >> 15; h *= 0x2c1b3c6dU;      h ^= h >> 12;
// 64-bit keys:
h ^= h >> 30; h *= 0xbf58476d1ce4e5b9ULL; h ^= h >> 27;
```

The xorshift breaks the shift structure; the subsequent multiply by `bucket.mul` spreads the
result. `mixk` is applied identically at build and at lookup, so the table stays consistent.

## The adaptive build

Construction runs in `assign(const ItemType*, std::size_t)`, which is `constexpr`, so for a
`constexpr` instance the whole thing executes during compilation. It is a thin wrapper around the
real builder, `_build`:

```
assign(items, size):
    reject empty / oversized              (throws)
    _premix = false
    if !_build(items, size):              # fast path
        _premix = true
        if !_build(items, size):          # robust fallback (pre-mixed)
            throw "cannot find suitable table"
```

`_build` returns `false` (instead of throwing) when the displacement search exhausts its
multiplier table, so `assign` can retry with the pre-mix. Duplicate-key and input-size errors
still throw immediately; they are not retryable.

`_build` itself is the CHD algorithm:

1. **Mapping.** For each key, compute its bucket (`item & (buckets_size - 1)`), fill a mapping
   record, and count keys per bucket.
2. **Sort.** A `constexpr` quicksort orders the mappings so the biggest buckets come first. The
   crowded buckets are the hardest to place, so place them while the index table is still empty
   (the standard CHD heuristic).
3. **Displacement search.** Walk the sorted mappings, grouping entries that share a bucket. For
   each multi-key group, try `mul = 1`, then successive primes from the table, placing every item
   at `((k * mul) >> shift) + 1` (with `k = _premix ? mixk(item) : item`). If a target slot is
   taken, roll back every slot this attempt wrote and try the next multiplier. If the multiplier
   table is exhausted, return `false`. Rollback is why a partially-placed group never corrupts the
   table.
4. **Completion.** The remaining mappings are singletons. Scan for the next free slot, drop each
   singleton there, and record `mul = 0, off = slot`. This fills the leftover holes densely, which
   is what makes the hash minimal. Return `true`.

## Complexity

- **Build**, per group: up to `P` multiplier trials (the prime table size), each touching every
  item in the group, so `O(P * NumItems)` worst case; in practice most groups place on an early
  multiplier. The sort is `O(NumItems log NumItems)`. Adversarial key sets run `_build` twice (fast
  then robust). All of it is compile time.
- **Lookup:** `O(1)`. One mask, one (optional) pre-mix, one multiply, one shift, one add, two array
  reads, one comparison. The `_premix` branch is a per-instance constant, so it predicts perfectly.
- **Space:** `buckets_size` bucket records plus `index_size + 1` index records, both linear in
  `NumItems` (`index_size` about `1.25 * NumItems` rounded up to a power of two).

## Design decisions and trade-offs

- **Power-of-two index table + multiply-shift** instead of a prime modulus. `(item * mul) >> shift`
  is a multiply and a shift; `(item * mul) % prime` is a multiply and a division. The shift is
  cheaper on every target and much cheaper on x86. The cost is the powers-of-two blind spot, which
  the adaptive pre-mix covers.
- **Adaptive fast/robust** rather than always pre-mixing. The pre-mix eats roughly half the naive
  multiply-shift speedup, and almost no real key set needs it, so making it the common case would
  give up most of the win. Trying the fast path first keeps the full speedup for the common case and
  only spends the pre-mix (and a second `_build`) on key sets that actually collide.
- **25 percent index headroom** (`NumItems + NumItems / 4`) trades a little memory for a much higher
  chance the displacement search succeeds. Tighter packing would make some key sets unplaceable.
- **Biggest buckets first** is the standard CHD trick: place crowded buckets while slots are
  plentiful so the multiplier search stays short.
- **Everything `constexpr`, no allocation.** The cost moves to compile time; the runtime artifact is
  plain arrays. The price is that key sets are fixed at compile time and large sets inflate
  compilation.

## Known limitations

- Integer keys only (`static_assert` on `std::is_integral`). Strings must be pre-hashed to
  integers (see the `keywords` library for a string front-end).
- The key set is fixed at build time. No insert, erase, or rehash.
- `index_size` must fit in `ItemType`, which caps how many keys a narrow `ItemType` can hold.
- If even the robust (pre-mixed) build cannot place a group, `assign` throws "cannot find suitable
  table". This is far rarer than with the prime lookup alone, but the multiplier table is still
  finite.
- `lookup()` skips the membership check and can return a stale position for a non-key. Only `count`,
  `find`, and `at` are safe for unverified inputs.

## Possible improvements

- Compress the bucket table. `mul` and `off` are both `uint32_t`; many sets need only a byte or two.
- Expose the multiplier-table bound, or allow a custom multiplier sequence, so harder key sets can
  keep searching.
- A build-time diagnostic reporting the chosen `buckets_size`, `index_size`, load factor, and
  whether the robust path was used, without enabling the full `PHF_DEBUG` tracing.
