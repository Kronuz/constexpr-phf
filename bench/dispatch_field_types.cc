// Cross-implementation benchmark on a REAL, mixed-length keyword set: Xapiand's 192
// field-type names (lengths 2..23, median 14), from schema.cc. Unlike the stop-words
// corpus (all short words), this exercises the short AND long regimes, so it shows which
// hash to pick for constexpr-phf here (FNV-1a byte-at-a-time vs a word-at-a-time hash), and
// how it compares to gperf, frozen, a compile-time trie, and std containers.
//
//   cmake --build build --target phf_dispatch_field_types && ./build/phf_dispatch_field_types
//
// The workload is a 50/50 mix of the real keywords and plausible non-keywords (each real
// keyword with a trailing '!', so same length distribution, guaranteed absent). All
// verified contenders must agree on the match count.

#include "phf_dispatch.hh"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "field_types.h"     // FIELD_TYPES(X)
#include "gperf_large.hpp"   // KwLarge::lookup

#include <frozen/string.h>
#include <frozen/unordered_set.h>

#include "ctrie.hh"

static constexpr std::string_view FIELDS[] = {
#define X(s) std::string_view(s),
    FIELD_TYPES(X)
#undef X
};
static constexpr std::size_t NF = sizeof(FIELDS) / sizeof(FIELDS[0]);

namespace {
using clock_type = std::chrono::steady_clock;

template <typename Pred>
void run(const char* label, const std::vector<std::string>& work, Pred&& pred) {
    std::size_t matched = 0;
    double best_ns = 1e18;
    for (int t = 0; t < 15; ++t) {
        std::size_t m = 0;
        const auto t0 = clock_type::now();
        for (const auto& w : work) {
            if (pred(w)) ++m;
        }
        const auto t1 = clock_type::now();
        best_ns = std::min(best_ns,
                           std::chrono::duration<double, std::nano>(t1 - t0).count() / work.size());
        matched = m;
    }
    std::cerr << "  " << std::setw(9) << matched << "   " << std::setw(6) << std::fixed
              << std::setprecision(2) << best_ns << " ns/op   [" << label << "]\n";
}
}  // namespace

int main() {
    // Workload: real keywords (members) + the same with a trailing '!' (non-members),
    // shuffled, repeated to a large stream.
    std::vector<std::string> pool;
    for (auto sv : FIELDS) {
        pool.emplace_back(sv);
        pool.emplace_back(std::string(sv) + "!");
    }
    std::mt19937 rng(20260711);
    std::vector<std::string> work;
    work.reserve(200000);
    std::uniform_int_distribution<std::size_t> pick(0, pool.size() - 1);
    for (int i = 0; i < 200000; ++i) {
        work.push_back(pool[pick(rng)]);
    }

    std::cerr << "Real Xapiand field-types: " << NF << " keywords (len 2..23), " << work.size()
              << " lookups, best of 15 (expect ~" << work.size() / 2 << " matches):\n";

    // --- constexpr-phf used for strings: hash (the caller's choice) + phf + verify ---
    static const pd::set<NF, pd::fnv1a> phf_fnv(FIELDS);
    static const pd::set<NF, pd::wordwise> phf_word(FIELDS);

    run("constexpr-phf verified (fnv1a)", work,
        [&](const std::string& w) { return phf_fnv.match(w) != pd::npos; });
    run("constexpr-phf verified (wordwise)", work,
        [&](const std::string& w) { return phf_word.match(w) != pd::npos; });
    run("constexpr-phf hash-only (wordwise)", work,
        [&](const std::string& w) { return phf_word.find(w) < phf_word.size(); });

    // --- gperf (real generated table for this exact set) ---
    run("gperf", work, [&](const std::string& w) {
        return KwLarge::lookup(w.data(), static_cast<unsigned>(w.size())) != nullptr;
    });

    // --- frozen ---
    static const auto frozen_set = frozen::make_unordered_set({
#define X(s) frozen::string(s),
        FIELD_TYPES(X)
#undef X
    });
    run("frozen::unordered_set", work, [&](const std::string& w) {
        return frozen_set.find(frozen::string(w.data(), w.size())) != frozen_set.end();
    });

    // --- ctrie ---
    static constexpr auto ctrie_set = ctrie::build(
#define X(s) s##_cword,
        FIELD_TYPES(X)
#undef X
            ""_cword);
    run("ctrie", work, [&](const std::string& w) { return ctrie_set.find(w) != ctrie::npos; });

    // --- raw hash switch, UNVERIFIED ---
    run("switch(fnv1a hash, UNVERIFIED)", work, [&](const std::string& w) {
        switch (pd::fnv1a::hash(w)) {
#define X(s) case pd::fnv1a::hash(s):
            FIELD_TYPES(X)
#undef X
            return true;
            default:
                return false;
        }
    });

    // --- std containers ---
    static const std::unordered_set<std::string> uset = [] {
        std::unordered_set<std::string> s;
#define X(k) s.insert(k);
        FIELD_TYPES(X)
#undef X
        return s;
    }();
    run("std::unordered_set", work, [&](const std::string& w) { return uset.count(w) != 0; });

    static const std::unordered_map<std::string, int> umap = [] {
        std::unordered_map<std::string, int> m;
        int i = 0;
#define X(k) m.emplace(k, i++);
        FIELD_TYPES(X)
#undef X
        return m;
    }();
    run("std::unordered_map", work, [&](const std::string& w) { return umap.count(w) != 0; });

    static const std::set<std::string> oset(uset.begin(), uset.end());
    run("std::set", work, [&](const std::string& w) { return oset.count(w) != 0; });

    return 0;
}
