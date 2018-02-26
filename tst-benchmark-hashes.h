#pragma once

template <typename T, T prime, T offset>
struct fnv1ah {
	static constexpr T hash(const char *p, std::size_t len, T seed = offset) {
		T hash = seed;
		for (std::size_t i = 0; i < len; ++i) {
			hash = (hash ^ static_cast<unsigned char>(p[i])) * prime;
		}
        return hash;
	}
	template <size_t N>
	static constexpr T hash(const char(&s)[N], T seed = offset) {
		return hash(s, N - 1, seed);
	}
	static T hash(const std::string& str, T seed = offset) {
        return hash(str.data(), str.size(), seed);
    }
};
using fnv1ah32 = fnv1ah<std::uint32_t, 0x1000193UL, 2166136261UL>;
