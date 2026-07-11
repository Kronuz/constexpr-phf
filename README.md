# constexpr-phf (`phf`)

![constexpr](https://img.shields.io/badge/constexpr-compile--time-blue)
![standard](https://img.shields.io/badge/C%2B%2B-17-blue)
![license](https://img.shields.io/badge/license-MIT-green)

A header-only, fully `constexpr` **minimal perfect hash** for a fixed set of integer keys.
The whole lookup table is built at compile time (CHD-style, "compress, hash, displace",
based on Dr. Daoud's work), so at runtime a key resolves to a dense slot in `[0, N)` with a
couple of multiplies, a shift, and two array reads. No collisions, no heap, no dependencies
beyond the standard library.

## What it is

`phf.hh` builds a minimal perfect hash function over a known set of integer keys entirely at
compile time. The lookup table (a buckets array plus an index array) is materialized as
`constexpr` data, so the runtime artifact is plain arrays and the hot path has no branches
and no allocation. Everything lives in the `phf` namespace.

The classic use is a compile-time dispatch table: map a fixed set of tokens to a dense index
and drive a `switch`. Because the slots are dense `[0, N)`, the compiler builds that switch as
a jump table.

## Integer keys only (and where strings live)

`phf` hashes **integers**. To key on strings, hash them to integers first (FNV-1a, xxHash, or
similar) and build a `phf` over the results. That string front-end (a pluggable hasher, a
switch-friendly `set`/`map`, optional verification against misdispatch, and a cross-implementation
benchmark vs gperf/frozen/`unordered_map`) is its own library, **[`keywords`](https://github.com/Kronuz/keywords)**,
which uses this one as its engine. Keeping the engine hash-agnostic is deliberate: it works for
any integer keys, not just string hashes.

## The lookup: division-free multiply-shift, with an automatic robust fallback

The runtime cost is one masked bucket read and one displaced index read:

```cpp
const auto& bucket = _buckets[item & (buckets_size - 1)];
const auto& elem   = _index[(((_premix ? mixk(item) : item) * bucket.mul) >> shift) + bucket.off];
```

The index reduction is a **multiply-shift** (`(item * mul) >> shift`) into a power-of-two table,
not a division by a prime. Dropping the modulo is measurably faster, especially on x86 where
integer division is expensive.

Pure multiply-shift has one failure mode: adversarial keys like distinct powers of two, where
`item * mul` is just a shift and entropy never reaches the top bits. So the build is **adaptive**.
It tries the fast path first (no pre-mix); only if the multiplier search cannot place the keys does
it fall back to a robust path that runs each key through a cheap non-linear pre-mix (`mixk`,
one xorshift-multiply). The choice is recorded per instance in `premixed()`, and the lookup mirrors
it. Every real-world key set takes the fast path; only the pathological ones pay for robustness,
and they pay it at compile time.

## Benchmarks

Three benchmarks live under `bench/`, built when this repo is the top-level CMake project.
Numbers below are x86_64, GCC 11, `-O3`.

**Integer core** (`bench/bench.cc`): `find()` in isolation. Every real key set takes the
division-free fast path; the one adversarial set (distinct powers of two) falls back and
stays correct. The cost is flat, the same ~1.2 ns whether the set has six keys or a thousand:

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

**String dispatch** (`bench/dispatch_field_types.cc`, `bench/dispatch_stop_words.cc`): `phf` is
integer-only, so you dispatch on strings by hashing them first (your choice of hash) and
verifying the hit. Against gperf, frozen, a compile-time trie, and std containers, on Xapiand's
192 field-type names (mixed length), ns/op:

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
464K-word text) constexpr-phf edges ahead of gperf too. The hash is the caller's to pick: a
word-at-a-time hash suits longer keys (21 ns verified here vs 25 for byte-at-a-time FNV-1a);
FNV-1a is as cheap on short ones.

## Install

Header-only. Drop `phf.hh` on your include path, or pull it with CMake FetchContent.
It is a single header at the repo root, so a consumer sees just `phf.hh`:

```cmake
include(FetchContent)
FetchContent_Declare(constexpr_phf
  GIT_REPOSITORY https://github.com/Kronuz/constexpr-phf.git
  GIT_TAG master
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(constexpr_phf)

target_link_libraries(your_target PRIVATE constexpr_phf)
```

## Usage

```cpp
#include "phf.hh"

// Build at compile time over a fixed set of integer keys.
static constexpr auto ids = phf::make_phf({101u, 202u, 303u, 404u});

// Dense, collision-free index into a parallel table.
const char* names[] = {"", "", "", ""};
names[ids.at(202u)] = "second";

// Membership without throwing.
if (ids.count(999u)) { /* not reached: 999 is absent */ }

// Compile-time-constant slots make a jump-table switch:
switch (ids.find(x)) {
    case decltype(ids)::npos: /* absent */ break;
    // case ids.find(101u): ...  (constexpr slot)
}
```

API surface: `find` (slot or `npos`), `count` (0/1), `at` / `operator[]` (slot or throw),
`lookup` (raw slot, no membership check), `size`, `empty`, and `premixed` (which build path was
chosen). `make_phf` builds from an array or brace list; `assign` also takes an
`initializer_list`, an iterator pair, or a pointer plus size.

## When not to use it

Not a general-purpose dynamic map: the key set is fixed at build time (no insert/erase/rehash),
and it hashes integers only. Very large key sets increase compile time. For arbitrary,
non-membership-verified input in a `switch`, use `find` (verified) rather than `lookup`.

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
