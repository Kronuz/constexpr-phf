// A compile-time string-keyword set built on the phf integer engine. It exists ONLY for the
// benchmarks, to show how constexpr-phf dispatches on strings and how that compares to the
// alternatives (gperf, frozen, a compile-time trie, std containers, a raw hash switch).
//
// The engine is integer-only and never sees a string: YOU pick a hash, it takes the integer.
// So this is the caller's pattern, not a phf feature: hash each key to an integer with a
// constexpr hash of your choosing, build a phf over the hashes, keep the keys indexed by slot,
// and on a lookup do the perfect-hash lookup then ONE compare against the single key stored at
// that slot, so a non-member never false-matches. Two hashes are inlined here so a benchmark
// can pick either and pull in nothing but phf.hh: FNV-1a (byte-at-a-time) and a word-at-a-time
// hash. Which one is faster depends on the keys (see the bench output).
#ifndef PHF_DISPATCH_HH
#define PHF_DISPATCH_HH

#include "phf.hh"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace pd {

constexpr std::size_t npos = phf::npos;

// FNV-1a, 64-bit: byte-at-a-time, cheapest for short keys.
struct fnv1a {
    static constexpr std::uint64_t hash(std::string_view s) noexcept {
        std::uint64_t h = 14695981039346656037ULL;
        for (char c : s) {
            h = (h ^ static_cast<unsigned char>(c)) * 0x100000001b3ULL;
        }
        return h;
    }
};

// Word-at-a-time 64-bit: eight bytes per step, so it pulls ahead as keys get longer.
struct wordwise {
    static constexpr std::uint64_t hash(std::string_view s) noexcept {
        constexpr std::uint64_t P = 0x9e3779b97f4a7c15ULL;
        const char* p = s.data();
        const std::size_t len = s.size();
        std::uint64_t h = 0x100000001b3ULL ^ (static_cast<std::uint64_t>(len) * P);
        std::size_t i = 0;
        while (i + 8 <= len) {
            std::uint64_t w = 0;
            for (int k = 0; k < 8; ++k) {
                w |= static_cast<std::uint64_t>(static_cast<unsigned char>(p[i + k])) << (8 * k);
            }
            h ^= w;
            h *= P;
            h ^= h >> 29;
            i += 8;
        }
        std::uint64_t tail = 0;
        int shift = 0;
        for (; i < len; ++i, shift += 8) {
            tail |= static_cast<std::uint64_t>(static_cast<unsigned char>(p[i])) << shift;
        }
        h ^= tail;
        h *= P;
        h ^= h >> 32;
        return h;
    }
};

// The caller picks the hash explicitly; phf itself has no hasher, it only takes the integer.
template <std::size_t N, class Hasher>
class set {
    phf::phf<std::uint64_t, N> _phf{};
    std::array<std::string_view, N> _keys{};
    std::size_t _min_len = 0;
    std::size_t _max_len = 0;

public:
    static constexpr std::size_t npos = phf::npos;

    constexpr explicit set(const std::string_view (&keys)[N]) {
        _min_len = _max_len = keys[0].size();
        for (std::size_t i = 1; i < N; ++i) {
            if (keys[i].size() < _min_len) _min_len = keys[i].size();
            if (keys[i].size() > _max_len) _max_len = keys[i].size();
        }
        std::array<std::uint64_t, N> hashes{};
        for (std::size_t i = 0; i < N; ++i) {
            hashes[i] = Hasher::hash(keys[i]);
        }
        _phf.assign(hashes.data(), N);
        for (std::size_t i = 0; i < N; ++i) {
            _keys[_phf.find(hashes[i])] = keys[i];
        }
    }

    // Hash-only, fast, unverified: a non-member can misdispatch (see phf::find).
    constexpr std::size_t find(std::string_view sv) const noexcept {
        return _phf.find(Hasher::hash(sv));
    }

    // Verified: length guard, then one compare against the single candidate at the slot.
    constexpr std::size_t match(std::string_view sv) const noexcept {
        if (static_cast<std::size_t>(sv.size() - _min_len) > (_max_len - _min_len)) {
            return npos;
        }
        const std::size_t slot = _phf.find(Hasher::hash(sv));
        if (slot == phf::npos) {
            return npos;
        }
        return _keys[slot] == sv ? slot : npos;
    }

    constexpr std::size_t size() const noexcept { return N; }
};

}  // namespace pd

#endif  // PHF_DISPATCH_HH
