// Cross-implementation benchmark for compile-time string membership.
//
// Filters stop words out of a text corpus, timing each approach. The corpus is read
// from stdin (whitespace-split), so pipe a large text in:
//
//   cmake --build build --target phf_dispatch_stop_words
//   gzcat bench/monte-cristo.txt.gz | ./build/phf_dispatch_stop_words
//
// Reports, per contender, how many words matched (correctness cross-check: every
// verified approach must agree) and the best single-pass time over the corpus.
//
// The stop-word list is 570 entries (tst-benchmark-stop_words.h). This is arbitrary
// input, so only VERIFIED lookups are apples-to-apples; the one unverified contender
// (constexpr-phf hash-only, the fast path) is included to show the speed/safety
// trade-off and is expected to over-count.

#include "phf_dispatch.hh"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "tst-benchmark-stop_words.h"        // STOP_WORDS_STRINGS(...)
#include "tst-benchmark-stop_words-gperf.h"  // Perfect_Hash::in_word_set

#ifndef KW_BENCH_NO_FROZEN
#include <frozen/string.h>
#include <frozen/unordered_set.h>
#endif

#ifndef KW_BENCH_NO_CTRIE
#include "ctrie.hh"
#endif

// The keyword set as a constexpr array of string_views, from the macro list.
static constexpr std::string_view STOP_ARR[] = {
#define STRING(s, ...) std::string_view(s),
    STOP_WORDS_STRINGS()
#undef STRING
};
static constexpr std::size_t STOPN = sizeof(STOP_ARR) / sizeof(STOP_ARR[0]);

namespace {

using clock_type = std::chrono::steady_clock;

template <typename Pred>
void run(const char* label, const std::vector<std::string>& words, Pred&& pred) {
    std::size_t matched = 0;
    double best_ms = 1e18;
    for (int t = 0; t < 15; ++t) {
        std::size_t m = 0;
        const auto t0 = clock_type::now();
        for (const auto& w : words) {
            if (pred(w)) ++m;
        }
        const auto t1 = clock_type::now();
        best_ms = std::min(best_ms, std::chrono::duration<double, std::milli>(t1 - t0).count());
        matched = m;
    }
    std::cerr << "  " << std::setw(9) << matched << " / " << words.size() << "   "
              << std::setw(8) << std::fixed << std::setprecision(2) << best_ms << " ms   ["
              << label << "]\n";
}

}  // namespace

int main() {
    const std::vector<std::string> words{std::istream_iterator<std::string>(std::cin), {}};
    std::cerr << "Filtering stop words over " << words.size() << " words (best of 15 passes):\n";

    // --- constexpr-phf used for strings: hash (the caller's choice) + phf + verify ---
    static const pd::set<STOPN, pd::fnv1a> phf_fnv(STOP_ARR);
    static const pd::set<STOPN, pd::wordwise> phf_word(STOP_ARR);

    run("constexpr-phf verified (fnv1a)", words,
        [&](const std::string& w) { return phf_fnv.match(w) != pd::npos; });
    run("constexpr-phf verified (wordwise)", words,
        [&](const std::string& w) { return phf_word.match(w) != pd::npos; });
    run("constexpr-phf hash-only (fnv1a)", words,
        [&](const std::string& w) { return phf_fnv.find(w) < phf_fnv.size(); });

    // --- switch on the verified lookup (jump-table dispatch) ---
    run("switch(constexpr-phf verified)", words, [&](const std::string& w) {
        switch (phf_fnv.match(w)) {
            case pd::npos:
                return false;
            default:
                return true;
        }
    });

    // --- gperf ---
    run("gperf", words, [&](const std::string& w) {
        return Perfect_Hash::in_word_set(w.data(), w.size()) != nullptr;
    });

#ifndef KW_BENCH_NO_FROZEN
    // --- frozen::unordered_set ---
    static const auto frozen_set = frozen::make_unordered_set({
#define STRING(s, ...) frozen::string(s),
        STOP_WORDS_STRINGS()
#undef STRING
    });
    run("frozen::unordered_set", words, [&](const std::string& w) {
        return frozen_set.find(frozen::string(w.data(), w.size())) != frozen_set.end();
    });
#endif

#ifndef KW_BENCH_NO_CTRIE
    // --- ctrie (compile-time trie) ---
    static constexpr auto ctrie_set = ctrie::build(
#define STRING(s, ...) s##_cword,
        STOP_WORDS_STRINGS()
#undef STRING
            ""_cword);
    run("ctrie", words, [&](const std::string& w) { return ctrie_set.find(w) != ctrie::npos; });
#endif

    // --- raw hash switch, UNVERIFIED (no membership check) ---
    run("switch(fnv1a hash)         UNVERIFIED", words, [&](const std::string& w) {
        switch (pd::fnv1a::hash(w)) {
#define STRING(s, ...) case pd::fnv1a::hash(s):
            STOP_WORDS_STRINGS()
#undef STRING
            return true;
            default:
                return false;
        }
    });

    // --- std containers ---
    static const std::unordered_set<std::string> uset = [] {
        std::unordered_set<std::string> s;
#define STRING(k, ...) s.insert(k);
        STOP_WORDS_STRINGS()
#undef STRING
        return s;
    }();
    run("std::unordered_set", words,
        [&](const std::string& w) { return uset.find(w) != uset.end(); });

    static const std::unordered_map<std::string, bool> umap = [] {
        std::unordered_map<std::string, bool> m;
#define STRING(k, ...) m.emplace(k, true);
        STOP_WORDS_STRINGS()
#undef STRING
        return m;
    }();
    run("std::unordered_map", words,
        [&](const std::string& w) { return umap.find(w) != umap.end(); });

    static const std::set<std::string> oset(uset.begin(), uset.end());
    run("std::set", words, [&](const std::string& w) { return oset.find(w) != oset.end(); });

    return 0;
}
