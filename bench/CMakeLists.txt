set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)

add_subdirectory(benchmark)
include_directories(benchmark/include)

set(bench_cc
  union_bench.cc
  intersection_bench.cc
  insert_bench.cc
  find_bench.cc
)

add_executable(set_benchmark ${bench_cc})

target_link_libraries(set_benchmark
  benchmark
  ${CMAKE_THREAD_LIBS_INIT}
  ${MATH_LIBS}
)
