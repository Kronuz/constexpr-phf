/* C++ code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf -ILC++ tst-benchmark-titans-gperf.in  */
/* Computed positions: -k'1-2' */

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
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#include <string.h>

#define TOTAL_KEYWORDS 33
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 10
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 46
/* maximum key range = 43, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const char *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
Perfect_Hash::hash (register const char *str, register unsigned int len)
{
  static unsigned char asso_values[] =
    {
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47,  0, 47, 15, 20,  0,
      47, 47, 15,  5, 47, 47,  0,  0, 47, 20,
       5, 47, 10, 10,  0, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47,  5, 47,  0,
      47, 20, 47, 47,  0, 15, 47, 47,  0, 47,
       0, 15, 20, 47,  0,  5,  5,  0, 47, 47,
      47,  0, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
      47, 47, 47, 47, 47, 47
    };
  return len + asso_values[(unsigned char)str[1]] + asso_values[(unsigned char)str[0]];
}

const char *
Perfect_Hash::in_word_set (register const char *str, register unsigned int len)
{
  static const char * wordlist[] =
    {
      "", "", "", "",
      "Aura",
      "Theia",
      "Themis",
      "Eurybia",
      "Eurynome",
      "Mnemosyne",
      "Atlas",
      "Phoebe",
      "Asteria",
      "Astraeus",
      "Rhea",
      "Prometheus",
      "Pallas",
      "Iapetus",
      "Eos",
      "Styx",
      "Crius",
      "Cronus",
      "Clymene",
      "Hyperion",
      "Leto",
      "Metis",
      "Tethys",
      "Oceanus",
      "Lelantos",
      "Menoetius",
      "Epimetheus",
      "Perses",
      "", "", "",
      "Coeus",
      "Selene",
      "", "", "",
      "Dione",
      "Helios",
      "", "", "", "",
      "Ophion"
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key];

          if (*str == *s && !strcmp (str + 1, s + 1))
            return s;
        }
    }
  return 0;
}
#line 35 "tst-benchmark-titans-gperf.in"

