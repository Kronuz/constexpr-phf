/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-frozen-unordered_set -I ./frozen/include ./tst-benchmark-frozen-unordered_set.cc && ./tst-benchmark-frozen-unordered_set < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

#include <frozen/unordered_set.h>
#include <frozen/string.h>
using namespace frozen::string_literals;

#include "tst-benchmark-titans.h"


constexpr static auto set_names = frozen::make_unordered_set({
	#define OPTION(option, name) #option##_s,
	TITANS_OPTIONS(benchmark)
	#undef OPTION
});
static const auto it_end = set_names.end();


inline std::size_t exists(const std::string& name) {
	auto it = set_names.find(frozen::string(name.data(), name.size()));
	if (it != it_end) {
		return 1;
	}
	return 0;
}


int main() {
	std::string line;
	std::size_t count = 0;

	std::chrono::duration<double, std::milli> duration{0};

	while (std::cin) {
		std::getline(std::cin, line);
		auto start = std::chrono::steady_clock::now();
		count += exists(line);
		auto stop = std::chrono::steady_clock::now();
		duration += stop - start;
	}

	std::cerr << std::endl;
	std::cerr << "tst-benchmark-frozen-unordered_set" << std::endl;
	std::cerr << "----------------------------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
