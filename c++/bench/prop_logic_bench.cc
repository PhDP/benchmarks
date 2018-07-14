#include "benchmark/benchmark.h"
#include "logic/prop.hh"

static void BM_PropLogic_Eval(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    using namespace logic;
    auto const values = std::unordered_set<std::string>{"b", "c"};
    auto const f = make_conjunction(make_disjunction(bottom(), make_disjunction("a", make_negation("b"))), top());
    state.ResumeTiming();
    eval(f, values);
  }
}
BENCHMARK(BM_PropLogic_Eval);
