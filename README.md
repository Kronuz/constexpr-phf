# A C++ constexpr (minimal) perfect hash function generator

Computes a constexpr (minimal) perfect hash function generator

There are times when one wishes there was a *fast* simple way to do
things like this:

```c
switch (option) {
	case "first_option":
		// do something
		break;
	case "other_option":
		// do something else
		break;

	...

	case "so_many_options":
		// do so much more
		break;
}
```

There are options: `std::unordered_map<std::string, void (*)(void)>` (map of
function pointers), a bunch of `if`/`else`, a `switch()` of hashed strings,
`gperf` (GNU's perfect hash function generator), etc.


## Benchmark

The contenders:

+ `std::set`
+ `std::unordered_set`
+ `std::unordered_map`
+ `switch()` statements of hashes
+ `frozen::unordered_set` (https://blog.quarkslab.com/frozen-an-header-only-constexpr-alternative-to-gperf-for-c14-users.html)
+ `gperf` (https://www.gnu.org/software/gperf/)
+ `phf` our (minimal) perfect hash function generator based on Dr. Daoud's work (http://iswsa.acm.org/mphf/index.html)


### Clang

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-clang -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-clang
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 638.122 ms [phf(fnv1ah32)::dump]
  stopped 23776700/46422000 in 670.987 ms [phf(fnv1ah64)::dump]
  stopped 23776700/46422000 in 783.914 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 849.898 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 819.775 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 855.006 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 852.964 ms [gperf]
  stopped 23776700/46422000 in 886.937 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1615.35 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1632.29 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1950.46 ms [unordered_set]
  stopped 23776700/46422000 in 1935.1 ms [unordered_map]
  stopped 23776700/46422000 in 2301.85 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 2320.5 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 5230.43 ms [set]
```


### GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-gcc7 -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-gcc7
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 610.706 ms [phf(fnv1ah32)::dump]
  stopped 23776700/46422000 in 681.957 ms [phf(fnv1ah64)::dump]
  stopped 23776700/46422000 in 745.737 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 797.741 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 747.25 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 812.421 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 812.355 ms [gperf]
  stopped 23776700/46422000 in 895.396 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1549.94 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1695.61 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 2053 ms [unordered_set]
  stopped 23776700/46422000 in 2084.86 ms [unordered_map]
  stopped 23776700/46422000 in 6894.86 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 9346.91 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 4234.64 ms [set]
```
