// A runnable tour of constexpr-phf.
//
// Build (when this repo is the top-level project):
//   cmake -B build && cmake --build build && ./build/phf_demo
//
// The one idea worth taking away: the whole hash table is built at COMPILE
// time. For a fixed set of keys known to the compiler, make_phf() materializes
// a collision-free lookup table as constexpr data, so at runtime a lookup is a
// couple of multiplies, a modulo, and two array reads, no probing and no heap.
// The library hashes integers, so the canonical trick for a keyword set is to
// hash each string to an integer first (here with a constexpr FNV-1a) and build
// the phf over those integers. This demo builds such a table over a handful of
// reserved keywords, proves at() is a perfect index with static_assert (so the
// proof runs in the compiler, not at runtime), and then dispatches a few
// member and non-member lookups through a parallel table.
#include <cstdint>
#include <cstdio>
#include <string>
#include <string_view>

#include "phf.hh"

// A constexpr FNV-1a over a string_view. The phf hashes integers, so we fold
// each keyword down to a 32-bit integer the compiler can see at build time.
constexpr std::uint32_t fnv1a(std::string_view s) {
	std::uint32_t h = 2166136261u;
	for (char c : s) {
		h ^= static_cast<std::uint8_t>(c);
		h *= 16777619u;
	}
	return h;
}

// The fixed keyword set. Order matters: at(key) returns the key's INDEX in this
// array, so a parallel array (here, a category per keyword) lines up by index.
constexpr std::string_view keywords[] = {
	"if", "else", "for", "while", "return", "break", "continue", "switch",
};
constexpr const char* categories[] = {
	"conditional", "conditional", "loop", "loop", "flow", "flow", "flow", "branch",
};

// The integer keys the phf is actually built over: one FNV-1a hash per keyword.
constexpr std::uint32_t keys[] = {
	fnv1a(keywords[0]), fnv1a(keywords[1]), fnv1a(keywords[2]), fnv1a(keywords[3]),
	fnv1a(keywords[4]), fnv1a(keywords[5]), fnv1a(keywords[6]), fnv1a(keywords[7]),
};

// Built ONCE, at compile time. The table is constexpr data baked into the binary.
constexpr auto table = phf::make_phf(keys);

// Compile-time proofs: the table is real constexpr data and at() is a perfect,
// in-range index. If any of these failed the program would not compile.
static_assert(table.size() == 8, "eight keywords");
static_assert(!table.empty(), "not empty");
static_assert(table.at(fnv1a("return")) < table.size(), "at() is in range, at compile time");
static_assert(table.find(fnv1a("nonsense")) == phf::npos, "non-member resolves to npos");

static void rule(const char* title) {
	std::printf("\n\033[1m-- %s --\033[0m\n", title);
}

// Look a word up through the perfect hash. count() checks membership; on a hit,
// at() gives the index into the parallel category table.
static void lookup(std::string_view word) {
	std::uint32_t key = fnv1a(word);
	if (table.count(key)) {
		std::size_t i = table.at(key);
		std::printf("  %-10s -> HIT   key 0x%08x  index %zu  category \"%s\"\n",
			std::string(word).c_str(), key, i, categories[i]);
	} else {
		std::printf("  %-10s -> MISS  key 0x%08x  (not a keyword, find()=npos)\n",
			std::string(word).c_str(), key);
	}
}

int main() {
	std::puts("constexpr-phf demo  (a compile-time keyword table, keys are FNV-1a hashes)");

	// --- 1. the table is compile-time data -----------------------------------
	rule("make_phf() built the table at compile time");
	std::printf("  size()     = %zu keys\n", table.size());
	std::printf("  capacity() = %zu  (internal index-table width, >= size)\n", table.capacity());
	std::printf("  empty()    = %s\n", table.empty() ? "true" : "false");
	std::puts("  (the static_asserts above already proved this in the compiler)");

	// --- 2. the perfect index: each key maps to a unique slot ----------------
	rule("at() is a collision-free index in [0, size), one slot per key");
	for (auto& w : keywords) {
		std::printf("  %-10s key 0x%08x  ->  index %zu\n",
			std::string(w).c_str(), fnv1a(w), table.at(fnv1a(w)));
	}
	std::puts("  (no two keywords share an index: that is what \"perfect\" means)");

	// --- 3. hit vs miss, dispatched through the parallel table ---------------
	rule("count()/at() lookups: members hit, non-members miss");
	lookup("for");        // member
	lookup("switch");     // member
	lookup("return");     // member
	lookup("foreach");    // non-member, but close to "for"
	lookup("function");   // non-member
	lookup("if ");        // non-member: trailing space, a different hash than "if"

	// --- 4. find() vs lookup(): the membership-checked vs raw paths ----------
	rule("find() returns npos for non-members; lookup() does NOT check membership");
	std::printf("  find(\"while\")    = %zu   (a real index)\n", table.find(fnv1a("while")));
	std::printf("  find(\"whilst\")   = %s   (not a keyword)\n",
		table.find(fnv1a("whilst")) == phf::npos ? "npos" : "??");
	std::size_t raw = table.lookup(fnv1a("whilst"));
	std::printf("  lookup(\"whilst\") = %s   (raw slot contents, NOT membership-checked)\n",
		raw == phf::npos ? "npos" : "some index");
	std::puts("  (always gate on count()/find(); lookup() trusts you already verified membership)");

	std::puts("\ndone.");
	return 0;
}
