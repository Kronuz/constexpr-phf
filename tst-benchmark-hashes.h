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
	template <typename... Args>
	T operator()(Args&&... args) const {
		return hash(std::forward<Args>(args)...);
	}
};
using fnv1ah32 = fnv1ah<std::uint32_t, 0x1000193UL, 2166136261UL>;
using fnv1ah64 = fnv1ah<std::uint64_t, 0x100000001b3ULL, 14695981039346656037ULL>;

constexpr std::uint32_t operator"" _fnv1a(const char* s, size_t size) {
	return fnv1ah64::hash(s, size);
}
