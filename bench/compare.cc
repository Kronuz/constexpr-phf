// Cross-strategy comparison for phf.hh.
//
// The case for a perfect hash, in numbers: when you dispatch on a FIXED set of keys
// known at build time, what does each alternative cost as the set grows? This pits the
// engine against the things you would otherwise reach for on the same sparse integer
// key sets (the hashes you actually dispatch on):
//
//   if-ladder            linear scan of == comparisons          O(n)
//   switch (binsearch)   what a sparse `switch` compiles into   O(log n) branches
//   std::unordered_map   hash + probe + pointer chase           ~O(1), but a heap
//   phf.find()           multiply-shift + two array reads       O(1), branchless, flat
//
// Build & run:
//   c++ -std=c++17 -O3 -march=native -I .. bench/compare.cc -o compare && ./compare

#include "phf.hh"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>

namespace {

using clock_type = std::chrono::steady_clock;
volatile std::uint64_t g_sink = 0;

// Best-of-N timing of an op over a shuffled work list, returned as ns per lookup.
template <typename F>
double time_op(F&& op, const std::vector<std::uint32_t>& work, int reps) {
    double best = 1e18;
    for (int t = 0; t < 9; ++t) {
        const auto t0 = clock_type::now();
        std::uint64_t acc = 0;
        for (int r = 0; r < reps; ++r) {
            for (auto k : work) {
                acc += op(k);
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
void run(const char* label, std::mt19937_64& rng) {
    std::set<std::uint32_t> ks;
    while (ks.size() < N) {
        ks.insert(static_cast<std::uint32_t>(rng()) | 1u);
    }
    const std::vector<std::uint32_t> keys(ks.begin(), ks.end());  // sorted

    std::unordered_map<std::uint32_t, std::uint32_t> umap;
    for (std::uint32_t i = 0; i < N; ++i) {
        umap[keys[i]] = i;
    }
    phf::phf<std::uint32_t, N> phf;
    phf.assign(keys.data(), N);

    std::vector<std::uint32_t> work;
    work.reserve(4096);
    for (int i = 0; i < 4096; ++i) {
        work.push_back(keys[rng() % N]);
    }

    auto ladder = [&](std::uint32_t k) {
        for (std::uint32_t i = 0; i < N; ++i) {
            if (keys[i] == k) return i;
        }
        return 0u;
    };
    auto binsearch = [&](std::uint32_t k) {
        return static_cast<std::uint32_t>(std::lower_bound(keys.begin(), keys.end(), k) - keys.begin());
    };
    auto hashmap = [&](std::uint32_t k) {
        const auto it = umap.find(k);
        return it == umap.end() ? 0u : it->second;
    };
    auto perfect = [&](std::uint32_t k) {
        return static_cast<std::uint32_t>(phf.find(k));
    };

    const double l = time_op(ladder, work, 300);
    const double b = time_op(binsearch, work, 300);
    const double u = time_op(hashmap, work, 300);
    const double p = time_op(perfect, work, 300);
    std::printf("  %-14s N=%-5zu  if-ladder %7.2f | switch(binsearch) %6.2f | unordered_map %5.2f | phf %5.2f  ns\n",
                label, N, l, b, u, p);
}

}  // namespace

int main() {
    std::mt19937_64 rng(12345);
    std::printf("Integer dispatch on a fixed sparse key set (ns/lookup, best of 9)\n\n");
    run<6>("time-units", rng);
    run<46>("lang-codes", rng);
    run<192>("field-types", rng);
    run<1000>("large", rng);
    std::printf("\n(sink %llu)\n", static_cast<unsigned long long>(g_sink));
    return 0;
}
