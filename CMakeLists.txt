cmake_minimum_required(VERSION 3.14)
project(constexpr_phf LANGUAGES CXX)

# Header-only library: a single phf.hh at the repo root (the only header here).
# Consumers link this INTERFACE target, or via FetchContent add the source dir.
add_library(constexpr_phf INTERFACE)
add_library(constexpr_phf::constexpr_phf ALIAS constexpr_phf)
target_include_directories(constexpr_phf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(constexpr_phf INTERFACE cxx_std_17)

# Tests, benchmark, and demo only build when this repo is the top-level project, so
# consumers pulling us in via FetchContent don't build them.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  enable_testing()

  # Smoke test.
  add_executable(phf_test test/test.cc)
  target_link_libraries(phf_test PRIVATE constexpr_phf)
  add_test(NAME phf_test COMMAND phf_test)

  # Deep correctness harness: random + adversarial key sets (incl. distinct powers of
  # two, which exercises the robust fallback), edge cases, throw modes.
  add_executable(phf_correctness test/correctness.cc)
  target_link_libraries(phf_correctness PRIVATE constexpr_phf)
  add_test(NAME phf_correctness COMMAND phf_correctness)

  # A runnable tour of the library (not a test): ./build/phf_demo
  add_executable(phf_demo examples/demo.cc)
  target_link_libraries(phf_demo PRIVATE constexpr_phf)

  # Integer-core micro-benchmark (not a test): ./build/phf_bench
  add_executable(phf_bench bench/bench.cc)
  target_link_libraries(phf_bench PRIVATE constexpr_phf)
  target_compile_options(phf_bench PRIVATE -O3)
endif()
