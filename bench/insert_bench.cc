#include "benchmark/benchmark.h"
#include "benchset/insert_unique.hh"
#include <random>
#include <set>
#include <vector>
#include <unordered_set>
#include <boost/container/flat_set.hpp>

static void BM_InsertIntoStdSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    state.ResumeTiming();
    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
  }
}
BENCHMARK(BM_InsertIntoStdSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_InsertIntoFlatSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    state.ResumeTiming();
    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
  }
}
BENCHMARK(BM_InsertIntoFlatSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_InsertIntoUSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::unordered_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    state.ResumeTiming();
    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
  }
}
BENCHMARK(BM_InsertIntoUSet)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_InsertIntoUniqueVector(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    state.ResumeTiming();
    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique(xs, unif(rng));
  }
}
BENCHMARK(BM_InsertIntoUniqueVector)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_InsertIntoUniqueVectorNoBack(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    state.ResumeTiming();
    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique_noback(xs, unif(rng));
  }
}
BENCHMARK(BM_InsertIntoUniqueVectorNoBack)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});
