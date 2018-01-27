set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)
include_directories(benchmark/include)

set(bench_cc
  main.cc
  #  union_bench.cc
  #  intersection_bench.cc
  #  insert_bench.cc
  #  find_bench.cc
  gate_oo_bench.cc
  gate_va_bench.cc
)

add_executable(all_benchmarks ${bench_cc})

target_link_libraries(all_benchmarks
  benchmark
  ${CMAKE_THREAD_LIBS_INIT}
  ${MATH_LIBS}
)
