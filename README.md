# constexpr-phf (`phf`)

![constexpr](https://img.shields.io/badge/constexpr-compile--time-blue)
![standard](https://img.shields.io/badge/C%2B%2B-17-blue)
![license](https://img.shields.io/badge/license-MIT-green)

A header-only, fully `constexpr` **minimal perfect hash** for a fixed set of integer keys.
The whole lookup table is built at compile time (a two-level CHD-style scheme, "compress,
hash, displace"), so at runtime a key resolves to a dense slot in `[0, N)` with a couple of
multiplies, a shift, and two array reads. No collisions, ever. No heap, no branch on the hot
path, no dependency beyond the standard library.

"Perfect" means no two keys collide, by construction. "Minimal" means the keys map onto a
dense `[0, N)` with no gaps, so the table is exactly as big as the key set. And because the
search that *finds* such a hash is `constexpr`, it runs during compilation and leaves behind
only the finished arrays.

## Why not a switch, or an if-ladder?

Say you are dispatching on a fixed set of tokens you know at build time. The idiomatic answers
are an `if`/`else if` ladder, or, once the token is hashed to an integer, a `switch` on that
hash. Both come apart as the set grows. An `if`-ladder is a linear scan. A `switch` on sparse
hash values cannot be a jump table (the labels are not dense), so the compiler turns it into an
`O(log n)` binary search of comparisons. A `std::unordered_map` trades the branches for a hash,
a probe, a pointer chase, and a likely cache miss.

A perfect hash maps the keys onto a dense `[0, N)`, so the dispatch becomes one array index (or
a real jump table). It is **flat and low**: the same handful of instructions at a thousand keys
as at six, worst case identical to best case. See [Benchmarks](#benchmarks) for the numbers
(at N=1000, ~1.2 ns vs an `if`-ladder's 162 ns and a `switch`'s 40 ns).

## What it is

`phf.hh` builds a minimal perfect hash function over a known set of integer keys entirely at
compile time. The lookup table (a buckets array plus an index array) is materialized as
`constexpr` data, so the runtime artifact is plain arrays and the hot path has no branches and
no allocation. Everything lives in the `phf` namespace.

The classic use is a **compile-time dispatch table**: map a fixed set of tokens to a dense index
and drive a `switch`. Because the slots are dense `[0, N)` and every `find()` of a key is a
compile-time constant, the compiler builds that switch as a jump table.

## Usage

```cpp
#include "phf.hh"

// Build the perfect hash over a fixed set of integer keys, at compile time.
static constexpr auto ids = phf::make_phf({101u, 202u, 303u, 404u});

static_assert(ids.size() == 4);
static_assert(!ids.empty());
```

**Membership and indexing.** Each key gets a unique, dense slot in `[0, N)`:

```cpp
ids.count(202u);   // 1  (present)
ids.count(999u);   // 0  (absent)
ids.find(202u);    // dense slot in [0, N); phf::npos if absent (non-throwing)
ids.at(202u);      // same slot, but throws std::out_of_range if absent
ids[202u];         // same as at()
```

**A parallel table.** The dense slot is an index into anything you keep alongside the keys:

```cpp
static constexpr unsigned keys[]  = {2, 3, 5, 7, 11, 13, 17, 19};
static constexpr const char* name[] = {"two","three","five","seven","eleven","thirteen","seventeen","nineteen"};
static constexpr auto primes = phf::make_phf(keys);

const char* name_of(unsigned k) {
    return primes.count(k) ? name[primes.find(k)] : "unknown";
}
```

**A string switch.** `phf` is integer-only, so hash the strings first and dispatch on the
slot. Every `ops.find(hash("..."))` is a compile-time constant, so these are real `case`
labels and the whole thing compiles to a dense jump table:

```cpp
// hash() is any constexpr string hash (FNV-1a, xxHash, a word-at-a-time hash, your pick).
static constexpr auto ops = phf::make_phf({hash("add"), hash("remove"), hash("replace"), hash("move")});

switch (ops.find(hash(op))) {
    case ops.find(hash("add")):     return do_add();
    case ops.find(hash("remove")):  return do_remove();
    case ops.find(hash("replace")): return do_replace();
    case ops.find(hash("move")):    return do_move();
    default:                        return unknown(op);   // not one of the keys
}
```

One honesty note: a perfect hash removes collisions *among the keys you gave it*, but it cannot
tell a stranger from a member. `find()` on a non-member reads some slot and hands back whatever
sits there. When the input might not be a member, verify: keep the original strings and compare
against the one at the slot, or guard the shape first. For a genuinely closed set (the input is
always one of the keys) you skip even that. `bench/dispatch_field_types.cc` shows the whole
verified pattern, benchmarked against gperf, frozen, a compile-time trie, and the std containers.

## Integer keys only (and where strings live)

`phf` hashes **integers**. To key on strings, hash them to integers first (FNV-1a, xxHash, a
word-at-a-time hash, whatever fits your keys) and build a `phf` over the results, verifying the
hit if the input is open. Keeping the engine hash-agnostic is deliberate: it works for any
integer keys, not just string hashes, and it lets you pick the hash that suits your data
(see the string-dispatch benchmark, where a word-at-a-time hash wins on long keys and FNV-1a on
short ones).

## The lookup: division-free multiply-shift, with an adaptive robust fallback

The two-level construction is CHD-style, in the lineage of [Daoud and Fox's minimal perfect
hashing](https://stevehanov.ca/blog/throw-away-the-keys-easy-minimal-perfect-hashing): a first
hash picks a bucket, and a small per-bucket displacement then places every key in a free slot
without collision. The *lookup*, though, has drifted well off that textbook path. The classic
scheme reduces the displaced hash into the table with a **modulo by a prime**; this one uses a
division-free **multiply-shift** into a power-of-two table:

```cpp
// in essence:
slot = ((item * bucket.mul) >> shift) + bucket.off;   // power-of-two table, no division
```

Dropping the modulo is measurably faster than the prime-modulo it replaced, especially on x86
where integer division is expensive. Pure multiply-shift has one failure mode: adversarial keys
like distinct powers of two, where `item * mul` is just a shift and entropy never reaches the
top bits. So the build is **adaptive**. It tries the fast path first (no pre-mix); only if the
multiplier search cannot place the keys does it fall back to a robust path that runs each key
through a cheap non-linear pre-mix (`mixk`, one xorshift-multiply). The choice is recorded per
instance in `premixed()`, and the lookup mirrors it. Every real-world key set takes the fast
path; only the pathological ones pay for robustness, and they pay it at compile time.

## Benchmarks

Three benchmarks live under `bench/`, built when this repo is the top-level CMake project.
Numbers below are x86_64, GCC 11, `-O3`.

**Integer core** (`bench/bench.cc`): `find()` in isolation. Every real key set takes the
division-free fast path; the one adversarial set (distinct powers of two) falls back and stays
correct. The cost is flat, the same ~1.2 ns whether the set has six keys or a thousand:

```
  N=6      1.28 ns/lookup   (fast)
  N=46     1.25 ns/lookup   (fast)
  N=192    1.18 ns/lookup   (fast)
  N=1000   1.33 ns/lookup   (fast)
  powers of two, N=32       correct (robust fallback)
```

**Versus the alternatives** (`bench/compare.cc`): the same lookup against what you would
otherwise reach for on a fixed set of sparse (hashed) integer keys, ns/lookup:

| keys | `if`-ladder | `switch` (binary search) | `unordered_map` | `phf` |
| ---: | ---: | ---: | ---: | ---: |
| 6 | 2.4 | 4.0 | 3.2 | 1.2 |
| 46 | 14 | 8.2 | 3.1 | 1.2 |
| 192 | 38 | 26 | 3.1 | 1.2 |
| 1000 | 162 | 40 | 3.2 | 1.3 |

The `if`-ladder is linear, a `switch` on sparse keys compiles to an `O(log n)` binary search,
and `unordered_map` never drops below its hash-plus-probe floor. Only `phf` is flat and low.

**String dispatch** (`bench/dispatch_field_types.cc`, `bench/dispatch_stop_words.cc`): the
engine used for strings (hash + verify) against gperf, frozen, a compile-time trie, and std
containers, on Xapiand's 192 field-type names (mixed length), ns/op:

| dispatch | ns/op |
| :-- | ---: |
| `gperf` (external codegen) | 14 |
| **constexpr-phf**, hash-only (unverified) | 18 |
| **constexpr-phf**, hash + verify | 21 |
| compile-time trie | 28 |
| `std::unordered_map` | 29 |
| `frozen::unordered_set` | 40 |
| `std::set` | 82 |

Hash-only is the fast path (hash, index, done, no compare, which can misdispatch a stranger, so
you feed it only members or guard first); verified adds one compare at the slot and never
false-matches. It beats every container, `frozen`, and the trie, and trails only gperf, which
needs a separate codegen step. On an all-short key set (570 English stop words filtered over a
464K-word text) constexpr-phf edges ahead of gperf too. The hash is the caller's to pick.

## API reference

All members are `constexpr` and live on `phf::phf<ItemType, NumItems>`; build one with the
`make_phf` factory.

| Member | Returns |
| :-- | :-- |
| `phf::make_phf(keys)` | Deduces `ItemType`/`NumItems` from an array or brace-list and builds the hash. The usual entry point. |
| `find(item)` | Dense slot in `[0, N)`, or `phf::npos` if absent. Non-throwing. The hot path. |
| `count(item)` | `1` if `item` is a key, `0` otherwise. |
| `at(item)` / `operator[](item)` | Dense slot, or throws `std::out_of_range` if absent. |
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

## When not to use it

Not a general-purpose dynamic map: the key set is fixed at build time (no insert / erase /
rehash), and it hashes integers only. Very large key sets increase compile time and
template-instantiation cost, since the table is *searched* at compile time. For arbitrary,
possibly-non-member input in a `switch`, verify the hit (or use `find` and check the slot's key)
rather than trusting `lookup`.

## Install

Header-only. Drop `phf.hh` on your include path, or pull it with CMake FetchContent. It is a
single header at the repo root, so a consumer sees just `phf.hh`:

```cmake
include(FetchContent)
FetchContent_Declare(constexpr_phf
  GIT_REPOSITORY https://github.com/Kronuz/constexpr-phf.git
  GIT_TAG master
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(constexpr_phf)

target_link_libraries(your_target PRIVATE constexpr_phf)
```

Requires C++17.

## Build the tests, demo, and benchmarks

```sh
cmake -B build && cmake --build build && ctest --test-dir build
./build/phf_demo                    # a runnable tour
./build/phf_bench                   # integer-core micro-benchmark
./build/phf_compare                 # phf vs if-ladder / switch / unordered_map
./build/phf_dispatch_field_types    # string dispatch vs gperf / frozen / trie / std
gzip -dc bench/monte-cristo.txt.gz | ./build/phf_dispatch_stop_words
```

The dispatch benchmarks fetch `ctrie` and `frozen` as contenders; the gperf tables are
pre-generated and committed under `bench/`.

See `ARCHITECTURE.md` for the internal design and `AGENTS.md` for contributor notes.

## License

MIT. Copyright (C) 2018-2019 German Mendez Bravo (Kronuz).
