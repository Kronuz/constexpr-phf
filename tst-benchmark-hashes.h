#pragma once

template <typename T, T prime, T offset>
struct fnv1ah {
	static constexpr T hash(const char *p, std::size_t len, T seed = offset) {
        return len == 1 ? (seed ^ static_cast<unsigned char>(*p)) * prime : (hash(p, len - 1, seed) ^ static_cast<unsigned char>(p[len - 1])) * prime;
	}
	template <size_t N>
	static constexpr T hash(const char(&s)[N], T seed = offset) {
		return hash(s, N - 1, seed);
	}
	static T hash(const std::string& str, T seed = offset) {
        T hash = seed;
		for (char c : str) {
            hash = (hash ^ static_cast<unsigned char>(c)) * prime;
        }
        return hash;
    }
};
using fnv1ah32 = fnv1ah<std::uint32_t, 0x1000193UL, 2166136261UL>;
