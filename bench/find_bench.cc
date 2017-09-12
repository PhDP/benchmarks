#include "benchmark/benchmark.h"
#include "benchset/insert_unique.hh"
#include <random>
#include <set>
#include <vector>
#include <unordered_set>
#include <boost/container/flat_set.hpp>

static void BM_FindFromHalfFilledStdSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>(state.range(0) * 2);
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));

    state.ResumeTiming();
    for (auto i = 0; i < state.range(0); ++i)
      xs.find(unif(rng));
  }
}
BENCHMARK(BM_FindFromHalfFilledStdSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_FindFromHalfFilledFlatSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>(state.range(0) * 2);
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));

    state.ResumeTiming();
    for (auto i = 0; i < state.range(0); ++i)
      xs.find(unif(rng));
  }
}
BENCHMARK(BM_FindFromHalfFilledFlatSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_FindFromHalfFilledUSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::unordered_set<int>{};

    auto unif = std::uniform_int_distribution<int>(state.range(0) * 2);
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));

    state.ResumeTiming();
    for (auto i = 0; i < state.range(0); ++i)
      xs.find(unif(rng));
  }
}
BENCHMARK(BM_FindFromHalfFilledUSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_FindFromHalfFilledVector(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>(state.range(0) * 2);
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique(xs, unif(rng));

    state.ResumeTiming();
    for (auto i = 0; i < state.range(0); ++i)
      std::lower_bound(xs.begin(), xs.end(), unif(rng));
  }
}
BENCHMARK(BM_FindFromHalfFilledVector)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});
