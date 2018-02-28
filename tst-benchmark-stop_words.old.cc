/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words ./tst-benchmark-stop_words.cc && ./tst-benchmark-stop_words
*/
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sysexits.h>

#include "phf.hh"

#include "hashes.hh"


int main(int argc, char const *argv[]) {
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " <stop_words_file>" << std::endl;
		return EX_USAGE;
	}
	const char* arg = argv[1];

	std::ifstream words(arg);
	if (!words.is_open()) {
		std::cerr << "Cannot open file: " << arg << std::endl;
		return 1;
	}

	// set
	std::set<std::string> stop_words_set;
	stop_words_set.insert(std::istream_iterator<std::string>(words), std::istream_iterator<std::string>());
	auto it_end = stop_words_set.end();
	if (stop_words_set.size() > 1000) {
		std::cerr << "Too many elements: " << stop_words_set.size() << std::endl;
		return 1;
	}

	// phf
	std::vector<uint64_t> result;
	std::transform(stop_words_set.begin(), stop_words_set.end(), std::back_inserter(result), fnv1ah64{});
	phf::phf<uint64_t, 1000> stop_words_phf;
	stop_words_phf.assign(result.data(), result.size());

	////

	std::chrono::time_point<std::chrono::steady_clock> start, stop;
	std::string line;

	std::size_t count_set = 0;
	std::chrono::duration<double, std::milli> duration_set{0};

	std::size_t count_phf = 0;
	std::chrono::duration<double, std::milli> duration_phf{0};

	while (std::cin) {
		std::getline(std::cin, line);

		start = std::chrono::steady_clock::now();
		auto it = stop_words_set.find(line);
		if (it != it_end) {
			++count_set;
		}
		stop = std::chrono::steady_clock::now();
		duration_set += stop - start;

		////

		start = std::chrono::steady_clock::now();
		auto pos = stop_words_phf.find(fnv1ah64::hash(line));
		if (pos != phf::npos) {
			++count_phf;
		}
		stop = std::chrono::steady_clock::now();
		duration_phf += stop - start;
	}

	////

	std::cerr << std::endl;
	std::cerr << "tst-benchmark-stop_words" << std::endl;
	std::cerr << "+-----------------------" << std::endl;
	std::cerr << "|count_set: " << count_set << std::endl;
	std::cerr << "|duration_set: " << duration_set.count() << " ms" << std::endl;
	std::cerr << "+-----------------------" << std::endl;
	std::cerr << "|count_phf: " << count_phf << std::endl;
	std::cerr << "|duration_phf: " << duration_phf.count() << " ms" << std::endl;
	std::cerr << "+----------------------" << std::endl;

	// stop_words_phf.dump();

	return 0;
}
