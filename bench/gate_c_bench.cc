#include "benchmark/benchmark.h"
#include "gates/c.h"
#include <random>
#include <vector>

auto random_c_bits(std::mt19937_64& rng, size_t nmemb) -> bool* {
  bool* bits = (bool*)malloc(nmemb * sizeof(bool));
  auto unif = std::uniform_real_distribution<double>(0.0, 1.0);
  for (auto i = 0u; i < nmemb; ++i) {
    bits[i] = (unif(rng) < 0.5);
  }
  return bits;
}

static void BM_CGatesEval(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto unif = std::uniform_real_distribution<double>(0.0, 1.0);
    auto rng = std::mt19937_64(state.range(0));

    bool* bits = random_c_bits(rng, state.range(0));

    c_gate* gs = (c_gate*)malloc(state.range(0) * sizeof(c_gate));
    for (auto i = 0u; i < state.range(0); ++i) {
      size_t const id = unif(rng) * 5.0;
      if (id == 0) {
        uint32_t const x = unif(rng) * state.range(0);
        c_gate g;
        g.kind = c_not_gate_t;
        g.n = { x: x };
        gs[i] = g;
      } else if (id == 1) {
        uint32_t const c = unif(rng) * state.range(0);
        uint32_t x = unif(rng) * state.range(0);
        while (x == c) x = unif(rng) * state.range(0);
        c_gate g;
        g.kind = c_cnot_gate_t;
        g.c = { c: c, x: x };
        gs[i] = g;
      } else if (id == 2) {
        uint32_t const x = unif(rng) * state.range(0);
        uint32_t y = unif(rng) * state.range(0);
        while (y == x) y = unif(rng) * state.range(0);
        c_gate g;
        g.kind = c_swap_gate_t;
        g.s = { a: x, b : y};
        gs[i] = g;
      } else if (id == 3) {
        uint32_t const c0 = unif(rng) * state.range(0);
        uint32_t c1 = unif(rng) * state.range(0);
        uint32_t x = unif(rng) * state.range(0);
        while (c1 == c0) c1 = unif(rng) * state.range(0);
        while (x == c0 || x == c1) x = unif(rng) * state.range(0);
        c_gate g;
        g.kind = c_toffoli_gate_t;
        g.t = { c0: c0, c1: c1, x: x };
        gs[i] = g;
      } else if (id == 4) {
        uint32_t const c = unif(rng) * state.range(0);
        uint32_t x = unif(rng) * state.range(0);
        uint32_t y = unif(rng) * state.range(0);
        while (x == c) x = unif(rng) * state.range(0);
        while (y == c || y == x) x = unif(rng) * state.range(0);
        c_gate g;
        g.kind = c_fredkin_gate_t;
        g.f = { c: c, a: x, b: y };
        gs[i] = g;
      }
    }
    state.ResumeTiming();
    apply_c_gates(bits, state.range(0), gs, state.range(0));
    free(gs);
    free(bits);
  }
}
BENCHMARK(BM_CGatesEval)
    ->Args({100000});
