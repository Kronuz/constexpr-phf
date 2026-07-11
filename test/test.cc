// Smoke test for the standalone constexpr-phf library.
// Build: c++ -std=c++17 -I.. test.cc -o test && ./test
#include <cassert>
#include <cstdio>
#include "phf.hh"

int main() {
	// Build a minimal perfect hash over a set of integer keys at compile time.
	static constexpr unsigned keys[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
	constexpr auto h = phf::make_phf(keys);

	static_assert(h.size() == 8, "size");
	static_assert(!h.empty(), "not empty");   // exercises the fixed empty()

	// Every key is present; non-keys are absent.
	for (unsigned k : keys) assert(h.count(k) == 1);
	assert(h.count(4) == 0);
	assert(h.count(1) == 0);
	assert(h.count(23) == 0);

	// at() is a perfect, collision-free mapping into [0, size).
	bool seen[8] = {};
	for (unsigned k : keys) {
		auto p = h.at(k);
		assert(p < 8 && !seen[p]);
		seen[p] = true;
	}

	std::printf("constexpr-phf OK: %zu keys, collision-free, empty()=%d\n",
	            h.size(), int(h.empty()));
	return 0;
}
