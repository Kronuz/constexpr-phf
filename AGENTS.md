# AGENTS.md

Guidance for agents working in this repo.

## What this is

A single-header, `constexpr` minimal perfect hash for a fixed set of integer keys. Extracted from
[Xapiand](https://github.com/Kronuz/Xapiand), where it backs compile-time dispatch tables for
reserved keywords in the query DSL and aggregations. See `README.md` for the user-facing API and
`ARCHITECTURE.md` for the internal design.

This is the **integer engine** only. The string front-end (pluggable hashers, a switch-friendly
`set`/`map`, verification, cross-implementation benchmarks) lives in a separate library,
[`keywords`](https://github.com/Kronuz/keywords), which depends on this one. Keep this repo
hash-agnostic and integer-only; do not add a string interface here.

## Repo map

- `phf.hh` — the entire library. Header-only, at the repo root. Contains a compile-time prime table, helpers
  (`quicksort`, `find_prime`, `prime`, `log2`), the pre-mix (`mixk`), the `phf<ItemType, NumItems>`
  class, and the `make_phf` factory. Everything is in namespace `phf`. It is the only header in the
  repo.
- `test/test.cc` — smoke test. Builds a `phf` over eight keys; checks `size`, `empty`, `count`, and
  that `at` is a collision-free mapping into `[0, size)`.
- `test/correctness.cc` — deeper harness (wired into CTest). Random sets N=1..5000, structured and
  adversarial sets (all keys in one bucket; **distinct powers of two**, which forces the robust
  fallback), `uint64` overflow keys, signed/negative keys, no-false-positive checks, and the throw
  modes. Verifies `at()` is always a bijection into `[0,N)`.
- `bench/bench.cc` — integer-core micro-benchmark (not a test). Times `find()` in isolation on
  well-distributed key sets (fast path, sub-ns) and confirms the powers-of-two set falls back to the
  robust path and stays correct. String-dispatch and cross-implementation benchmarks belong in
  `keywords`, not here.
- `examples/demo.cc` — a runnable tour of the API.
- `CMakeLists.txt` — the `constexpr_phf` INTERFACE target (exposes the repo root, matching the other
  extracted libs);
  tests, bench, and demo build only when this repo is top-level.
- `LICENSE` — MIT, Copyright (C) 2018-2019 German Mendez Bravo (Kronuz).

## Build & run

```sh
cmake -B build && cmake --build build && ctest --test-dir build
./build/phf_demo     # a runnable tour
./build/phf_bench    # the integer-core micro-benchmark
```

Most of the test is `static_assert` and `assert`, so a clean compile already exercises the
compile-time build path.

## Conventions

- C++17, header-only. No `.cpp` for the library itself; do not add one.
- Zero dependencies beyond the standard library. Do not introduce third-party includes.
- `<iostream>` is included only under `#define PHF_DEBUG`, and every `std::cerr` line is gated
  behind that macro. Keep it that way: the default build must have no I/O dependency.
- Tabs for indentation, matching the existing file.
- Everything user-facing stays `constexpr` and `noexcept` where it already is.

## Load-bearing invariants

These must not break:

- `buckets_size` stays a power of two (`1 << log2(NumItems + 1)`). Bucket selection relies on
  `item & (buckets_size - 1)` being a cheap mask.
- `index_size` stays a power of two (`1 << index_bits`) and at least `NumItems`. The lookup uses a
  high-bits shift (`>> shift`, `shift = item_bits - index_bits`), not a modulus. Do not reintroduce a
  prime modulus.
- The lookup formula `_index[(((_premix ? mixk(item) : item) * mul) >> shift) + off]` must stay in
  sync with how `_build` assigns `mul`/`off` **and** with the `mixk` pre-mix. The pre-mix must be
  applied identically at build and at lookup, gated on the same `_premix`.
- The adaptive build order is load-bearing: `assign` tries `_build` with `_premix = false` first,
  then `_premix = true`. `_build` returns `false` on an exhausted multiplier search (retryable);
  it must not throw there. Duplicate-key and input-size errors still throw and are not retryable.
- `_index` keeps its `index_size + 1` slots with slot 0 reserved (offsets are 1-based).
- Membership is decided by `elem.item == item`, not by the slot existing. `count`, `find`, and `at`
  must keep that check. `lookup` deliberately omits it; do not "fix" it.
- `empty()` returns `_size == 0`. An older Xapiand copy returned `!!_size` (inverted); this repo
  fixed it. Do not regress it.
- `premixed()` is read-only and reflects the chosen path. It is informational; correctness must not
  depend on callers reading it.
- Duplicate keys throw, oversized or empty inputs throw, and a build that fails even with the pre-mix
  throws "cannot find suitable table". Keep these failure modes.

## How to extend

- New query methods belong on the `phf` class next to `count`/`find`/`at`, routed through `_lookup`
  so they share the one lookup formula (including the `_premix` branch).
- New input shapes belong as `assign` overloads (array, `initializer_list`, iterator-pair, and
  pointer-plus-size already exist), all funneling into `assign(const ItemType*, std::size_t)` and
  thus through the adaptive `_build`.
- If you touch `_build` or the lookup, re-run `phf_correctness`. The **distinct powers of two** case
  is the gate that proves the fast path fails over to the robust path; a change that makes it pass on
  the fast path or fail on the robust path is a regression.
- Exercise several key-set sizes (a single key, and a set large enough to create multi-key buckets)
  so both the displacement path and the singleton-completion path are covered.
- To debug a build, define `PHF_DEBUG` before including `phf.hh` for `std::cerr` tracing of mappings,
  the multiplier search, rollbacks, and the final tables.
