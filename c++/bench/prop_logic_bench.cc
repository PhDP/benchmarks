#include "benchmark/benchmark.h"
#include "logic/prop.hh"
#include "logic/c_prop.h"

static void BM_PropLogic_Eval(benchmark::State& state) {
  using namespace logic;
  while (state.KeepRunning()) {
    using namespace logic;
    auto const values = std::unordered_set<std::string>{"b", "c"};
    auto const f = make_conjunction(make_disjunction(bottom(), make_disjunction("a", make_negation("b"))), top());
    eval(f, values);
  }
}
BENCHMARK(BM_PropLogic_Eval);

static void BM_PropLogic_Index_Eval(benchmark::State& state) {
  using namespace logic;
  while (state.KeepRunning()) {
    using namespace logic;
    auto const values = std::unordered_set<std::string>{"b", "c"};
    auto const f = make_conjunction(make_disjunction(bottom(), make_disjunction("a", make_negation("b"))), top());
    eval_by_idx(f, values);
  }
}
BENCHMARK(BM_PropLogic_Index_Eval);

static void BM_C_PropLogic_Eval(benchmark::State& state) {
  using namespace logic;
  while (state.KeepRunning()) {
    auto const values = std::unordered_set<std::string>{"b", "c"};
    c_formula* f = make_conjunction(make_disjunction(make_bottom(), make_disjunction(make_variable("a"), make_negation(make_variable("b")))), make_top());
    c_eval(f, values);
    c_formula_free(f);
    free(f);
  }
}
BENCHMARK(BM_C_PropLogic_Eval);
