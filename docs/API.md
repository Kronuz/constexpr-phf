# constexpr-phf API reference

All members are `constexpr` and live on `phf::phf<ItemType, NumItems>`; build one with the
`make_phf` factory.

| Member | Returns |
| :-- | :-- |
| `phf::make_phf(keys)` | Deduces `ItemType`/`NumItems` from an array or brace-list and builds the hash. The usual entry point. |
| `find(item)` | Dense slot in `[0, N)`, or `phf::npos` if absent. Non-throwing. The hot path. |
| `count(item)` | `1` if `item` is a key, `0` otherwise. |
| `at(item)` / `operator[](../item)` | Dense slot, or throws `std::out_of_range` if absent. |
| `lookup(item)` | Raw slot with **no** membership check (returns whatever sits there for a non-key). Use only after verifying membership. |
| `size()` | Number of keys. |
| `empty()` | `true` if it holds no keys. |
| `capacity()` | Width of the internal index table (`index_size`), always `>= size()`. |
| `premixed()` | Which build path placed the keys: `false` = fast division-free path, `true` = robust pre-mixed fallback. |

`make_phf` and the constructors / `assign` also take an `initializer_list`, an iterator pair, or
a pointer plus size. `ItemType` must be integral, and `index_size` must fit in `ItemType`
(a `static_assert` enforces it). Duplicate keys throw `std::invalid_argument`; so does the rare
case where no multiplier places a key set collision-free. `<iostream>` is pulled in only under
`#define PHF_DEBUG`; the default build has no I/O dependency.

## Integer keys only (and where strings live)

`phf` hashes **integers**. To key on strings, hash them to integers first (FNV-1a, xxHash, a
word-at-a-time hash, whatever fits your keys) and build a `phf` over the results, verifying the
hit if the input is open. Keeping the engine hash-agnostic is deliberate: it works for any
integer keys, not just string hashes, and it lets you pick the hash that suits your data
(see the string-dispatch benchmark, where a word-at-a-time hash wins on long keys and FNV-1a on
short ones).

## When not to use it

Not a general-purpose dynamic map: the key set is fixed at build time (no insert / erase /
rehash), and it hashes integers only. Very large key sets increase compile time and
template-instantiation cost, since the table is *searched* at compile time. For arbitrary,
possibly-non-member input in a `switch`, verify the hit (or use `find` and check the slot's key)
rather than trusting `lookup`.
