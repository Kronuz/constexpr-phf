/*
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words -I ./frozen/include ./tst-benchmark-stop_words.cc && gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words
*/

// #define DISABLE_PHF_FNV1AH32 1
// #define DISABLE_PHF_FNV1AH64 1
// #define DISABLE_SWITCH_PHF_FNV1AH32 1
// #define DISABLE_SWITCH_PHF_FNV1AH64 1
// #define DISABLE_GPREF 1
// #define DISABLE_FROZEN_UNORDERED_SET 1
// #define DISABLE_SWITCH_FNV1AH32 1
// #define DISABLE_SWITCH_FNV1AH64 1
// #define DISABLE_CTRIE 1
// #define DISABLE_UNORDERED_SET 1
// #define DISABLE_UNORDERED_MAP 1
// #define DISABLE_IF_ELSE_FNV1AH32 1
// #define DISABLE_IF_ELSE_FNV1AH64 1
// #define DISABLE_SET 1

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>

#include <string>
#include <vector>

#include "hashes.hh"
#include "phf.hh"

#include "tst-benchmark-stop_words.h"
#ifndef DISABLE_GPREF
#include "tst-benchmark-stop_words-gperf.h"  // gperf -ILC++ tst-benchmark-stop_words-gperf.in > tst-benchmark-stop_words-gperf.h
#endif
#ifndef DISABLE_FROZEN_UNORDERED_SET
#include <frozen/string.h>
#include <frozen/unordered_set.h>
#endif
#ifndef DISABLE_CTRIE
#include "ctrie.hh"
#endif
#ifndef DISABLE_UNORDERED_SET
#include <unordered_set>
#endif
#ifndef DISABLE_UNORDERED_MAP
#include <unordered_map>
#endif
#ifndef DISABLE_SET
#include <set>
#endif


