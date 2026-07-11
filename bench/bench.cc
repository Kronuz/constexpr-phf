// Integer-core micro-benchmark for phf.hh.
//
// Measures the whole runtime cost of the library in isolation: the division-free
// multiply-shift lookup on well-distributed integer keys (the common, fast path),
// plus a check that an adversarial key set (distinct powers of two) automatically
// falls back to the robust pre-mixed path and stays correct.
//
// This benchmarks the ENGINE only (integer key -> dense slot). A companion benchmark,
// bench/compare.cc, pits it against the alternatives you would otherwise reach for
// (if-ladder, switch, std::unordered_map) on the same fixed integer key sets.
//
// Build & run:
//   c++ -std=c++17 -O3 -march=native -I .. bench.cc -o bench && ./bench

#include "phf.hh"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <random>
#include <set>
#include <vector>

namespace {

using clock_type = std::chrono::steady_clock;
volatile std::uint64_t g_sink = 0;

// Best-of-N timing of find() over a shuffled work list, returned as ns per lookup.
template <typename Phf>
double time_lookup(const Phf& phf, const std::vector<std::uint32_t>& work, int reps) {
    double best = 1e18;
    for (int t = 0; t < 7; ++t) {
        const auto t0 = clock_type::now();
        std::uint64_t acc = 0;
        for (int r = 0; r < reps; ++r) {
            for (auto k : work) {
                acc += static_cast<std::uint64_t>(phf.find(k));
            }
        }
        const auto t1 = clock_type::now();
        g_sink += acc;
        const double ns = std::chrono::duration<double, std::nano>(t1 - t0).count();
        best = std::min(best, ns / static_cast<double>(work.size() * static_cast<std::size_t>(reps)));
    }
    return best;
}

template <std::size_t N>
void bench_random(const char* label, std::mt19937_64& rng) {
    std::set<std::uint32_t> keyset;
    while (keyset.size() < N) {
        keyset.insert(static_cast<std::uint32_t>(rng()));
    }
    std::vector<std::uint32_t> keys(keyset.begin(), keyset.end());

    phf::phf<std::uint32_t, N> phf;
    phf.assign(keys.data(), N);

    std::vector<std::uint32_t> work;
    work.reserve(4096);
    for (int i = 0; i < 4096; ++i) {
        work.push_back(keys[rng() % N]);
    }

    const double ns = time_lookup(phf, work, 500);
    std::printf("  %-22s N=%-5zu path=%-6s  %.2f ns/lookup\n",
                label, N, phf.premixed() ? "robust" : "fast", ns);
}

void bench_adversarial() {
    constexpr std::size_t N = 32;
    std::vector<std::uint32_t> keys;
    for (std::uint32_t i = 0; i < N; ++i) {
        keys.push_back(std::uint32_t(1) << i);
    }
    phf::phf<std::uint32_t, N> phf;
    phf.assign(keys.data(), N);

    std::set<std::size_t> slots;
    bool ok = true;
    for (auto k : keys) {
        const auto s = phf.find(k);
        if (s == phf::npos || s >= N || !slots.insert(s).second) {
            ok = false;
        }
    }
    std::printf("  %-22s N=%-5zu path=%-6s  correct=%s (auto fallback)\n",
                "powers of two", N, phf.premixed() ? "robust" : "fast", ok ? "yes" : "NO");
}

}  // namespace

int main() {
    std::mt19937_64 rng(12345);
    std::printf("phf integer-core micro-benchmark (find(): multiply-shift, dense [0,N) slots)\n\n");
    bench_random<6>("time-units-sized", rng);
    bench_random<46>("lang-codes-sized", rng);
    bench_random<192>("field-types-sized", rng);
    bench_random<1000>("large", rng);
    std::printf("\n");
    bench_adversarial();
    std::printf("\n(sink %llu)\n", static_cast<unsigned long long>(g_sink));
    return 0;
}
