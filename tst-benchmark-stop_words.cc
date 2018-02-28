/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words -I ./frozen/include ./tst-benchmark-stop_words.cc && gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words
*/
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <sysexits.h>

#include <frozen/unordered_set.h>
#include <frozen/string.h>
using namespace frozen::string_literals;

#include "phf.hh"
#include "hashes.hh"

#include "tst-benchmark-stop_words.h"
#include "tst-benchmark-stop_words-gperf.h"
#include "tst-benchmark-stop_words-table64.h"


int main() {
	////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> words{std::istream_iterator<std::string>(std::cin), {}};
	////////////////////////////////////////////////////////////////////////////
	std::cerr << "Using " << words.size() << " words..." << std::endl;


	//           _
	//  ___  ___| |_
	// / __|/ _ \ __|
	// \__ \  __/ |_
	// |___/\___|\__|
	{
		std::set<std::string> stop_words_set{
			#define STRING(option, name) option,
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		};
		auto it_end = stop_words_set.end();
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_set.find(word);
			if (it != it_end) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (set)" << std::endl;
	}


	//                            _                   _              _
	//  _   _ _ __   ___  _ __ __| | ___ _ __ ___  __| |    ___  ___| |_
	// | | | | '_ \ / _ \| '__/ _` |/ _ \ '__/ _ \/ _` |   / __|/ _ \ __|
	// | |_| | | | | (_) | | | (_| |  __/ | |  __/ (_| |   \__ \  __/ |_
	//  \__,_|_| |_|\___/|_|  \__,_|\___|_|  \___|\__,_|___|___/\___|\__|
	//                                                |_____|
	{
		std::unordered_set<std::string> stop_words_set{
			#define STRING(option, name) option,
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		};
		auto it_end = stop_words_set.end();
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_set.find(word);
			if (it != it_end) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (unordered_set)" << std::endl;
	}


	//                         __
	//   __ _ _ __   ___ _ __ / _|
	//  / _` | '_ \ / _ \ '__| |_
	// | (_| | |_) |  __/ |  |  _|
	//  \__, | .__/ \___|_|  |_|
	//  |___/|_|
	{
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			if (Perfect_Hash::in_word_set(word.data(), word.size())) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (gperf)" << std::endl;
	}


	//   __                                                    _                   _              _
	//  / _|_ __ ___ _______ _ __    _   _ _ __   ___  _ __ __| | ___ _ __ ___  __| |    ___  ___| |_
	// | |_| '__/ _ \_  / _ \ '_ \  | | | | '_ \ / _ \| '__/ _` |/ _ \ '__/ _ \/ _` |   / __|/ _ \ __|
	// |  _| | | (_) / /  __/ | | | | |_| | | | | (_) | | | (_| |  __/ | |  __/ (_| |   \__ \  __/ |_
	// |_| |_|  \___/___\___|_| |_|  \__,_|_| |_|\___/|_|  \__,_|\___|_|  \___|\__,_|___|___/\___|\__|
	//                                                                             |_____|
	{
		auto stop_words_frozen_unordered_set = frozen::make_unordered_set({
			#define STRING(option, name) frozen::string(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		auto it_end = stop_words_frozen_unordered_set.end();
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_frozen_unordered_set.find(frozen::string(word.data(), word.size()));
			if (it != it_end) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (frozen::unordered_set)" << std::endl;
	}


	//        _      __            __            _       _     _________
	//  _ __ | |__  / _|    _     / _|_ ____   _/ | __ _| |__ |___ /___ \
	// | '_ \| '_ \| |_   _| |_  | |_| '_ \ \ / / |/ _` | '_ \  |_ \ __) |
	// | |_) | | | |  _| |_   _| |  _| | | \ V /| | (_| | | | |___) / __/
	// | .__/|_| |_|_|     |_|   |_| |_| |_|\_/ |_|\__,_|_| |_|____/_____|
	// |_|
	{
		fnv1ah32 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto pos = stop_words_phf.find(fnv1a(word));
			if (pos != phf::npos) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (phf + fnv1ah32)" << std::endl;
	}


	//        _      __            __            _       _      __   _  _
	//  _ __ | |__  / _|    _     / _|_ ____   _/ | __ _| |__  / /_ | || |
	// | '_ \| '_ \| |_   _| |_  | |_| '_ \ \ / / |/ _` | '_ \| '_ \| || |_
	// | |_) | | | |  _| |_   _| |  _| | | \ V /| | (_| | | | | (_) |__   _|
	// | .__/|_| |_|_|     |_|   |_| |_| |_|\_/ |_|\__,_|_| |_|\___/   |_|
	// |_|
	{
		fnv1ah64 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto pos = stop_words_phf.find(fnv1a(word));
			if (pos != phf::npos) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (phf + fnv1ah64)" << std::endl;
	}


	//        _      __ _       _        _     _      _________
	//  _ __ | |__  / _( )___  | |_ __ _| |__ | | ___|___ /___ \
	// | '_ \| '_ \| |_|// __| | __/ _` | '_ \| |/ _ \ |_ \ __) |
	// | |_) | | | |  _| \__ \ | || (_| | |_) | |  __/___) / __/
	// | .__/|_| |_|_|   |___/  \__\__,_|_.__/|_|\___|____/_____|
	// |_|
	{
		#include "tst-benchmark-stop_words-table32.h"
		hash_type fnv1a{};
		phf::fast_hasher<index_type::item_type> _hasher;
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto item = fnv1a(word);
			const auto& elem = _index[static_cast<std::size_t>(_hasher.hash(item, _displacement[item % displacement_size]) % index_size)];
			if (elem.item == item) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (phf's table32)" << std::endl;
	}


	//        _      __ _       _        _     _       __   _  _
	//  _ __ | |__  / _( )___  | |_ __ _| |__ | | ___ / /_ | || |
	// | '_ \| '_ \| |_|// __| | __/ _` | '_ \| |/ _ \ '_ \| || |_
	// | |_) | | | |  _| \__ \ | || (_| | |_) | |  __/ (_) |__   _|
	// | .__/|_| |_|_|   |___/  \__\__,_|_.__/|_|\___|\___/   |_|
	// |_|
	{
		#include "tst-benchmark-stop_words-table64.h"
		hash_type fnv1a{};
		phf::fast_hasher<index_type::item_type> _hasher;
		////
		std::size_t count = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto item = fnv1a(word);
			const auto& elem = _index[static_cast<std::size_t>(_hasher.hash(item, _displacement[item % displacement_size]) % index_size)];
			if (elem.item == item) {
				++count;
			}
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << " count: " << count << " duration: " << duration.count() << " ms (phf's table64)" << std::endl;
	}


	return 0;
}
