#include "benchmark/benchmark.h"
#include "gates/oo.hh"
#include "random_bits.hh"
#include <random>
#include <vector>

static void BM_ObjectOrientedGatesEval(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto unif = std::uniform_real_distribution<double>(0.0, 1.0);
    auto rng = std::mt19937_64(state.range(0));

    auto const bits = random_bits(rng, state.range(0));

    auto gs = oo_gate::gates{};
    for (auto i = 0u; i < state.range(0); ++i) {
      size_t const id = unif(rng) * 5.0;
      if (id == 0) {
        size_t const x = unif(rng) * state.range(0);
        oo_gate::add_gate(gs, oo_gate::not_gate(x));
      } else if (id == 1) {
        size_t const c = unif(rng) * state.range(0);
        size_t x = unif(rng) * state.range(0);
        while (x == c) x = unif(rng) * state.range(0);
        oo_gate::add_gate(gs, oo_gate::cnot_gate(c, x));
      } else if (id == 2) {
        size_t const x = unif(rng) * state.range(0);
        size_t y = unif(rng) * state.range(0);
        while (y == x) y = unif(rng) * state.range(0);
        oo_gate::add_gate(gs, oo_gate::swap_gate(x, y));
      } else if (id == 3) {
        size_t const c0 = unif(rng) * state.range(0);
        size_t c1 = unif(rng) * state.range(0);
        size_t x = unif(rng) * state.range(0);
        while (c1 == c0) c1 = unif(rng) * state.range(0);
        while (x == c0 || x == c1) x = unif(rng) * state.range(0);
        oo_gate::add_gate(gs, oo_gate::toffoli_gate(c0, c1, x));
      } else if (id == 4) {
        size_t const c = unif(rng) * state.range(0);
        size_t x = unif(rng) * state.range(0);
        size_t y = unif(rng) * state.range(0);
        while (x == c) x = unif(rng) * state.range(0);
        while (y == c || y == x) x = unif(rng) * state.range(0);
        oo_gate::add_gate(gs, oo_gate::fredkin_gate(c, x, y));
      }
    }
    state.ResumeTiming();
    auto z = apply_gates(bits, gs);
  }
}
BENCHMARK(BM_ObjectOrientedGatesEval)
    ->Args({100000});

