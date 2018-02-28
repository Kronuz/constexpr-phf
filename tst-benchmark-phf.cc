/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-phf ./tst-benchmark-phf.cc && ./tst-benchmark-phf < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

#include "phf.hh"

#include "hashes.hh"

#include "tst-benchmark-titans.h"


PHF_INIT_BEGIN(benchmark)
	#define OPTION PHF_OPTION_INIT
	TITANS_OPTIONS(benchmark)
	#undef OPTION
PHF_INIT_END()


inline std::size_t exists(const std::string& name) {
	auto pos = PHF_FIND(name, benchmark);
	if (pos != phf::npos) {
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
	std::cerr << "tst-benchmark-phf" << std::endl;
	std::cerr << "-----------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
