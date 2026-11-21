# Source layout

Where the code lives, and why the one large file stays whole. cpp-libraries' `docs/SPLITTING.md`
is the rule: a piece is a unit someone opens alone, and a file over 1,000 lines stays whole only
when it is one coherent unit. No file here was split.

## `phf.hh`: kept whole (1,484 lines)

`phf.hh` is the whole library, and the contract users rely on is that one file: the README tells
them that copying `phf.hh` onto the include path works, and `AGENTS.md` keeps it the only header.
SPLITTING.md keeps a single-file library single-file unless the owner decides otherwise.

The file's parts don't make separate units either:

| Lines | Part | Why it stays |
|---|---|---|
| 41-81 | `npos`, `swap`, `partition`, `quicksort` | 40 lines: the sentinel and the sort `phf::_build` runs |
| 84-1108 | the `primes` table, `find_prime`, `prime` | one table (about 1,000 lines of numbers) and its two accessors; `_build` draws its multipliers from it |
| 1111-1124 | `log2` | 14 lines, sizes the class's static tables |
| 1127-1468 | `class phf` | one class whose members share the bucket and index tables and the one lookup formula |
| 1471-1480 | `make_phf` | 10 lines, the factory for the class |

The one cut a maintainer would recognize is the prime table with its accessors, moved to its own
header. It leaves the code to read at about 460 lines, but it ends the copy-one-file contract, so
it is the owner's call and not made here.

## Other files over 1,000 lines

`bench/tst-benchmark-stop_words-gperf.h` (1,315 lines) is gperf output, regenerated from
`bench/tst-benchmark-stop_words-gperf.in` and never edited by hand.
