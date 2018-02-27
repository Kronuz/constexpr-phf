/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-phf ./tst-phf.cc && ./tst-phf
*/
#include <iostream>
#include <string>
#include <sysexits.h>

#include "phf.hh"

#include "tst-benchmark-hashes.h"


#include "tst-benchmark-names.h"
constexpr static auto phf_names = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	NAMES_OPTIONS(names)
	#undef OPTION
});


#include "tst-benchmark-titans.h"
constexpr static auto phf_titans = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	TITANS_OPTIONS(titans)
	#undef OPTION
});


#include "tst-benchmark-words.h"
static auto phf_words = phf::make_phf({
	#define OPTION(option, name) fnv1ah64::hash(#option),
	WORDS_OPTIONS(words)
	#undef OPTION
});


int main(int argc, char const *argv[]) {
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " <word>" << std::endl;
		return EX_USAGE;
	}
	const char* arg = argv[1];

	bool found = false;

	std::size_t pos;
	auto hash = fnv1ah64::hash(arg);

	pos = phf_names.find(hash);
	if (pos != phf::npos) {
		std::cerr << arg << " found in NAMES at " << pos << std::endl;
		found = true;
	}

	pos = phf_titans.find(hash);
	if (pos != phf::npos) {
		std::cerr << arg << " found in TITANS at " << pos << std::endl;
		found = true;
	}

	pos = phf_words.find(hash);
	if (pos != phf::npos) {
		std::cerr << arg << " found in WORDS at " << pos << std::endl;
		found = true;
	}

	if (!found) {
		std::cerr << arg << " not found!" << std::endl;
	}
	return 0;
}
