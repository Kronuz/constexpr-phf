# constexpr-phf benchmarks

Four benchmarks live under `bench/` and build when this repository is the top-level CMake
project. The numbers below are from an Apple M4 Pro (arm64, macOS 26.7.2) with Apple clang
17.0.0 and `-O3 -DNDEBUG`, at commit `dd7a9ff`, and each is the best of three runs. The
comparators' versions: libc++ as shipped with Apple clang 17.0.0 for the standard containers,
[gperf](https://www.gnu.org/software/gperf/) 3.0.3 and 3.1 for the committed tables,
[frozen](https://github.com/serge-sans-paille/frozen) at `d53e0a1` and
[ctrie](https://github.com/Kronuz/ctrie) at `bbce6d6`.

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/phf_bench
./build/phf_compare
./build/phf_dispatch_field_types
gzcat bench/monte-cristo.txt.gz | ./build/phf_dispatch_stop_words
```

## Integer core

`phf_bench` times `find()` alone over 4,096 member keys drawn at random from a set of random
32-bit keys, in nanoseconds per lookup (best of seven rounds of 2,048,000 lookups). *Path* is
the build path the table took: *fast* is the plain multiply-shift, *pre-mixed* the fallback.

| Keys | Path | ns per lookup |
| ---: | :-- | ---: |
| 6 | fast | 0.58 |
| 46 | fast | 0.54 |
| 192 | fast | 0.49 |
| 1,000 | fast | 0.54 |

A set of 32 distinct powers of two defeats the fast path; the table takes the pre-mixed path
and places every key in its own slot.

## Versus the alternatives

`phf_compare` looks up member keys drawn at random from fixed sets of sparse 32-bit keys, in
nanoseconds per lookup (best of nine rounds of 1,228,800 lookups). The *`if` ladder* compares
the key with each member in turn, *binary search* is `std::lower_bound` over the sorted keys
(what a `switch` on sparse keys compiles into), *`std::unordered_map`* maps each key to its
index, and *`phf`* is `find()`. All four return each key's index in the sorted key list, and a
separate check over the same lookups found no disagreement.

| Keys | `if` ladder | binary search | `std::unordered_map` | `phf` |
| ---: | ---: | ---: | ---: | ---: |
| 6 | 1.39 | 1.50 | 1.00 | 0.53 |
| 46 | 6.64 | 3.93 | 1.61 | 0.53 |
| 192 | 32.9 | 7.39 | 1.69 | 0.48 |
| 1,000 | 138 | 8.65 | 1.38 | 0.53 |

The `if` ladder grows with the set, the binary search with its logarithm, and
`std::unordered_map` stays near its hash-and-probe floor; `phf` stays flat and lowest.

## String dispatch

The library hashes integers, so string dispatch puts a hash in front. Two hashes from
`bench/phf_dispatch.hh` appear: *fnv1a* (64-bit FNV-1a, a byte at a time) and *wordwise* (eight
bytes per step). *Verified* compares the string at the slot after `find()`, so a non-member
never matches; *hash-only* skips that compare, so a non-member whose hash equals a member's
would match. *`switch` on the hash* is a `switch` over the FNV-1a hash with one `case` per
member, which the compiler turns into a binary search. The other rows are the named library or
container holding the same strings.

**Field types** (`phf_dispatch_field_types`): Xapiand's 192 field-type names (2 to 23 bytes,
median 14) and 200,000 lookups, half of them a name with a `!` appended, so they miss; best of
15 passes, nanoseconds per lookup. Every contender finds the same 99,543 members.

| Contender | ns per lookup |
| :-- | ---: |
| `phf`, hash-only (wordwise) | 8.99 |
| gperf 3.0.3 | 10.9 |
| `phf`, verified (wordwise) | 14.1 |
| `phf`, verified (fnv1a) | 17.0 |
| `std::unordered_map` | 19.7 |
| ctrie | 19.8 |
| `std::unordered_set` | 20.0 |
| frozen `unordered_set` | 28.2 |
| `switch` on the hash (unverified) | 30.8 |
| `std::set` | 56.5 |

**Stop words** (`phf_dispatch_stop_words`): 570 English stop words filtered out of the 464,220
words of *The Count of Monte Cristo* (`bench/monte-cristo.txt.gz`), milliseconds per pass, best
of 15 passes. Every contender counts the same 237,767 stop words.

| Contender | ms per pass |
| :-- | ---: |
| `phf`, hash-only (fnv1a) | 3.40 |
| `phf`, verified (fnv1a) | 4.53 |
| `switch` on the verified `phf` slot | 4.54 |
| gperf 3.1 | 4.57 |
| `phf`, verified (wordwise) | 5.26 |
| frozen `unordered_set` | 5.94 |
| `std::unordered_set` | 7.07 |
| `std::unordered_map` | 7.23 |
| ctrie | 7.60 |
| `switch` on the hash (unverified) | 9.26 |
| `std::set` | 32.6 |

On the mixed-length names, verified `phf` beats every container, frozen and the trie and trails
only gperf, which needs a code generator; on the short stop words it matches gperf. Which hash
wins depends on the keys: wordwise on the longer names, FNV-1a on the short words.
