# A C++ constexpr minimal perfect hash table

Computes a constexpr minimal perfect hash table

###

```sh
gperf -ILC++ tst-benchmark-names-gperf.in > tst-benchmark-names-gperf.h
gperf -ILC++ tst-benchmark-titans-gperf.in > tst-benchmark-titans-gperf.h
```

## Clang

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-gperf-clang ./tst-benchmark-gperf.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-switch-clang ./tst-benchmark-mph-switch.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-clang ./tst-benchmark-mph.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-frozen-unordered_set-clang -I ./frozen/include ./tst-benchmark-frozen-unordered_set.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-clang ./tst-benchmark-switch.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-clang ./tst-benchmark-unordered_map.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-clang ./tst-benchmark-unordered_set.cc

./tst-benchmark-gperf-clang < /usr/share/dict/words
./tst-benchmark-mph-clang < /usr/share/dict/words
./tst-benchmark-mph-switch-clang < /usr/share/dict/words
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

tst-benchmark-mph
-----------------
count: 15
duration: 15.0302 ms

tst-benchmark-mph-switch
------------------------
count: 15
duration: 14.9135 ms

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

## GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-gperf-gcc7 ./tst-benchmark-gperf.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-switch-gcc7 ./tst-benchmark-mph-switch.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-gcc7 ./tst-benchmark-mph.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-frozen-unordered_set-gcc7 -I ./frozen/include ./tst-benchmark-frozen-unordered_set.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-gcc7 ./tst-benchmark-switch.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-gcc7 ./tst-benchmark-unordered_map.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-gcc7 ./tst-benchmark-unordered_set.cc

./tst-benchmark-gperf-gcc7 < /usr/share/dict/words
./tst-benchmark-mph-gcc7 < /usr/share/dict/words
./tst-benchmark-mph-switch-gcc7 < /usr/share/dict/words
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

tst-benchmark-mph
-----------------
count: 15
duration: 11.331 ms

tst-benchmark-mph-switch
------------------------
count: 15
duration: 11.254 ms

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
