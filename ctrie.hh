/*
 * Copyright (C) 2019 German Mendez Bravo (Kronuz)
 *
 * Based on https://github.com/heyterrance/ctrie
 *
 */

#ifndef CTRIE_HH
#define CTRIE_HH

#include <limits>
#include <string>
#include <string_view>
#include <type_traits>

namespace ctrie {
	static constexpr size_t npos = std::numeric_limits<size_t>::max();

	namespace detail {
		template <char... Letters>
		struct Word {};

		template <char C, typename... Tries>
		struct Find;

		template <size_t V, char C, typename... Children>
		struct Trie : std::integral_constant<char, C> {
			constexpr size_t find(const char* word) const;
			constexpr size_t find(const char* begin, const char* end) const;
			constexpr size_t find(const char* word, size_t size) const {
				return find(word, word + size);
			}
			template <typename S, typename std::enable_if_t<std::is_same<std::string, std::decay_t<S>>::value, int> = 0>
			constexpr size_t find(S&& word) const {
				return find(word.c_str());
			}
			template <typename S, typename std::enable_if_t<std::is_same<std::string_view, std::decay_t<S>>::value, int> = 0>
			constexpr size_t find(S&& word) const {
				return find(word.begin(), word.end());
			}
		};

		template <char C>
		struct Find<C> {
			using type = std::false_type;
		};

		template <char C, typename TrieT, typename... Tries>
		struct Find<C, TrieT, Tries...> : Find<C, Tries...> {};

		template <size_t V, char C, typename... Cs, typename... Tries>
		struct Find<C, Trie<V, C, Cs...>, Tries...> {
			using type = std::true_type;
		};

		template <typename Parent, typename Child>
		struct Adopt;

		template <size_t __, char _, typename Child, typename... Children>
		struct Adopt<Trie<__, _, Children...>, Child> {
			using type = Trie<__, _, Child, Children...>;
		};

		template <char C, typename Trie>
		struct Remove;

		template <char C, size_t __, char _, typename Child, typename... Children>
		struct Remove<C, Trie<__, _, Child, Children...>> :
			Remove<C, Trie<__, _, Children..., Child>> {};

		template <size_t V, char C, size_t __, char _, typename... Cs, typename... Children>
		struct Remove<
			C,
			Trie<__, _, Trie<V, C, Cs...>, Children...>
		> {
			using parent = Trie<__, _, Children...>;
			using removed = Trie<V, C, Cs...>;
		};

		template <size_t V, typename Word, typename...>
		struct Insert;

		template <size_t V, char L, char... Ls, size_t __, char _, typename... Children>
		struct Insert<V, Word<L, Ls...>, Trie<__, _, Children...>> :
			Insert<
				V,
				Word<L, Ls...>,
				typename Find<L, Children...>::type,
				Trie<__, _, Children...>
			> {};

		template <size_t V, char L, char... Ls, size_t __, char _, typename... Children>
		struct Insert<V, Word<L, Ls...>, std::true_type, Trie<__, _, Children...>> {
		private:
			using remove_result = Remove<L, Trie<__, _, Children...>>;
			using parent = typename remove_result::parent;
			using removed = typename remove_result::removed;

			using child = typename Insert<V, Word<Ls...>, removed>::type;

		public:
			using type = typename Adopt<parent, child>::type;
		};

		template <size_t V, typename TrieT>
		struct Insert<V, Word<>, TrieT> {
			using type = TrieT;
		};

		template <size_t V, char L, char... Ls, size_t __, char _, typename... Children>
		struct Insert<V, Word<L, Ls...>, std::false_type, Trie<__, _, Children...>> :
			Adopt<
				Trie<__, _, Children...>,
				typename Insert<V, Word<Ls...>, Trie<V, L>>::type
			> {};

		template <size_t V, typename TrieT, typename... Words>
		struct Build {
			using type = TrieT;
		};

		template <size_t V, typename TrieT, typename W, typename... Words>
		struct Build<V, TrieT, W, Words...> :
			Build<
				V + 1,
				typename Insert<V, W, TrieT>::type,
				Words...
			> {};

		template <typename... Children>
		struct Pack {};

		constexpr
		size_t find(Pack<>, const char*, const char*) {
			return npos;
		}

		template <typename Child, typename... Children>
		constexpr
		size_t find(Pack<Child, Children...>, const char* begin, const char* end) {
			auto found = find(Child{}, begin, end);
			if (found != npos) {
				return found;
			}
			return find(Pack<Children...>{}, begin, end);
		}

		template <size_t V, char C, typename... Children>
		constexpr
		size_t find(Trie<V, C, Children...>, const char* begin, const char* end) {
			if (begin != end && *begin == C) {
				return find(Pack<Children...>{}, ++begin, end);
			}
			return npos;
		}

		template <typename Child, typename... Children>
		constexpr
		size_t find(Trie<0, '\0', Child, Children...>, const char* begin, const char* end) {
			// Root node.
			return find(Pack<Child, Children...>{}, begin, end);
		}

		template <size_t V>
		constexpr
		size_t find(Trie<V, '\0'>, const char* begin, const char* end) {
			// Leaf node.
			if (begin == end) {
				return V;
			}
			return npos;
		}

		constexpr
		size_t find(Pack<>, const char*) {
			return npos;
		}

		template <typename Child, typename... Children>
		constexpr
		size_t find(Pack<Child, Children...>, const char* word) {
			auto found = find(Child{}, word);
			if (found != npos) {
				return found;
			}
			return find(Pack<Children...>{}, word);
		}

		template <size_t V, char C, typename... Children>
		constexpr
		size_t find(Trie<V, C, Children...>, const char* word) {
			if (*word == C) {
				return find(Pack<Children...>{}, ++word);
			}
			return npos;
		}

		template <typename Child, typename... Children>
		constexpr
		size_t find(Trie<0, '\0', Child, Children...>, const char* word) {
			// Root node.
			return find(Pack<Child, Children...>{}, word);
		}

		template <size_t V>
		constexpr
		size_t find(Trie<V, '\0'>, const char* word) {
			// Leaf node.
			if (*word == '\0') {
				return V;
			}
			return npos;
		}

		template <size_t V, char C, typename... Children>
		constexpr
		size_t Trie<V, C, Children...>::find(const char* begin, const char* end) const {
			return detail::find(*this, begin, end);
		}

		template <size_t V, char C, typename... Children>
		constexpr
		size_t Trie<V, C, Children...>::find(const char* word) const {
			return detail::find(*this, word);
		}
	} // namespace detail

	template <typename... Words>
	constexpr
	typename detail::Build<0, detail::Trie<0, '\0'>, Words...>::type build(Words...) { return {}; }
} // namespace ctrie

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-string-literal-operator-template"
template <typename CharT, CharT... Letters>
constexpr
ctrie::detail::Word<Letters..., '\0'> operator""_cword() { return {}; }
#pragma clang diagnostic push

#endif // CTRIE_HH
