/* C++ code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf /tmp/kw_large.gperf  */
/* Computed positions: -k'2-3,9-11,17,$' */

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

#line 5 "/tmp/kw_large.gperf"
struct KwEntryLarge { const char* name; int idx; };

#define TOTAL_KEYWORDS 192
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 23
#define MIN_HASH_VALUE 19
#define MAX_HASH_VALUE 717
/* maximum key range = 699, duplicates = 0 */

class KwLarge
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static struct KwEntryLarge *lookup (const char *str, unsigned int len);
};

inline unsigned int
KwLarge::hash (const char *str, unsigned int len)
{
  static unsigned short asso_values[] =
    {
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718,  90, 160, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718,   0,  85, 110,
      205,  10,  15,  20,  90,  55, 225, 115, 205,  60,
       60,   5,  95, 718,   0,  15,  15, 220, 718,  85,
      235,  30,  30, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718, 718, 718, 718,
      718, 718, 718, 718, 718, 718, 718
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[16]+1];
      /*FALLTHROUGH*/
      case 16:
      case 15:
      case 14:
      case 13:
      case 12:
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct KwEntryLarge *
KwLarge::lookup (const char *str, unsigned int len)
{
  static struct KwEntryLarge wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 38 "/tmp/kw_large.gperf"
      {"array/geo", 31},
      {""}, {""}, {""},
#line 14 "/tmp/kw_large.gperf"
      {"geo", 7},
      {""}, {""}, {""}, {""}, {""},
#line 10 "/tmp/kw_large.gperf"
      {"date", 3},
      {""}, {""}, {""},
#line 11 "/tmp/kw_large.gperf"
      {"datetime", 4},
      {""},
#line 25 "/tmp/kw_large.gperf"
      {"array", 18},
      {""}, {""},
#line 16 "/tmp/kw_large.gperf"
      {"positive", 9},
      {""}, {""},
#line 20 "/tmp/kw_large.gperf"
      {"string", 13},
      {""}, {""}, {""},
#line 30 "/tmp/kw_large.gperf"
      {"array/date", 23},
#line 34 "/tmp/kw_large.gperf"
      {"array/float", 27},
      {""},
#line 95 "/tmp/kw_large.gperf"
      {"foreign/array", 88},
      {""}, {""}, {""},
#line 145 "/tmp/kw_large.gperf"
      {"foreign/array/positive", 138},
#line 29 "/tmp/kw_large.gperf"
      {"boolean/array", 22},
#line 36 "/tmp/kw_large.gperf"
      {"array/floating", 29},
#line 151 "/tmp/kw_large.gperf"
      {"foreign/array/script", 144},
#line 73 "/tmp/kw_large.gperf"
      {"foreign/geo", 66},
#line 51 "/tmp/kw_large.gperf"
      {"string/array", 44},
#line 40 "/tmp/kw_large.gperf"
      {"array/integer", 33},
      {""},
#line 169 "/tmp/kw_large.gperf"
      {"foreign/array/string", 162},
      {""}, {""}, {""},
#line 32 "/tmp/kw_large.gperf"
      {"array/datetime", 25},
      {""}, {""}, {""},
#line 175 "/tmp/kw_large.gperf"
      {"foreign/array/text", 168},
#line 85 "/tmp/kw_large.gperf"
      {"foreign/string", 78},
      {""}, {""},
#line 60 "/tmp/kw_large.gperf"
      {"foreign", 53},
      {""},
#line 18 "/tmp/kw_large.gperf"
      {"term", 11},
      {""}, {""},
#line 9 "/tmp/kw_large.gperf"
      {"boolean", 2},
      {""}, {""},
#line 47 "/tmp/kw_large.gperf"
      {"term/array", 40},
      {""},
#line 15 "/tmp/kw_large.gperf"
      {"integer", 8},
#line 49 "/tmp/kw_large.gperf"
      {"keyword/array", 42},
#line 39 "/tmp/kw_large.gperf"
      {"geo/array", 32},
#line 31 "/tmp/kw_large.gperf"
      {"date/array", 24},
      {""}, {""},
#line 187 "/tmp/kw_large.gperf"
      {"foreign/array/timedelta", 180},
      {""},
#line 54 "/tmp/kw_large.gperf"
      {"array/time", 47},
      {""}, {""},
#line 181 "/tmp/kw_large.gperf"
      {"foreign/array/time", 174},
      {""},
#line 173 "/tmp/kw_large.gperf"
      {"string/foreign/array", 166},
      {""}, {""},
#line 157 "/tmp/kw_large.gperf"
      {"foreign/array/term", 150},
      {""},
#line 170 "/tmp/kw_large.gperf"
      {"foreign/string/array", 163},
      {""},
#line 81 "/tmp/kw_large.gperf"
      {"foreign/term", 74},
      {""},
#line 86 "/tmp/kw_large.gperf"
      {"string/foreign", 79},
#line 64 "/tmp/kw_large.gperf"
      {"boolean/foreign", 57},
#line 108 "/tmp/kw_large.gperf"
      {"boolean/array/foreign", 101},
      {""}, {""},
#line 42 "/tmp/kw_large.gperf"
      {"array/positive", 35},
#line 174 "/tmp/kw_large.gperf"
      {"string/array/foreign", 167},
      {""},
#line 147 "/tmp/kw_large.gperf"
      {"array/foreign/positive", 140},
      {""}, {""},
#line 153 "/tmp/kw_large.gperf"
      {"array/foreign/script", 146},
      {""},
#line 134 "/tmp/kw_large.gperf"
      {"foreign/geo/array", 127},
#line 41 "/tmp/kw_large.gperf"
      {"integer/array", 34},
      {""},
#line 171 "/tmp/kw_large.gperf"
      {"array/foreign/string", 164},
      {""},
#line 133 "/tmp/kw_large.gperf"
      {"foreign/array/geo", 126},
      {""},
#line 23 "/tmp/kw_large.gperf"
      {"timedelta", 16},
      {""}, {""}, {""},
#line 177 "/tmp/kw_large.gperf"
      {"array/foreign/text", 170},
#line 22 "/tmp/kw_large.gperf"
      {"time", 15},
#line 46 "/tmp/kw_large.gperf"
      {"array/term", 39},
#line 17 "/tmp/kw_large.gperf"
      {"script", 10},
      {""}, {""},
#line 121 "/tmp/kw_large.gperf"
      {"foreign/array/float", 114},
#line 84 "/tmp/kw_large.gperf"
      {"keyword/foreign", 77},
#line 168 "/tmp/kw_large.gperf"
      {"keyword/array/foreign", 161},
      {""},
#line 96 "/tmp/kw_large.gperf"
      {"array/foreign", 89},
      {""}, {""},
#line 142 "/tmp/kw_large.gperf"
      {"array/integer/foreign", 135},
#line 127 "/tmp/kw_large.gperf"
      {"foreign/array/floating", 120},
      {""}, {""}, {""},
#line 77 "/tmp/kw_large.gperf"
      {"foreign/positive", 70},
#line 50 "/tmp/kw_large.gperf"
      {"array/string", 43},
#line 189 "/tmp/kw_large.gperf"
      {"array/foreign/timedelta", 182},
#line 33 "/tmp/kw_large.gperf"
      {"datetime/array", 26},
#line 75 "/tmp/kw_large.gperf"
      {"foreign/integer", 68},
      {""},
#line 45 "/tmp/kw_large.gperf"
      {"script/array", 38},
#line 183 "/tmp/kw_large.gperf"
      {"array/foreign/time", 176},
#line 43 "/tmp/kw_large.gperf"
      {"positive/array", 36},
#line 97 "/tmp/kw_large.gperf"
      {"foreign/array/object", 90},
      {""},
#line 89 "/tmp/kw_large.gperf"
      {"foreign/time", 82},
#line 159 "/tmp/kw_large.gperf"
      {"array/foreign/term", 152},
#line 79 "/tmp/kw_large.gperf"
      {"foreign/script", 72},
      {""}, {""}, {""},
#line 158 "/tmp/kw_large.gperf"
      {"foreign/term/array", 151},
      {""}, {""},
#line 107 "/tmp/kw_large.gperf"
      {"boolean/foreign/array", 100},
#line 82 "/tmp/kw_large.gperf"
      {"term/foreign", 75},
      {""}, {""},
#line 76 "/tmp/kw_large.gperf"
      {"integer/foreign", 69},
#line 144 "/tmp/kw_large.gperf"
      {"integer/array/foreign", 137},
#line 66 "/tmp/kw_large.gperf"
      {"date/foreign", 59},
      {""}, {""},
#line 63 "/tmp/kw_large.gperf"
      {"foreign/boolean", 56},
      {""},
#line 44 "/tmp/kw_large.gperf"
      {"array/script", 37},
      {""}, {""}, {""},
#line 103 "/tmp/kw_large.gperf"
      {"foreign/array/boolean", 96},
#line 135 "/tmp/kw_large.gperf"
      {"array/foreign/geo", 128},
      {""}, {""},
#line 55 "/tmp/kw_large.gperf"
      {"time/array", 48},
      {""}, {""}, {""}, {""},
#line 155 "/tmp/kw_large.gperf"
      {"script/foreign/array", 148},
      {""},
#line 136 "/tmp/kw_large.gperf"
      {"array/geo/foreign", 129},
      {""},
#line 123 "/tmp/kw_large.gperf"
      {"array/foreign/float", 116},
#line 152 "/tmp/kw_large.gperf"
      {"foreign/script/array", 145},
#line 167 "/tmp/kw_large.gperf"
      {"keyword/foreign/array", 160},
#line 130 "/tmp/kw_large.gperf"
      {"array/floating/foreign", 123},
      {""},
#line 80 "/tmp/kw_large.gperf"
      {"script/foreign", 73},
      {""},
#line 68 "/tmp/kw_large.gperf"
      {"datetime/foreign", 61},
#line 129 "/tmp/kw_large.gperf"
      {"array/foreign/floating", 122},
      {""}, {""},
#line 156 "/tmp/kw_large.gperf"
      {"script/array/foreign", 149},
#line 78 "/tmp/kw_large.gperf"
      {"positive/foreign", 71},
      {""}, {""}, {""},
#line 172 "/tmp/kw_large.gperf"
      {"array/string/foreign", 165},
      {""}, {""}, {""}, {""},
#line 99 "/tmp/kw_large.gperf"
      {"array/foreign/object", 92},
#line 166 "/tmp/kw_large.gperf"
      {"array/keyword/foreign", 159},
#line 118 "/tmp/kw_large.gperf"
      {"array/datetime/foreign", 111},
      {""}, {""}, {""},
#line 74 "/tmp/kw_large.gperf"
      {"geo/foreign", 67},
      {""}, {""}, {""}, {""}, {""},
#line 137 "/tmp/kw_large.gperf"
      {"geo/foreign/array", 130},
#line 161 "/tmp/kw_large.gperf"
      {"term/foreign/array", 154},
      {""},
#line 12 "/tmp/kw_large.gperf"
      {"float", 5},
#line 143 "/tmp/kw_large.gperf"
      {"integer/foreign/array", 136},
#line 138 "/tmp/kw_large.gperf"
      {"geo/array/foreign", 131},
#line 113 "/tmp/kw_large.gperf"
      {"date/foreign/array", 106},
      {""}, {""},
#line 104 "/tmp/kw_large.gperf"
      {"foreign/boolean/array", 97},
#line 91 "/tmp/kw_large.gperf"
      {"foreign/timedelta", 84},
#line 13 "/tmp/kw_large.gperf"
      {"floating", 6},
      {""}, {""},
#line 105 "/tmp/kw_large.gperf"
      {"array/foreign/boolean", 98},
      {""}, {""}, {""},
#line 154 "/tmp/kw_large.gperf"
      {"array/script/foreign", 147},
#line 139 "/tmp/kw_large.gperf"
      {"foreign/array/integer", 132},
#line 65 "/tmp/kw_large.gperf"
      {"foreign/date", 58},
      {""}, {""},
#line 57 "/tmp/kw_large.gperf"
      {"timedelta/array", 50},
#line 67 "/tmp/kw_large.gperf"
      {"foreign/datetime", 60},
#line 19 "/tmp/kw_large.gperf"
      {"keyword", 12},
#line 109 "/tmp/kw_large.gperf"
      {"foreign/array/date", 102},
      {""}, {""}, {""},
#line 115 "/tmp/kw_large.gperf"
      {"foreign/array/datetime", 108},
#line 69 "/tmp/kw_large.gperf"
      {"foreign/float", 62},
      {""}, {""},
#line 163 "/tmp/kw_large.gperf"
      {"foreign/array/keyword", 156},
#line 148 "/tmp/kw_large.gperf"
      {"array/positive/foreign", 141},
      {""},
#line 21 "/tmp/kw_large.gperf"
      {"text", 14},
      {""},
#line 71 "/tmp/kw_large.gperf"
      {"foreign/floating", 64},
      {""},
#line 182 "/tmp/kw_large.gperf"
      {"foreign/time/array", 175},
      {""}, {""},
#line 140 "/tmp/kw_large.gperf"
      {"foreign/integer/array", 133},
#line 90 "/tmp/kw_large.gperf"
      {"time/foreign", 83},
#line 188 "/tmp/kw_large.gperf"
      {"foreign/timedelta/array", 181},
      {""},
#line 52 "/tmp/kw_large.gperf"
      {"array/text", 45},
      {""}, {""},
#line 191 "/tmp/kw_large.gperf"
      {"timedelta/foreign/array", 184},
      {""}, {""},
#line 35 "/tmp/kw_large.gperf"
      {"float/array", 28},
#line 120 "/tmp/kw_large.gperf"
      {"datetime/array/foreign", 113},
#line 112 "/tmp/kw_large.gperf"
      {"array/date/foreign", 105},
      {""}, {""}, {""},
#line 150 "/tmp/kw_large.gperf"
      {"positive/array/foreign", 143},
      {""}, {""},
#line 56 "/tmp/kw_large.gperf"
      {"array/timedelta", 49},
      {""},
#line 87 "/tmp/kw_large.gperf"
      {"foreign/text", 80},
#line 28 "/tmp/kw_large.gperf"
      {"array/boolean", 21},
#line 122 "/tmp/kw_large.gperf"
      {"foreign/float/array", 115},
      {""},
#line 164 "/tmp/kw_large.gperf"
      {"foreign/keyword/array", 157},
      {""},
#line 162 "/tmp/kw_large.gperf"
      {"term/array/foreign", 155},
      {""}, {""}, {""},
#line 92 "/tmp/kw_large.gperf"
      {"timedelta/foreign", 85},
#line 114 "/tmp/kw_large.gperf"
      {"date/array/foreign", 107},
      {""}, {""},
#line 141 "/tmp/kw_large.gperf"
      {"array/foreign/integer", 134},
      {""},
#line 192 "/tmp/kw_large.gperf"
      {"timedelta/array/foreign", 185},
      {""}, {""}, {""}, {""},
#line 111 "/tmp/kw_large.gperf"
      {"array/foreign/date", 104},
      {""},
#line 53 "/tmp/kw_large.gperf"
      {"text/array", 46},
#line 106 "/tmp/kw_large.gperf"
      {"array/boolean/foreign", 99},
#line 117 "/tmp/kw_large.gperf"
      {"array/foreign/datetime", 110},
#line 160 "/tmp/kw_large.gperf"
      {"array/term/foreign", 153},
      {""}, {""},
#line 165 "/tmp/kw_large.gperf"
      {"array/foreign/keyword", 158},
      {""}, {""},
#line 124 "/tmp/kw_large.gperf"
      {"array/float/foreign", 117},
      {""}, {""}, {""},
#line 184 "/tmp/kw_large.gperf"
      {"array/time/foreign", 177},
      {""}, {""},
#line 8 "/tmp/kw_large.gperf"
      {"object", 1},
#line 146 "/tmp/kw_large.gperf"
      {"foreign/positive/array", 139},
#line 185 "/tmp/kw_large.gperf"
      {"time/foreign/array", 178},
      {""}, {""}, {""},
#line 119 "/tmp/kw_large.gperf"
      {"datetime/foreign/array", 112},
#line 48 "/tmp/kw_large.gperf"
      {"array/keyword", 41},
#line 125 "/tmp/kw_large.gperf"
      {"float/foreign/array", 118},
      {""}, {""},
#line 149 "/tmp/kw_large.gperf"
      {"positive/foreign/array", 142},
      {""},
#line 37 "/tmp/kw_large.gperf"
      {"floating/array", 30},
#line 59 "/tmp/kw_large.gperf"
      {"uuid/array", 52},
      {""}, {""},
#line 70 "/tmp/kw_large.gperf"
      {"float/foreign", 63},
#line 61 "/tmp/kw_large.gperf"
      {"foreign/object", 54},
      {""}, {""},
#line 27 "/tmp/kw_large.gperf"
      {"object/array", 20},
      {""}, {""}, {""}, {""}, {""},
#line 110 "/tmp/kw_large.gperf"
      {"foreign/date/array", 103},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 26 "/tmp/kw_large.gperf"
      {"array/object", 19},
      {""}, {""}, {""}, {""}, {""},
#line 190 "/tmp/kw_large.gperf"
      {"array/timedelta/foreign", 183},
      {""},
#line 83 "/tmp/kw_large.gperf"
      {"foreign/keyword", 76},
      {""}, {""}, {""}, {""},
#line 98 "/tmp/kw_large.gperf"
      {"foreign/object/array", 91},
      {""}, {""}, {""}, {""},
#line 101 "/tmp/kw_large.gperf"
      {"object/foreign/array", 94},
      {""}, {""}, {""}, {""}, {""},
#line 72 "/tmp/kw_large.gperf"
      {"floating/foreign", 65},
      {""},
#line 176 "/tmp/kw_large.gperf"
      {"foreign/text/array", 169},
#line 62 "/tmp/kw_large.gperf"
      {"object/foreign", 55},
      {""}, {""},
#line 88 "/tmp/kw_large.gperf"
      {"text/foreign", 81},
#line 186 "/tmp/kw_large.gperf"
      {"time/array/foreign", 179},
      {""},
#line 102 "/tmp/kw_large.gperf"
      {"object/array/foreign", 95},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 94 "/tmp/kw_large.gperf"
      {"uuid/foreign", 87},
      {""}, {""}, {""}, {""},
#line 116 "/tmp/kw_large.gperf"
      {"foreign/datetime/array", 109},
      {""}, {""},
#line 100 "/tmp/kw_large.gperf"
      {"array/object/foreign", 93},
      {""},
#line 128 "/tmp/kw_large.gperf"
      {"foreign/floating/array", 121},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 193 "/tmp/kw_large.gperf"
      {"foreign/array/uuid", 186},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 179 "/tmp/kw_large.gperf"
      {"text/foreign/array", 172},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
#line 58 "/tmp/kw_large.gperf"
      {"array/uuid", 51},
      {""},
#line 132 "/tmp/kw_large.gperf"
      {"floating/array/foreign", 125},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 24 "/tmp/kw_large.gperf"
      {"uuid", 17},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 197 "/tmp/kw_large.gperf"
      {"uuid/foreign/array", 190},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 178 "/tmp/kw_large.gperf"
      {"array/text/foreign", 171},
      {""}, {""}, {""}, {""},
#line 195 "/tmp/kw_large.gperf"
      {"array/foreign/uuid", 188},
      {""}, {""}, {""}, {""},
#line 196 "/tmp/kw_large.gperf"
      {"array/uuid/foreign", 189},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 131 "/tmp/kw_large.gperf"
      {"floating/foreign/array", 124},
#line 180 "/tmp/kw_large.gperf"
      {"text/array/foreign", 173},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 126 "/tmp/kw_large.gperf"
      {"float/array/foreign", 119},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 198 "/tmp/kw_large.gperf"
      {"uuid/array/foreign", 191},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 194 "/tmp/kw_large.gperf"
      {"foreign/uuid/array", 187},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 7 "/tmp/kw_large.gperf"
      {"undefined", 0},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 93 "/tmp/kw_large.gperf"
      {"foreign/uuid", 86}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
