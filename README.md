# A C++ constexpr perfect hash table

Computes a constexpr perfect hash table (or minimal perfect hash)

## Example

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-phf-clang ./tst-phf.cc

./tst-phf-clang Cronus
./tst-phf-clang Antonella
```

## Benchmark

### Clang

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-gperf-clang ./tst-benchmark-gperf.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-phf-switch-clang ./tst-benchmark-phf-switch.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-phf-clang ./tst-benchmark-phf.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-frozen-unordered_set-clang -I ./frozen/include ./tst-benchmark-frozen-unordered_set.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-clang ./tst-benchmark-switch.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-clang ./tst-benchmark-unordered_map.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-clang ./tst-benchmark-unordered_set.cc

./tst-benchmark-gperf-clang < /usr/share/dict/words
./tst-benchmark-phf-clang < /usr/share/dict/words
./tst-benchmark-phf-switch-clang < /usr/share/dict/words
./tst-benchmark-frozen-unordered_set-clang < /usr/share/dict/words
./tst-benchmark-switch-clang < /usr/share/dict/words
./tst-benchmark-unordered_set-clang < /usr/share/dict/words
./tst-benchmark-unordered_map-clang < /usr/share/dict/words
```

```
tst-benchmark-gperf
-------------------
count: 15
duration: 10.9965 ms

tst-benchmark-phf
-----------------
count: 15
duration: 14.9456 ms

tst-benchmark-phf-switch
------------------------
count: 15
duration: 14.9483 ms

tst-benchmark-frozen-unordered_set
----------------------------------
count: 15
duration: 14.7188 ms

tst-benchmark-switch
--------------------
count: 15
duration: 17.2478 ms

tst-benchmark-unordered_set
---------------------------
count: 15
duration: 20.0898 ms

tst-benchmark-unordered_map
---------------------------
count: 15
duration: 20.5951 ms
```


### GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-gperf-gcc7 ./tst-benchmark-gperf.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-phf-switch-gcc7 ./tst-benchmark-phf-switch.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-phf-gcc7 ./tst-benchmark-phf.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-frozen-unordered_set-gcc7 -I ./frozen/include ./tst-benchmark-frozen-unordered_set.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-gcc7 ./tst-benchmark-switch.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-gcc7 ./tst-benchmark-unordered_map.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-gcc7 ./tst-benchmark-unordered_set.cc

./tst-benchmark-gperf-gcc7 < /usr/share/dict/words
./tst-benchmark-phf-gcc7 < /usr/share/dict/words
./tst-benchmark-phf-switch-gcc7 < /usr/share/dict/words
./tst-benchmark-frozen-unordered_set-gcc7 < /usr/share/dict/words
./tst-benchmark-switch-gcc7 < /usr/share/dict/words
./tst-benchmark-unordered_set-gcc7 < /usr/share/dict/words
./tst-benchmark-unordered_map-gcc7 < /usr/share/dict/words
```

```
tst-benchmark-gperf
-------------------
count: 15
duration: 7.819 ms

tst-benchmark-phf
-----------------
count: 15
duration: 11.312 ms

tst-benchmark-phf-switch
------------------------
count: 15
duration: 11.25 ms

tst-benchmark-frozen-unordered_set
----------------------------------
count: 15
duration: 11.098 ms

tst-benchmark-switch
--------------------
count: 15
duration: 12.422 ms

tst-benchmark-unordered_set
---------------------------
count: 15
duration: 17.928 ms

tst-benchmark-unordered_map
---------------------------
count: 15
duration: 17.963 ms
```
