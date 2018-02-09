#include "benchmark/benchmark.h"
#include "expr/bt.hh"

static void BM_BoostExpr_Creates(benchmark::State& state) {
  while (state.KeepRunning()) {
    bt::expr e0 = (bt::expr{1} + bt::expr{0} * bt::expr{"x"}) * bt::expr{3} + bt::expr{12};
    for (auto j = 0; j < state.range(0); ++j) {
      if (j % 2)
        e0 = e0 / bt::expr{2};
      else
        e0 = bt::expr{3} * e0 + bt::expr{1};
    }
  }
}
BENCHMARK(BM_BoostExpr_Creates)
    ->Args({1})
    ->Args({5})
    ->Args({10})
    ->Args({15});

static void BM_BoostExpr_Simplify(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    bt::expr e0 = (bt::expr{1} + bt::expr{0} * bt::expr{"x"}) * bt::expr{3} + bt::expr{12};
    for (auto j = 0; j < state.range(0); ++j) {
      if (j % 2)
        e0 = e0 / bt::expr{2};
      else
        e0 = bt::expr{3} * e0 + bt::expr{1};
    }
    state.ResumeTiming();
    auto const s0 = boost::apply_visitor(bt::simplify{}, e0);
  }
}
BENCHMARK(BM_BoostExpr_Simplify)
    ->Args({1})
    ->Args({5})
    ->Args({10})
    ->Args({15});
