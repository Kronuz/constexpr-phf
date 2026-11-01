# constexpr-phf

Part of [Kronuz C++ Libraries](https://github.com/Kronuz/cpp-libraries), a collection of small, reusable C++ libraries.

[![CI](https://github.com/Kronuz/constexpr-phf/actions/workflows/ci.yml/badge.svg)](https://github.com/Kronuz/constexpr-phf/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Header-only](https://img.shields.io/badge/header--only-yes-green.svg)

Header-only compile-time minimal perfect hash for C++17: fixed integer keys map to dense slots in two array reads.
`phf::make_phf` searches for a collision-free table during constant evaluation: a bucket picked
by the key's low bits holds a multiplier and an offset, and `((key * mul) >> shift) + off` is
the key's slot. Nothing is built at run time, and `find()` of a known key is a constant that
works as a `case` label. Reach for it for keyword tables, protocol opcodes and any `switch` on
hashed strings.

## ✨ Highlights

- **Flat lookups.** `find()` costs about the same whether the set has 6 keys or 1,000:
  0.48 to 0.53 ns per lookup on an Apple M4 Pro and 0.92 to 1.17 on an Intel Core i9-9980HK
  (see [Performance](#-performance)).
- **Built by the compiler.** The search for a collision-free table runs in `constexpr` and
  leaves two small arrays behind: no heap, no I/O, no static initialization.
- **Real jump tables.** `find()` of a known key is a compile-time constant, so it works as a
  `case` label.
- **No division.** A lookup multiplies and shifts into a power-of-two table. A key set that
  defeats the multiplier search, such as distinct powers of two, takes a pre-mixed path chosen
  when the table is built.
- **String dispatch.** With a string hash in front and one compare to verify the hit, it beats
  `std::unordered_map`, `frozen` and a compile-time trie on 192 mixed-length keywords, and
  trails only gperf, which needs a code generator ([docs/BENCHMARKS.md](docs/BENCHMARKS.md)).

## 🚀 Quick start

A string `switch` that compiles to a jump table. `fnv1a` stands for any `constexpr` string
hash:

```cpp
#include "phf.hh"

#include <cstdint>
#include <cstdio>
#include <string_view>

constexpr std::uint32_t fnv1a(std::string_view s) {  // any constexpr string hash works
	std::uint32_t h = 2166136261u;
	for (char c : s) { h = (h ^ static_cast<unsigned char>(c)) * 16777619u; }
	return h;
}

constexpr auto ops = phf::make_phf({fnv1a("add"), fnv1a("remove"), fnv1a("move")});

const char* dispatch(std::string_view op) {
	switch (ops.find(fnv1a(op))) {  // a jump table: every case label is a constant
		case ops.find(fnv1a("add")):    return "adding";
		case ops.find(fnv1a("remove")): return "removing";
		case ops.find(fnv1a("move")):   return "moving";
		default:                        return "unknown";
	}
}

int main() {
	std::printf("%s %s %s\n", dispatch("move"), dispatch("add"), dispatch("copy"));
	// moving adding unknown
}
```

`find()` returns the key's index in the list given to `make_phf`, or `phf::npos` for a
non-key; `at()` throws instead. A perfect hash separates only the keys it was built from, and
two strings with the same hash look alike to it, so for open input compare the string at the
slot. [`examples/demo.cc`](examples/demo.cc) shows a parallel table and that check.

## 📦 Installation

Requires a C++17 compiler and CMake 3.14 or newer; no other dependencies. CI builds and tests
it on Linux (x86_64 with GCC and Clang, arm64), macOS (arm64, x86_64) and FreeBSD, plus
ASan + UBSan and TSan builds.

```cmake
include(FetchContent)
FetchContent_Declare(constexpr_phf
  GIT_REPOSITORY https://github.com/Kronuz/constexpr-phf.git
  GIT_TAG        183081ea89f030f214348374c2cc3e5efb741933)  # or master, to track the tip
FetchContent_MakeAvailable(constexpr_phf)

target_link_libraries(my_app PRIVATE constexpr_phf::constexpr_phf)
```

```cpp
#include "phf.hh"
```

The target is header-only, so copying `phf.hh` onto the include path works too.

## 🎯 When to use it

A fixed set of integer keys known at build time and looked up often, or string dispatch with a
hash in front and a verify step for open input.

Not for:

- Keys that change at run time: there is no insert or erase.
- Very large key sets: the search runs at compile time, and every build pays for it.
- Keys that are not integers: `phf` hashes integers only, so hash strings first (for example
  with [hashes](https://github.com/Kronuz/hashes)).

## ⚡ Performance

`phf_compare` looks up member keys drawn at random from fixed sets of 6, 46, 192 and 1,000
sparse 32-bit keys, in nanoseconds per lookup (the best of three runs, each the best of nine
rounds of 1,228,800 lookups). The *`if` ladder* compares the key with each member in turn,
*binary search* is `std::lower_bound` over the sorted keys (what a `switch` on sparse keys
compiles into), *`std::unordered_map`* maps each key to its index, and *`phf`* is `find()`. All
four return each key's index in the sorted key list; a separate check over the same lookups
found no disagreement. `std::lower_bound` and `std::unordered_map` are
[libc++](https://libcxx.llvm.org/)'s, as shipped with Apple clang 17.0.0 on each machine.

| Machine, keys | `if` ladder (ns) | binary search (ns) | `std::unordered_map` (ns) | `phf` (ns) |
|---|---:|---:|---:|---:|
| Apple M4 Pro, 6 | 1.39 | 1.50 | 1.00 | 0.53 |
| Apple M4 Pro, 46 | 6.64 | 3.93 | 1.61 | 0.53 |
| Apple M4 Pro, 192 | 32.9 | 7.39 | 1.69 | 0.48 |
| Apple M4 Pro, 1,000 | 138 | 8.65 | 1.38 | 0.53 |
| Intel Core i9-9980HK, 6 | 0.76 | 3.14 | 2.55 | 0.98 |
| Intel Core i9-9980HK, 46 | 7.57 | 10.0 | 10.3 | 0.98 |
| Intel Core i9-9980HK, 192 | 34.3 | 13.3 | 10.1 | 0.92 |
| Intel Core i9-9980HK, 1,000 | 82.8 | 13.1 | 6.82 | 1.17 |

On the i9 a six-key `if` ladder beats `phf`; from 46 keys on, `phf` is the fastest on both
machines.

For strings, a hash in front and one compare at the slot: on Xapiand's 192 field-type names,
with half of 200,000 lookups missing, `phf` with a word-at-a-time hash takes 14.1 ns per lookup
on the M4 Pro and 21.4 on the i9, against 10.9 and 16.5 for
[gperf](https://www.gnu.org/software/gperf/) 3.0.3, 19.7 and 41.7 for `std::unordered_map`,
19.8 and 30.9 for [ctrie](https://github.com/Kronuz/ctrie) at `bbce6d6`, and 28.2 and 33.0 for
[frozen](https://github.com/serge-sans-paille/frozen) at `d53e0a1`; every contender finds the
same 99,543 members. [docs/BENCHMARKS.md](docs/BENCHMARKS.md) has every contender, a stop-word
filter over a novel, and the integer core alone.

Apple M4 Pro (arm64), macOS 26.7.2, Apple clang 17.0.0 (clang-1700.3.19.1), and Intel Core
i9-9980HK (x86_64), macOS 15.8.1, Apple clang 17.0.0 (clang-1700.6.4.2), both `-O3 -DNDEBUG`:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target phf_compare phf_dispatch_field_types
./build/phf_compare
./build/phf_dispatch_field_types
```

## 📚 Documentation

- [docs/API.md](docs/API.md): `make_phf`, the members, integer keys and strings, and when not
  to use it.
- [ARCHITECTURE.md](ARCHITECTURE.md): the data layout, the lookup formula, the pre-mix, and the
  adaptive build.
- [docs/BENCHMARKS.md](docs/BENCHMARKS.md): the integer core, the comparison with an `if`
  ladder, a binary search and `std::unordered_map`, and string dispatch against gperf, frozen,
  a compile-time trie and the standard containers.
- [AGENTS.md](AGENTS.md): repository map, invariants, and traps.
- [Catalog entry](https://github.com/Kronuz/cpp-libraries/blob/main/AGENTS.md#constexpr-phf) in
  Kronuz C++ Libraries.

## 🛠️ Building and testing

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

`./build/phf_demo` runs the tour. The benchmarks (`phf_bench`, `phf_compare`,
`phf_dispatch_field_types` and `phf_dispatch_stop_words`) build with the tests; the dispatch
benchmarks fetch ctrie and frozen, and the gperf tables are committed under `bench/`.

## 🤝 Contributing

Issues and pull requests are welcome. Read [AGENTS.md](AGENTS.md) and the catalog's
[rules of engagement](https://github.com/Kronuz/cpp-libraries/blob/main/AGENTS.md#rules-of-engagement)
first; CI must pass on every platform.

## 📄 License

MIT, Copyright (c) 2018-2026 Germán Méndez Bravo. See [LICENSE](LICENSE).
