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
c++ -std=c++17 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-clang -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-clang
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 605.015 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 654.328 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 612.922 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 654.641 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 846.043 ms [gperf]
  stopped 23776700/46422000 in 885.386 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1402.76 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1452.33 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1522.44 ms [ctrie]
  stopped 23776700/46422000 in 1821.04 ms [unordered_set]
  stopped 23776700/46422000 in 1817.42 ms [unordered_map]
  stopped 23776700/46422000 in 2606.69 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 2645.08 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 4590.99 ms [set]
```


### GCC 8

```sh
g++-7 -std=c++17 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-gcc8 -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-gcc8
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 644.927 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 690.715 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 638.193 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 697.615 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 742.117 ms [gperf]
  stopped 23776700/46422000 in 829.808 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1414.21 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1488.30 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1042.80 ms [ctrie]
  stopped 23776700/46422000 in 1918.92 ms [unordered_set]
  stopped 23776700/46422000 in 1938.93 ms [unordered_map]
  stopped 23776700/46422000 in 6387.15 ms [if/else(fnv1ah32)]
  stopped 23776700/46422000 in 8312.30 ms [if/else(fnv1ah64)]
  stopped 23776700/46422000 in 4205.88 ms [set]
```
