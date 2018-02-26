# A C++ constexpr minimal perfect hash table

Computes a constexpr minimal perfect hash table

###

```sh
gperf tst-benchmark-names.in > tst-benchmark-names.c
gperf tst-benchmark-titans.in > tst-benchmark-titans.c
```

## Clang

```sh
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-clang ./tst-benchmark-mph.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph2-clang ./tst-benchmark-mph2.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-clang ./tst-benchmark-switch.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-clang ./tst-benchmark-unordered_map.cc
c++ -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-clang ./tst-benchmark-unordered_set.cc

./tst-benchmark-mph-clang < /usr/share/dict/words
./tst-benchmark-mph2-clang < /usr/share/dict/words
./tst-benchmark-switch-clang < /usr/share/dict/words
./tst-benchmark-unordered_map-clang < /usr/share/dict/words
./tst-benchmark-unordered_set-clang < /usr/share/dict/words
```

```
tst-benchmark-mph
-----------------
count: 1308
duration: 20.742 ms

tst-benchmark-mph2
------------------
count: 1308
duration: 20.7898 ms

tst-benchmark-switch
--------------------
count: 1308
duration: 23.8089 ms

tst-benchmark-unordered_map
---------------------------
count: 1308
duration: 23.9406 ms

tst-benchmark-unordered_set
---------------------------
count: 1308
duration: 23.4559 ms
```

## GCC 7

```sh
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph-gcc7 ./tst-benchmark-mph.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-mph2-gcc7 ./tst-benchmark-mph2.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-switch-gcc7 ./tst-benchmark-switch.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_map-gcc7 ./tst-benchmark-unordered_map.cc
g++-7 -std=c++14 -pedantic -Wall -Wextra -O3 -o tst-benchmark-unordered_set-gcc7 ./tst-benchmark-unordered_set.cc

./tst-benchmark-mph-gcc7 < /usr/share/dict/words
./tst-benchmark-mph2-gcc7 < /usr/share/dict/words
./tst-benchmark-switch-gcc7 < /usr/share/dict/words
./tst-benchmark-unordered_map-gcc7 < /usr/share/dict/words
./tst-benchmark-unordered_set-gcc7 < /usr/share/dict/words
```

```
tst-benchmark-mph
-----------------
count: 1308
duration: 17.195 ms

tst-benchmark-mph2
------------------
count: 1308
duration: 16.874 ms

tst-benchmark-switch
--------------------
count: 1308
duration: 18.144 ms

tst-benchmark-unordered_map
---------------------------
count: 1308
duration: 19.923 ms

tst-benchmark-unordered_set
---------------------------
count: 1308
duration: 21.083 ms
```
