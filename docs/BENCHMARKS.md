# constexpr-phf benchmarks

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
