# A C++ constexpr perfect hash table

Computes a constexpr perfect hash table (or minimal perfect hash)

## Benchmark

### Clang

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-clang -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-clang
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 662.897 ms [phf(fnv1ah32)::dump]
  stopped 23776700/46422000 in 682.839 ms [phf(fnv1ah64)::dump]
  stopped 23776700/46422000 in 822.897 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 812.447 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 827.008 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 861.319 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 824.845 ms [gperf]
  stopped 23776700/46422000 in 893.336 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1609.27 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1639.28 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1974.48 ms [unordered_set]
  stopped 23776700/46422000 in 5245.91 ms [set]
```


### GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-stop_words-gcc7 -I ./frozen/include ./tst-benchmark-stop_words.cc

gzcat 'The Count of Monte Cristo.txt.gz' | ./tst-benchmark-stop_words-gcc7
```

```
Finding stop words in a total of 464220 words...
  stopped 23776700/46422000 in 574.195 ms [phf(fnv1ah32)::dump]
  stopped 23776700/46422000 in 557.475 ms [phf(fnv1ah64)::dump]
  stopped 23776700/46422000 in 678.713 ms [switch(phf(fnv1ah32))]
  stopped 23776700/46422000 in 690.241 ms [switch(phf(fnv1ah64))]
  stopped 23776700/46422000 in 678.776 ms [phf(fnv1ah32)]
  stopped 23776700/46422000 in 691.492 ms [phf(fnv1ah64)]
  stopped 23776700/46422000 in 775.358 ms [gperf]
  stopped 23776700/46422000 in 833.808 ms [frozen::unordered_set]
  stopped 23776700/46422000 in 1414.45 ms [switch(fnv1ah32)]
  stopped 23776700/46422000 in 1449.67 ms [switch(fnv1ah64)]
  stopped 23776700/46422000 in 1953.66 ms [unordered_set]
  stopped 23776700/46422000 in 4489.51 ms [set]
```
