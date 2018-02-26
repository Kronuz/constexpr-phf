/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set ./tst-benchmark-unordered_set.cc && ./tst-benchmark-unordered_set < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

#include <unordered_set>

#include "tst-benchmark-hashes.h"
#ifdef NAMES
#include "tst-benchmark-names.h"
#else
#include "tst-benchmark-titans.h"
#endif
#define OPTIONS NAMES_OPTIONS


static const std::unordered_set<std::string> set_names = {
	#define OPTION(option, name) #option,
	OPTIONS(benchmark)
	#undef OPTION
};
static const auto it_end = set_names.end();

inline std::size_t exists(const std::string& name) {
	auto it = set_names.find(name);
	if (it != it_end) {
		return 1;
	}
	return 0;
}


int main() {
	std::string line;
	std::size_t count = 0;

	std::chrono::duration<double, std::milli> duration{0};

	while(std::cin) {
		std::getline(std::cin, line);
		auto start = std::chrono::steady_clock::now();
		count += exists(line);
		auto stop = std::chrono::steady_clock::now();
		duration += stop - start;
	}

	std::cerr << std::endl;
	std::cerr << "tst-benchmark-unordered_set" << std::endl;
	std::cerr << "---------------------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