int main() {
	////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> words{std::istream_iterator<std::string>(std::cin), {}};
	////////////////////////////////////////////////////////////////////////////
	std::cerr << "Finding stop words in a total of " << words.size() << " words..." << std::endl;

	/*        _      __  ____            _       _     ___________
	 *  _ __ | |__  / _|/ / _|_ ____   _/ | __ _| |__ |___ /___ \ \
	 * | '_ \| '_ \| |_| | |_| '_ \ \ / / |/ _` | '_ \  |_ \ __) | |
	 * | |_) | | | |  _| |  _| | | \ V /| | (_| | | | |___) / __/| |
	 * | .__/|_| |_|_| | |_| |_| |_|\_/ |_|\__,_|_| |_|____/_____| |
	 * |_|              \_\                                     /_/
	 */
	#ifndef DISABLE_PHF_FNV1AH32
	{
		fnv1ah32 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto pos = stop_words_phf.find(fnv1a(word));
			if (pos != phf::npos) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [phf(fnv1ah32)]" << std::endl;
	}
	#endif


	/*        _      __  ____            _       _      __   _  _ __
	 *  _ __ | |__  / _|/ / _|_ ____   _/ | __ _| |__  / /_ | || |\ \
	 * | '_ \| '_ \| |_| | |_| '_ \ \ / / |/ _` | '_ \| '_ \| || |_| |
	 * | |_) | | | |  _| |  _| | | \ V /| | (_| | | | | (_) |__   _| |
	 * | .__/|_| |_|_| | |_| |_| |_|\_/ |_|\__,_|_| |_|\___/   |_| | |
	 * |_|              \_\                                       /_/
	 */
	#ifndef DISABLE_PHF_FNV1AH64
	{
		fnv1ah64 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto pos = stop_words_phf.find(fnv1a(word));
			if (pos != phf::npos) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [phf(fnv1ah64)]" << std::endl;
	}
	#endif


	/*               _ _       _      __      _      __  ____            _       _     _____________
	 *  _____      _(_) |_ ___| |__  / /_ __ | |__  / _|/ / _|_ ____   _/ | __ _| |__ |___ /___ \ \ \
	 * / __\ \ /\ / / | __/ __| '_ \| || '_ \| '_ \| |_| | |_| '_ \ \ / / |/ _` | '_ \  |_ \ __) | | |
	 * \__ \\ V  V /| | || (__| | | | || |_) | | | |  _| |  _| | | \ V /| | (_| | | | |___) / __/| | |
	 * |___/ \_/\_/ |_|\__\___|_| |_| || .__/|_| |_|_| | |_| |_| |_|\_/ |_|\__,_|_| |_|____/_____| | |
	 *                               \_\_|              \_\                                     /_/_/
	 */
	#ifndef DISABLE_SWITCH_PHF_FNV1AH32
	{
		fnv1ah32 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			switch (stop_words_phf.find(fnv1a(word))) {
				#define STRING(option, name) case stop_words_phf.find(fnv1a(option)):
				STOP_WORDS_STRINGS(stop_words)
				#undef STRING
				++stopped;
				break;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [switch(phf(fnv1ah32))]" << std::endl;
	}
	#endif


	/*               _ _       _      __      _      __  ____            _       _      __   _  _ ____
	 *  _____      _(_) |_ ___| |__  / /_ __ | |__  / _|/ / _|_ ____   _/ | __ _| |__  / /_ | || |\ \ \
	 * / __\ \ /\ / / | __/ __| '_ \| || '_ \| '_ \| |_| | |_| '_ \ \ / / |/ _` | '_ \| '_ \| || |_| | |
	 * \__ \\ V  V /| | || (__| | | | || |_) | | | |  _| |  _| | | \ V /| | (_| | | | | (_) |__   _| | |
	 * |___/ \_/\_/ |_|\__\___|_| |_| || .__/|_| |_|_| | |_| |_| |_|\_/ |_|\__,_|_| |_|\___/   |_| | | |
	 *                               \_\_|              \_\                                       /_/_/
	 */
	#ifndef DISABLE_SWITCH_PHF_FNV1AH64
	{
		fnv1ah64 fnv1a{};
		constexpr auto stop_words_phf = phf::make_phf({
			#define STRING(option, name) fnv1a(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			switch (stop_words_phf.find(fnv1a(word))) {
				#define STRING(option, name) case stop_words_phf.find(fnv1a(option)):
				STOP_WORDS_STRINGS(stop_words)
				#undef STRING
				++stopped;
				break;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [switch(phf(fnv1ah64))]" << std::endl;
	}
	#endif


	/*                         __
	 *   __ _ _ __   ___ _ __ / _|
	 *  / _` | '_ \ / _ \ '__| |_
	 * | (_| | |_) |  __/ |  |  _|
	 *  \__, | .__/ \___|_|  |_|
	 *  |___/|_|
	 */
	#ifndef DISABLE_GPREF
	{
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			if (Perfect_Hash::in_word_set(word.data(), word.size())) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [gperf]" << std::endl;
	}
	#endif


	/*   __                                                      _                   _              _
	 *  / _|_ __ ___ _______ _ __  _ _ _   _ _ __   ___  _ __ __| | ___ _ __ ___  __| |    ___  ___| |_
	 * | |_| '__/ _ \_  / _ \ '_ \(_|_) | | | '_ \ / _ \| '__/ _` |/ _ \ '__/ _ \/ _` |   / __|/ _ \ __|
	 * |  _| | | (_) / /  __/ | | |_ _| |_| | | | | (_) | | | (_| |  __/ | |  __/ (_| |   \__ \  __/ |_
	 * |_| |_|  \___/___\___|_| |_(_|_)\__,_|_| |_|\___/|_|  \__,_|\___|_|  \___|\__,_|___|___/\___|\__|
	 *                                                                               |_____|
	 */
	#ifndef DISABLE_FROZEN_UNORDERED_SET
	{
		auto stop_words_frozen_unordered_set = frozen::make_unordered_set({
			#define STRING(option, name) frozen::string(option),
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		});
		auto it_end = stop_words_frozen_unordered_set.end();
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_frozen_unordered_set.find(frozen::string(word.data(), word.size()));
			if (it != it_end) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [frozen::unordered_set]" << std::endl;
	}
	#endif


	/*               _ _       _      ____            _       _     ___________
	 *  _____      _(_) |_ ___| |__  / / _|_ ____   _/ | __ _| |__ |___ /___ \ \
	 * / __\ \ /\ / / | __/ __| '_ \| | |_| '_ \ \ / / |/ _` | '_ \  |_ \ __) | |
	 * \__ \\ V  V /| | || (__| | | | |  _| | | \ V /| | (_| | | | |___) / __/| |
	 * |___/ \_/\_/ |_|\__\___|_| |_| |_| |_| |_|\_/ |_|\__,_|_| |_|____/_____| |
	 *                               \_\                                     /_/
	 */
	#ifndef DISABLE_SWITCH_FNV1AH32
	{
		fnv1ah32 fnv1a{};
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			switch (fnv1a(word)) {
				#define STRING(option, name) case fnv1a(option): ++stopped; break;
				STOP_WORDS_STRINGS(stop_words)
				#undef STRING
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [switch(fnv1ah32)]" << std::endl;
	}
	#endif


	/*               _ _       _      ____            _       _      __   _  _ __
	 *  _____      _(_) |_ ___| |__  / / _|_ ____   _/ | __ _| |__  / /_ | || |\ \
	 * / __\ \ /\ / / | __/ __| '_ \| | |_| '_ \ \ / / |/ _` | '_ \| '_ \| || |_| |
	 * \__ \\ V  V /| | || (__| | | | |  _| | | \ V /| | (_| | | | | (_) |__   _| |
	 * |___/ \_/\_/ |_|\__\___|_| |_| |_| |_| |_|\_/ |_|\__,_|_| |_|\___/   |_| | |
	 *                               \_\                                       /_/
	 */
	#ifndef DISABLE_SWITCH_FNV1AH64
	{
		fnv1ah64 fnv1a{};
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			switch (fnv1a(word)) {
				#define STRING(option, name) case fnv1a(option): ++stopped; break;
				STOP_WORDS_STRINGS(stop_words)
				#undef STRING
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [switch(fnv1ah64)]" << std::endl;
	}
	#endif


	/*       _        _
	 *   ___| |_ _ __(_) ___
	 *  / __| __| '__| |/ _ \
	 * | (__| |_| |  | |  __/
	 *  \___|\__|_|  |_|\___|
	 */
	#ifndef DISABLE_CTRIE
	{
		constexpr auto stop_words_mph = ctrie::build(
			#define STRING(option, name) option##_cword,
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
			""_cword
		);
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto pos = stop_words_mph.find(word);
			if (pos != ctrie::npos) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [ctrie]" << std::endl;
	}
	#endif


	/*                            _                   _              _
	 *  _   _ _ __   ___  _ __ __| | ___ _ __ ___  __| |    ___  ___| |_
	 * | | | | '_ \ / _ \| '__/ _` |/ _ \ '__/ _ \/ _` |   / __|/ _ \ __|
	 * | |_| | | | | (_) | | | (_| |  __/ | |  __/ (_| |   \__ \  __/ |_
	 *  \__,_|_| |_|\___/|_|  \__,_|\___|_|  \___|\__,_|___|___/\___|\__|
	 *                                                |_____|
	 */
	#ifndef DISABLE_UNORDERED_SET
	{
		std::unordered_set<std::string> stop_words_set{
			#define STRING(option, name) option,
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		};
		auto it_end = stop_words_set.end();
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_set.find(word);
			if (it != it_end) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [unordered_set]" << std::endl;
	}
	#endif


	/*                            _                   _
	 *  _   _ _ __   ___  _ __ __| | ___ _ __ ___  __| |    _ __ ___   __ _ _ __
	 * | | | | '_ \ / _ \| '__/ _` |/ _ \ '__/ _ \/ _` |   | '_ ` _ \ / _` | '_ \
	 * | |_| | | | | (_) | | | (_| |  __/ | |  __/ (_| |   | | | | | | (_| | |_) |
	 *  \__,_|_| |_|\___/|_|  \__,_|\___|_|  \___|\__,_|___|_| |_| |_|\__,_| .__/
	 *                                                |_____|              |_|
	 */
	#ifndef DISABLE_UNORDERED_MAP
	{
		std::unordered_map<std::string, bool> stop_words_set{
			#define STRING(option, name) { option, true },
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		};
		auto it_end = stop_words_set.end();
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_set.find(word);
			if (it != it_end) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [unordered_map]" << std::endl;
	}
	#endif


	/*  _  __   __   _           ____            _       _     ___________
	 * (_)/ _| / /__| |___  ___ / / _|_ ____   _/ | __ _| |__ |___ /___ \ \
	 * | | |_ / / _ \ / __|/ _ \ | |_| '_ \ \ / / |/ _` | '_ \  |_ \ __) | |
	 * | |  _/ /  __/ \__ \  __/ |  _| | | \ V /| | (_| | | | |___) / __/| |
	 * |_|_|/_/ \___|_|___/\___| |_| |_| |_|\_/ |_|\__,_|_| |_|____/_____| |
	 *                          \_\                                     /_/
	 */
	#ifndef DISABLE_IF_ELSE_FNV1AH32
	{
		fnv1ah32 fnv1a{};
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto word_hash = fnv1a(word);
			#define STRING(option, name) if (word_hash == fnv1a(option)) ++stopped; else
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
			void(0);
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [if/else(fnv1ah32)]" << std::endl;
	}
	#endif


	/*  _  __   __   _           ____            _       _      __   _  _ __
	 * (_)/ _| / /__| |___  ___ / / _|_ ____   _/ | __ _| |__  / /_ | || |\ \
	 * | | |_ / / _ \ / __|/ _ \ | |_| '_ \ \ / / |/ _` | '_ \| '_ \| || |_| |
	 * | |  _/ /  __/ \__ \  __/ |  _| | | \ V /| | (_| | | | | (_) |__   _| |
	 * |_|_|/_/ \___|_|___/\___| |_| |_| |_|\_/ |_|\__,_|_| |_|\___/   |_| | |
	 *                          \_\                                       /_/
	 */
	#ifndef DISABLE_IF_ELSE_FNV1AH64
	{
		fnv1ah64 fnv1a{};
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto word_hash = fnv1a(word);
			#define STRING(option, name) if (word_hash == fnv1a(option)) ++stopped; else
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
			void(0);
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [if/else(fnv1ah64)]" << std::endl;
	}
	#endif


	/*           _
	 *  ___  ___| |_
	 * / __|/ _ \ __|
	 * \__ \  __/ |_
	 * |___/\___|\__|
	 */
	#ifndef DISABLE_SET
	{
		std::set<std::string> stop_words_set{
			#define STRING(option, name) option,
			STOP_WORDS_STRINGS(stop_words)
			#undef STRING
		};
		auto it_end = stop_words_set.end();
		////
		std::size_t total = 0;
		std::size_t stopped = 0;
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < 100; ++i)
		for (const auto& word : words) {
			auto it = stop_words_set.find(word);
			if (it != it_end) {
				++stopped;
			}
			++total;
		}
		auto stop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = (stop - start);
		std::cerr << "  stopped " << stopped << "/" << total << " in " << duration.count() << " ms [set]" << std::endl;
	}
	#endif


	return 0;
}
