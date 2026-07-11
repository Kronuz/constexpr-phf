// Correctness audit for constexpr-phf (phf.hh).
// Verifies: minimal (at() in [0,N)), perfect (bijective, no collision), count() has no
// false positives, find/at agree, and the documented failure modes throw.
#include "phf.hh"
#include <cstdint>
#include <vector>
#include <set>
#include <random>
#include <cstdio>
#include <stdexcept>
#include <algorithm>

static int g_fail = 0, g_check = 0;

template <std::size_t N, typename T>
void verify_set(const std::vector<T>& keys, const char* label) {
    ++g_check;
    phf::phf<T, N> h;
    try { h.assign(keys.data(), N); }
    catch (const std::exception& e) { printf("  [FAIL] %s: build threw: %s\n", label, e.what()); ++g_fail; return; }
    if (h.size() != N) { printf("  [FAIL] %s: size()=%zu != %zu\n", label, h.size(), N); ++g_fail; return; }
    std::vector<int> seen(N, 0);
    for (std::size_t i = 0; i < N; ++i) {
        T k = keys[i];
        if (h.count(k) != 1) { printf("  [FAIL] %s: count(present)!=1\n", label); ++g_fail; return; }
        std::size_t idx = h.at(k);
        if (idx >= N) { printf("  [FAIL] %s: at()=%zu >= N=%zu (NOT minimal)\n", label, idx, N); ++g_fail; return; }
        if (seen[idx]++) { printf("  [FAIL] %s: at() collision at %zu (NOT perfect)\n", label, idx); ++g_fail; return; }
        if (h.find(k) != idx) { printf("  [FAIL] %s: find != at\n", label); ++g_fail; return; }
    }
    // false positives: probe many non-keys
    std::set<T> ks(keys.begin(), keys.end());
    std::mt19937_64 rng(999);
    int fp = 0;
    for (int t = 0; t < 200000; ++t) { T p = (T)rng(); if (!ks.count(p) && h.count(p) != 0) ++fp; }
    if (fp) { printf("  [FAIL] %s: %d false positives\n", label, fp); ++g_fail; return; }
}

template <std::size_t N>
void random_trials(int trials) {
    std::mt19937_64 rng(0xC0FFEEu + N);
    for (int t = 0; t < trials; ++t) {
        std::set<std::uint32_t> s;
        while (s.size() < N) s.insert((std::uint32_t)rng());
        std::vector<std::uint32_t> keys(s.begin(), s.end());
        std::shuffle(keys.begin(), keys.end(), rng);
        char buf[64]; snprintf(buf, sizeof buf, "random u32 N=%zu t=%d", N, t);
        verify_set<N, std::uint32_t>(keys, buf);
    }
}

int main() {
    printf("== random distinct u32 key sets (bijective/minimal/no-false-pos) ==\n");
    random_trials<1>(30);  random_trials<2>(30);   random_trials<3>(30);
    random_trials<5>(30);  random_trials<8>(30);   random_trials<13>(30);
    random_trials<16>(30); random_trials<17>(30);  random_trials<32>(20);
    random_trials<64>(20); random_trials<100>(20); random_trials<128>(10);
    random_trials<256>(10);random_trials<500>(5);  random_trials<1000>(3);

    printf("== structured key sets ==\n");
    { std::vector<std::uint32_t> k; for (std::uint32_t i=0;i<64;++i) k.push_back(i);      verify_set<64,std::uint32_t>(k, "sequential 0..63"); }
    { std::vector<std::uint32_t> k; for (std::uint32_t i=0;i<32;++i) k.push_back(1u<<i);   verify_set<32,std::uint32_t>(k, "distinct powers of two"); }

    printf("== adversarial: ALL keys in one bucket (multiples of buckets_size) ==\n");
    // buckets_size = 1<<log2(N+1); multiples of a big power of two all hash to bucket 0,
    // forcing a single mul to spread every key. This is the CHD worst case.
    { std::vector<std::uint32_t> k; for (std::uint32_t i=0;i<16;++i) k.push_back(i*4096u); // 16 -> buckets_size 32
      try { verify_set<16,std::uint32_t>(k, "16 keys one bucket"); }
      catch (const std::exception& e){ printf("  [threw] 16 one-bucket: %s\n", e.what()); } }
    { std::vector<std::uint32_t> k; for (std::uint32_t i=0;i<32;++i) k.push_back(i*65536u); // 32 -> buckets_size 64
      try { verify_set<32,std::uint32_t>(k, "32 keys one bucket"); ++g_check; }
      catch (const std::exception& e){ printf("  [threw] 32 one-bucket: %s\n", e.what()); } }

    printf("== larger sets (runtime assign, no constexpr limit) ==\n");
    { std::mt19937_64 r(3); std::set<std::uint32_t> s; while(s.size()<5000) s.insert((std::uint32_t)r());
      std::vector<std::uint32_t> k(s.begin(),s.end()); verify_set<5000,std::uint32_t>(k, "random N=5000"); }

    printf("== huge uint64 keys near max (multiply overflow) ==\n");
    { std::vector<std::uint64_t> k; std::mt19937_64 r(7);
      std::set<std::uint64_t> s; while(s.size()<50) s.insert(r()|0xF000000000000000ull);
      k.assign(s.begin(), s.end()); verify_set<50,std::uint64_t>(k, "u64 high keys"); }

    printf("== signed int keys incl. NEGATIVE (potential OOB) ==\n");
    { std::vector<int> k = {-5,-4,-3,-2,-1,0,1,2,3,4}; 
      try { verify_set<10,int>(k, "signed w/ negatives"); }
      catch (const std::exception& e) { printf("  [threw] signed negatives: %s\n", e.what()); } }

    printf("== documented failure modes (must throw) ==\n");
    { // duplicate keys
      std::vector<std::uint32_t> k = {1,2,3,4,4,6,7,8}; bool threw=false;
      try { phf::phf<std::uint32_t,8> h; h.assign(k.data(),8); } catch(const std::exception&){ threw=true; }
      ++g_check; if(!threw){printf("  [FAIL] duplicate keys did NOT throw\n");++g_fail;} else printf("  [ok] duplicates throw\n"); }
    { // empty
      std::vector<std::uint32_t> k = {1}; bool threw=false;
      try { phf::phf<std::uint32_t,8> h; h.assign(k.data(),0); } catch(const std::exception&){ threw=true; }
      ++g_check; if(!threw){printf("  [FAIL] empty did NOT throw\n");++g_fail;} else printf("  [ok] empty throws\n"); }

    printf("\n%s: %d checks, %d failures\n", g_fail? "RESULT FAIL":"RESULT PASS", g_check, g_fail);
    return g_fail ? 1 : 0;
}
