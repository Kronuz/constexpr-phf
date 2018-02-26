/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch ./tst-benchmark-switch.cc && ./tst-benchmark-switch < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

#include "tst-benchmark-hashes.h"
#ifdef NAMES
#include "tst-benchmark-names.h"
#else
#include "tst-benchmark-titans.h"
#endif
#define OPTIONS NAMES_OPTIONS


inline std::size_t exists(const std::string& name) {
	switch (fnv1ah32::hash(name)) {
		#define OPTION(option, name) case fnv1ah32::hash(#option): return 1;
		OPTIONS(benchmark)
		#undef OPTION
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
	std::cerr << "tst-benchmark-switch" << std::endl;
	std::cerr << "--------------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
