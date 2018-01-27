#include "benchmark/benchmark.h"
#include "benchset/union.hh"
#include <random>

static void BM_UnionWithStdSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};
    auto ys = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stdset_union(xs, ys);
  }
}
BENCHMARK(BM_UnionWithStdSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithStdSetEmplaceHint(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};
    auto ys = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stdset_union_eh(xs, ys);
  }
}
BENCHMARK(BM_UnionWithStdSetEmplaceHint)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithFlatSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};
    auto ys = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::flatset_union(xs, ys);
  }
}
BENCHMARK(BM_UnionWithFlatSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithFlatSetEmplaceHint(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};
    auto ys = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::flatset_union_eh(xs, ys);
  }
}
BENCHMARK(BM_UnionWithFlatSetEmplaceHint)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithUSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::unordered_set<int>{};
    auto ys = std::unordered_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stduset_union(xs, ys);
  }
}
BENCHMARK(BM_UnionWithUSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithVector(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};
    auto ys = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique(xs, unif(rng));
    while ((signed)ys.size() < state.range(0)) benchunion::insert_unique(ys, unif(rng));

    state.ResumeTiming();
    auto z = benchunion::vectorset_union(xs, ys);
  }
}
BENCHMARK(BM_UnionWithVector)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_UnionWithVectorNoBack(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};
    auto ys = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique_noback(xs, unif(rng));
    while ((signed)ys.size() < state.range(0)) benchunion::insert_unique_noback(ys, unif(rng));

    state.ResumeTiming();
    auto z = benchunion::vectorset_union_noback(xs, ys);
  }
}
BENCHMARK(BM_UnionWithVectorNoBack)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

