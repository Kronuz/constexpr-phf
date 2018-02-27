/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-gperf ./tst-benchmark-gperf.cc && ./tst-benchmark-gperf < /usr/share/dict/words
*/
#include <iostream>
#include <chrono>
#include <string>

// gpref.h files are generated like this:
//   gperf -ILC++ tst-benchmark-names-gperf.in > tst-benchmark-names-gperf.h
//   gperf -ILC++ tst-benchmark-titans-gperf.in > tst-benchmark-titans-gperf.h
#include "tst-benchmark-titans-gperf.h"


inline std::size_t exists(const std::string& name) {
	auto str = Perfect_Hash::in_word_set(name.data(), name.size());
	if (str) {
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
	std::cerr << "tst-benchmark-gperf" << std::endl;
	std::cerr << "-------------------" << std::endl;
	std::cerr << "count: " << count << std::endl;
	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
