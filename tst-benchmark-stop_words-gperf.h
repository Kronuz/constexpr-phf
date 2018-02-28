/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf -ILC++ tst-benchmark-stop_words-gperf.in  */
/* Computed positions: -k'1-6,9' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#include <string.h>

#define TOTAL_KEYWORDS 570
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 13
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 3752
/* maximum key range = 3752, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const char *in_word_set (const char *str, size_t len);
};

inline unsigned int
Perfect_Hash::hash (const char *str, size_t len)
{
  static unsigned short asso_values[] =
    {
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,  195,
      3753,  880, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753,   85,  590,   80,
       730,   25,  915,    5,  530,   60,   15,  465,  940,  426,
        10,  105,  200,   20,  210,    0,   30,  320,  660,   50,
       900,  930,   55,  490,    0, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753,
      3753, 3753, 3753, 3753, 3753, 3753, 3753, 3753
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[8])];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
        hval += asso_values[static_cast<unsigned char>(str[5])];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[static_cast<unsigned char>(str[4])];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[static_cast<unsigned char>(str[3])];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[static_cast<unsigned char>(str[2]+2)];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[static_cast<unsigned char>(str[1]+2)];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0])];
        break;
    }
  return hval;
}

const char *
Perfect_Hash::in_word_set (const char *str, size_t len)
{
  static const char * wordlist[] =
    {
      "",
      "s",
      "", "", "", "",
      "g",
      "", "", "", "",
      "n",
      "",
      "see",
      "", "",
      "j",
      "", "", "", "",
      "q",
      "so",
      "she",
      "seen",
      "",
      "e",
      "go",
      "", "", "",
      "t",
      "no",
      "",
      "goes",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "th",
      "", "", "",
      "w",
      "to",
      "the",
      "soon",
      "",
      "z",
      "we",
      "", "", "",
      "i",
      "",
      "nor",
      "then",
      "", "",
      "ie",
      "", "", "", "", "",
      "too",
      "", "", "", "",
      "que",
      "",
      "these",
      "c",
      "ex",
      "",
      "when",
      "",
      "a",
      "eg",
      "who",
      "",
      "noone",
      "seeing",
      "", "", "",
      "those",
      "", "", "",
      "thus",
      "", "",
      "co",
      "",
      "next",
      "",
      "o",
      "",
      "all",
      "sure",
      "", "", "", "",
      "were",
      "whose",
      "", "", "", "", "", "",
      "oh",
      "are",
      "", "", "", "", "", "",
      "three",
      "", "", "", "",
      "along",
      "",
      "or",
      "",
      "than",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "some",
      "alone",
      "", "", "",
      "that",
      "thats",
      "", "", "",
      "greetings",
      "", "", "", "", "", "",
      "thence",
      "", "", "", "", "", "", "",
      "what",
      "", "", "", "", "", "", "", "",
      "our",
      "ours",
      "",
      "whence",
      "am",
      "", "", "", "", "", "",
      "zero",
      "",
      "p",
      "", "", "", "", "", "",
      "com",
      "", "",
      "r",
      "", "",
      "same",
      "", "",
      "re",
      "", "", "", "",
      "changes",
      "",
      "name",
      "", "", "", "", "",
      "among",
      "",
      "amongst",
      "non",
      "come",
      "comes",
      "", "",
      "per",
      "sent",
      "cause",
      "causes",
      "", "", "", "", "", "",
      "sometime",
      "sometimes",
      "",
      "across",
      "", "",
      "gone",
      "", "", "", "",
      "none",
      "", "",
      "in",
      "sup",
      "plus",
      "allow",
      "allows",
      "", "", "", "", "",
      "someone",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "who's",
      "",
      "an",
      "inc",
      "went",
      "there",
      "theres",
      "", "",
      "came",
      "", "",
      "certain",
      "", "",
      "again",
      "",
      "against",
      "", "", "", "",
      "on",
      "",
      "near",
      "where",
      "", "",
      "one",
      "ones",
      "", "", "", "", "", "",
      "u",
      "weren't",
      "", "",
      "their",
      "theirs",
      "", "", "", "",
      "please",
      "", "", "", "", "", "", "", "", "",
      "almost",
      "", "", "", "", "", "", "", "", "",
      "",
      "therein",
      "", "", "",
      "that's",
      "", "",
      "once",
      "",
      "aren't",
      "",
      "can",
      "want",
      "wants",
      "except",
      "consequently",
      "", "", "", "",
      "wherein",
      "", "", "",
      "what's",
      "", "", "", "", "",
      "is",
      "",
      "else",
      "", "", "",
      "corresponding",
      "", "",
      "course",
      "", "",
      "cant",
      "", "",
      "whereas",
      "",
      "thru",
      "", "", "", "", "",
      "thereafter",
      "",
      "as",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "just",
      "", "", "", "", "",
      "whereafter",
      "",
      "m",
      "", "", "", "", "",
      "me",
      "", "", "", "", "", "",
      "seem",
      "seems",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "was",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "k",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "them",
      "",
      "contain",
      "contains",
      "", "", "",
      "there's",
      "", "", "", "", "", "", "",
      "containing",
      "", "", "", "",
      "won't",
      "", "", "", "",
      "more",
      "",
      "where's",
      "", "",
      "going",
      "cannot",
      "through",
      "seeming",
      "this",
      "whom",
      "", "", "", "", "", "",
      "un",
      "six",
      "also",
      "mean",
      "",
      "serious",
      "", "", "",
      "h",
      "up",
      "ok",
      "", "",
      "themselves",
      "he",
      "",
      "took",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "try",
      "",
      "tries",
      "", "",
      "why",
      "", "",
      "unless",
      "", "",
      "upon",
      "take",
      "", "",
      "her",
      "hers",
      "", "", "",
      "say",
      "says",
      "particular",
      "taken",
      "particularly",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "can't",
      "b",
      "if",
      "",
      "here",
      "quite",
      "",
      "be",
      "",
      "uucp",
      "", "", "", "", "",
      "thank",
      "thanks",
      "", "",
      "such",
      "", "", "", "",
      "been",
      "", "", "", "", "",
      "apart",
      "", "",
      "way",
      "thereupon",
      "", "", "", "", "", "",
      "trying",
      "", "", "",
      "concerning",
      "",
      "of",
      "", "", "", "",
      "us",
      "",
      "whereupon",
      "", "", "",
      "use",
      "uses",
      "",
      "saying",
      "", "", "", "", "", "", "", "", "",
      "v",
      "whether",
      "",
      "each",
      "",
      "herein",
      "ignored",
      "", "", "", "", "",
      "get",
      "gets",
      "", "", "", "",
      "keep",
      "keeps",
      "", "",
      "welcome",
      "", "", "",
      "et",
      "got",
      "", "",
      "wasn't",
      "",
      "not",
      "", "", "", "", "", "",
      "inner",
      "", "",
      "together",
      "nine",
      "",
      "selves",
      "",
      "thorough",
      "", "", "", "",
      "etc",
      "kept",
      "", "", "", "", "", "", "",
      "it",
      "",
      "something",
      "", "",
      "instead",
      "", "", "",
      "d",
      "", "", "", "", "", "",
      "somewhat",
      "know",
      "knows",
      "", "", "", "", "", "",
      "at",
      "",
      "help",
      "known",
      "",
      "do",
      "",
      "need",
      "needs",
      "gotten",
      "", "",
      "does",
      "", "", "", "",
      "somewhere",
      "below",
      "", "", "", "", "", "", "",
      "whenever",
      "",
      "since",
      "",
      "getting",
      "any",
      "",
      "ought",
      "", "",
      "sub",
      "", "", "", "", "", "", "",
      "here's",
      "somehow",
      "", "", "", "", "", "", "",
      "most",
      "",
      "whoever",
      "", "", "", "", "", "", "",
      "isn't",
      "", "", "", "", "", "", "",
      "out",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "must",
      "appear",
      "", "",
      "ask",
      "throughout",
      "", "", "", "", "", "", "", "", "",
      "hence",
      "", "", "", "", "", "", "",
      "somebody",
      "able",
      "", "", "", "", "",
      "appreciate",
      "", "",
      "sensible",
      "", "", "", "",
      "whatever",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "second",
      "thereby",
      "secondly",
      "", "", "", "", "", "", "",
      "during",
      "", "", "", "", "",
      "another",
      "", "", "",
      "x",
      "whereby",
      "", "", "", "", "", "", "", "", "",
      "asking",
      "", "", "",
      "f",
      "",
      "my",
      "", "",
      "anyone",
      "qv",
      "", "", "",
      "though",
      "nd",
      "", "", "",
      "y",
      "",
      "has",
      "self",
      "", "", "", "", "", "",
      "l",
      "", "",
      "even",
      "seven",
      "", "",
      "new",
      "best",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "now",
      "", "", "",
      "doesn't",
      "for",
      "",
      "tends",
      "",
      "already",
      "wherever",
      "", "", "", "", "",
      "done",
      "ain't",
      "",
      "vs",
      "two",
      "they",
      "", "", "", "",
      "tell",
      "think",
      "", "",
      "edu",
      "elsewhere",
      "", "",
      "hi",
      "",
      "may",
      "", "", "",
      "you",
      "necessary",
      "associated",
      "", "", "",
      "well",
      "", "", "",
      "saw",
      "", "", "", "", "", "",
      "other",
      "others",
      "", "", "", "", "", "",
      "far",
      "into",
      "", "",
      "because",
      "old",
      "",
      "much",
      "", "", "", "",
      "thanx",
      "", "",
      "its",
      "", "", "", "",
      "i'm",
      "", "", "", "", "", "",
      "whole",
      "",
      "perhaps",
      "", "",
      "least",
      "",
      "happens",
      "", "", "", "", "", "", "", "", "",
      "neither",
      "",
      "onto",
      "", "", "", "", "",
      "being",
      "",
      "by",
      "", "", "", "", "",
      "unlikely",
      "", "", "", "", "",
      "inasmuch",
      "", "", "",
      "consider",
      "otherwise",
      "value",
      "", "",
      "him",
      "", "",
      "enough",
      "", "", "", "", "", "", "", "",
      "eight",
      "appropriate",
      "",
      "hereupon",
      "immediate",
      "", "",
      "whither",
      "", "",
      "using",
      "",
      "rd",
      "viz",
      "", "",
      "placed",
      "", "", "",
      "meanwhile",
      "", "", "", "", "", "", "", "",
      "ever",
      "which",
      "", "", "", "", "", "", "", "", "",
      "never",
      "", "", "",
      "ourselves",
      "",
      "considering",
      "became",
      "", "", "", "", "",
      "off",
      "", "",
      "hasn't",
      "", "", "",
      "we're",
      "", "", "", "",
      "don't",
      "",
      "become",
      "becomes",
      "",
      "c'mon",
      "", "",
      "entirely",
      "",
      "about",
      "", "", "",
      "according",
      "sorry",
      "accordingly",
      "seemed",
      "possible",
      "four",
      "",
      "around",
      "",
      "and",
      "", "", "", "",
      "via",
      "", "", "", "", "",
      "your",
      "yours",
      "",
      "exactly",
      "",
      "becoming",
      "", "", "", "",
      "over",
      "", "", "", "",
      "certainly",
      "", "",
      "several",
      "t's",
      "therefore",
      "doing",
      "", "",
      "own",
      "", "",
      "wonder",
      "",
      "yourself",
      "", "", "", "", "",
      "only",
      "", "", "", "", "", "", "", "",
      "yes",
      "", "", "",
      "various",
      "", "", "", "", "", "",
      "less",
      "yourselves",
      "", "", "",
      "moreover",
      "", "",
      "specify",
      "",
      "said",
      "", "", "",
      "c's",
      "",
      "tried",
      "", "",
      "a's",
      "unto",
      "specifying",
      "", "", "", "", "", "",
      "nothing",
      "",
      "lest",
      "right",
      "", "",
      "but",
      "", "", "",
      "regards",
      "", "",
      "regardless",
      "", "", "",
      "regarding",
      "", "", "",
      "his",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "often",
      "",
      "clearly",
      "", "", "", "", "", "",
      "currently",
      "", "", "", "", "",
      "relatively",
      "",
      "despite",
      "", "", "", "",
      "believe",
      "", "",
      "reasonably",
      "",
      "between",
      "", "", "", "", "", "",
      "wish",
      "", "", "", "",
      "last",
      "", "", "", "",
      "used",
      "", "", "", "", "", "", "", "",
      "anywhere",
      "", "", "",
      "they're",
      "", "",
      "from",
      "", "", "", "",
      "gives",
      "", "",
      "anything",
      "", "", "", "",
      "indicate",
      "indicates",
      "given",
      "", "", "", "", "",
      "behind",
      "", "",
      "he's",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "you're",
      "", "", "", "", "", "", "", "",
      "first",
      "", "", "",
      "look",
      "looks",
      "", "", "", "",
      "third",
      "", "", "",
      "seriously",
      "", "", "", "", "", "",
      "anyhow",
      "", "",
      "will",
      "",
      "before",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "how",
      "",
      "beforehand",
      "", "", "", "", "", "", "",
      "unfortunately",
      "", "", "", "", "", "",
      "while",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "respectively",
      "", "",
      "after",
      "might",
      "", "",
      "normally",
      "", "",
      "looking",
      "probably",
      "",
      "above",
      "better",
      "",
      "had",
      "",
      "forth",
      "", "", "", "",
      "twice",
      "",
      "herself",
      "",
      "have",
      "", "",
      "willing",
      "", "",
      "okay",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "further",
      "", "", "",
      "having",
      "", "", "",
      "hello",
      "", "",
      "yet",
      "", "", "", "", "",
      "it's",
      "", "", "",
      "let",
      "", "", "",
      "outside",
      "", "", "",
      "maybe",
      "", "", "", "", "", "", "", "",
      "we've",
      "", "", "",
      "very",
      "aside",
      "",
      "former",
      "",
      "formerly",
      "", "", "", "", "",
      "many",
      "", "", "", "", "", "", "", "", "",
      "thoroughly",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "we'd",
      "especially",
      "", "", "", "",
      "under",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "insofar",
      "",
      "down",
      "",
      "furthermore",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "provides",
      "with",
      "", "", "", "", "", "", "", "",
      "although",
      "", "",
      "rather",
      "", "", "", "", "", "", "", "", "",
      "",
      "nowhere",
      "example",
      "", "",
      "beside",
      "besides",
      "", "", "", "", "", "", "", "", "",
      "haven't",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "hadn't",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "within",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "would",
      "", "", "", "", "", "", "", "",
      "both",
      "let's",
      "", "",
      "wouldn't",
      "hereafter",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "",
      "could",
      "", "", "", "", "", "", "", "",
      "downwards",
      "", "", "",
      "couldn't",
      "", "", "",
      "they've",
      "", "", "",
      "anyway",
      "anyways",
      "", "", "", "", "",
      "few",
      "", "", "", "",
      "i'd",
      "",
      "like",
      "", "", "", "", "", "", "", "",
      "i've",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "you've",
      "", "", "", "", "", "", "",
      "i'll",
      "", "", "", "", "",
      "novel",
      "", "", "", "", "", "", "", "", "",
      "",
      "they'd",
      "", "", "", "", "", "", "", "",
      "later",
      "either",
      "", "", "", "", "", "", "", "",
      "you'd",
      "presumably",
      "", "", "", "",
      "beyond",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "latter",
      "",
      "latterly",
      "", "", "", "", "", "", "",
      "indeed",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "shall",
      "", "", "", "",
      "truly",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "specified",
      "",
      "toward",
      "towards",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "away",
      "brief",
      "should",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "always",
      "follows",
      "followed",
      "", "", "", "", "",
      "following",
      "", "", "", "", "", "", "", "", "",
      "shouldn't",
      "", "", "", "", "", "", "",
      "himself",
      "", "",
      "every",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "namely",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "did",
      "", "",
      "hereby",
      "", "", "",
      "everything",
      "",
      "they'll",
      "actually",
      "", "", "", "", "", "", "", "",
      "nevertheless",
      "", "", "", "",
      "without",
      "",
      "indicated",
      "", "", "", "",
      "described",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "",
      "howbeit",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "nearly",
      "",
      "everyone",
      "available",
      "until",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "however",
      "", "", "", "", "", "", "", "", "",
      "anybody",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "inward",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "overall",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "afterwards",
      "", "", "", "", "", "", "", "",
      "five",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "",
      "it'd",
      "", "", "", "", "",
      "everywhere",
      "", "", "", "",
      "definitely",
      "", "", "", "", "",
      "didn't",
      "", "", "", "", "", "", "", "", "",
      "",
      "merely",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "hither",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "fifth",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "",
      "ltd",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "nobody",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "liked",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "usually",
      "", "", "", "", "", "", "", "", "",
      "mostly",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "we'll",
      "", "", "", "", "",
      "useful",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "",
      "mainly",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "different",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "itself",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "hopefully",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "still",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "",
      "little",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "you'll",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "",
      "really",
      "", "", "", "", "", "", "", "", "",
      "",
      "myself",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "obviously",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "hardly",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "",
      "it'll",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "",
      "lately",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "",
      "everybody",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "",
      "likely",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "",
      "awfully"
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          const char *s = wordlist[key];

          if (*str == *s && !strcmp (str + 1, s + 1))
            return s;
        }
    }
  return 0;
}
#line 572 "tst-benchmark-stop_words-gperf.in"

