#include "benchmark/benchmark.h"
#include "expr/va.hh"

static void BM_Std17Expr_Creates(benchmark::State& state) {
  while (state.KeepRunning()) {
    va::expr e0 = (va::expr{1} + va::expr{0} * va::expr{"x"}) * va::expr{3} + va::expr{12};
    for (auto j = 0; j < state.range(0); ++j) {
      if (j % 2)
        e0 = e0 / va::expr{2};
      else
        e0 = va::expr{3} * e0 + va::expr{1};
    }
  }
}
BENCHMARK(BM_Std17Expr_Creates)
    ->Args({1})
    ->Args({5})
    ->Args({10})
    ->Args({15});

static void BM_Std17Expr_Simplify(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    va::expr e0 = (va::expr{1} + va::expr{0} * va::expr{"x"}) * va::expr{3} + va::expr{12};
    for (auto j = 0; j < state.range(0); ++j) {
      if (j % 2)
        e0 = e0 / va::expr{2};
      else
        e0 = va::expr{3} * e0 + va::expr{1};
    }
    state.ResumeTiming();
    auto const s0 = std::visit(va::simplify{}, e0);
  }
}
BENCHMARK(BM_Std17Expr_Simplify)
    ->Args({1})
    ->Args({5})
    ->Args({10})
    ->Args({15});
