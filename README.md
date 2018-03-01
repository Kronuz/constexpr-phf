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
  stopped 23776700/46422000 in 685.83 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 679.489 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 666.526 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 678.863 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 843.622 ms [gperf]
  stopped 23776700/46422000 in 875.943 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1580.48 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1621.58 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1969.85 ms [unordered_set]
  stopped 23776700/46422000 in 1947.09 ms [unordered_map]
  stopped 23776700/46422000 in 2301.62 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 2376.37 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 5347.96 ms [set]
```


### GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-gcc7 -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-gcc7
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 688.024 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 691.24 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 709.122 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 708.612 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 801.921 ms [gperf]
  stopped 23776700/46422000 in 987.715 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1458.43 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1479.54 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1963.78 ms [unordered_set]
  stopped 23776700/46422000 in 1949.04 ms [unordered_map]
  stopped 23776700/46422000 in 6550.6 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 8893.97 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 4331.27 ms [set]
```
