/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph2 ./tst-benchmark-mph2.cc && ./tst-benchmark-mph2 < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

#include "mph.hh"

#include "tst-benchmark-hashes.h"
#include "tst-benchmark-names.h"
#define OPTIONS NAMES_OPTIONS


MPH_INIT_BEGIN(benchmark)
	#define OPTION MPH_OPTION_INIT
	OPTIONS(benchmark)
	#undef OPTION
MPH_INIT_END()


inline std::size_t exists(const std::string& name) {
	auto pos = MPH_FIND(name, benchmark);
	if (pos != mph::npos) {
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
	std::cerr << "tst-benchmark-mph2" << std::endl;
	std::cerr << "------------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}