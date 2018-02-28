/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-phf ./tst-phf.cc && ./tst-phf
*/
#include <chrono>
#include <iostream>
#include <string>
#include <sysexits.h>

#include "phf.hh"

#include "hashes.hh"

#include "tst-benchmark-titans.h"
#include "tst-benchmark-names.h"
#include "tst-benchmark-words.h"


#ifdef TITANS_OPTIONS
constexpr static auto phf_titans = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	TITANS_OPTIONS(titans)
	#undef OPTION
});
#endif


#ifdef NAMES_OPTIONS
constexpr static auto phf_names = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	NAMES_OPTIONS(names)
	#undef OPTION
});
#endif


#ifdef WORDS_OPTIONS
static auto phf_words = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	WORDS_OPTIONS(words)
	#undef OPTION
});
#endif


int main(int argc, char const *argv[]) {
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " <word>" << std::endl;
		return EX_USAGE;
	}
	const char* arg = argv[1];

	bool found = false;
	std::chrono::duration<double, std::milli> duration{0};
	std::chrono::time_point<std::chrono::steady_clock> start, stop;

	std::size_t pos;
	auto hash = fnv1ah64::hash(arg);

	#ifdef TITANS_OPTIONS
	start = std::chrono::steady_clock::now();
	pos = phf_titans.find(hash);
	stop = std::chrono::steady_clock::now();
	duration += stop - start;
	if (pos != phf::npos) {
		std::cerr << arg << " found in TITANS at " << pos << std::endl;
		found = true;
	}
	#endif

	#ifdef NAMES_OPTIONS
	start = std::chrono::steady_clock::now();
	pos = phf_names.find(hash);
	stop = std::chrono::steady_clock::now();
	duration += stop - start;
	if (pos != phf::npos) {
		std::cerr << arg << " found in NAMES at " << pos << std::endl;
		found = true;
	}
	#endif

	#ifdef WORDS_OPTIONS
	start = std::chrono::steady_clock::now();
	pos = phf_words.find(hash);
	stop = std::chrono::steady_clock::now();
	duration += stop - start;
	if (pos != phf::npos) {
		std::cerr << arg << " found in WORDS at " << pos << std::endl;
		found = true;
	}
	#endif

	if (!found) {
		std::cerr << arg << " not found!" << std::endl;
	}

	std::cerr << "duration: " << duration.count() << " ms" << std::endl;

	return 0;
}
