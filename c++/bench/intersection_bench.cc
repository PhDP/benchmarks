#include "benchmark/benchmark.h"
#include "benchset/intersection.hh"
#include <random>

static void BM_IntersectionWithStdSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};
    auto ys = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stdset_intersection(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithStdSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithStdSetEmplaceHint(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::set<int>{};
    auto ys = std::set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stdset_intersection_eh(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithStdSetEmplaceHint)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithFlatSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};
    auto ys = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::flatset_intersection(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithFlatSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithFlatSetEmplaceHint(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = boost::container::flat_set<int>{};
    auto ys = boost::container::flat_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::flatset_intersection_eh(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithFlatSetEmplaceHint)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithUSetInsert(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::unordered_set<int>{};
    auto ys = std::unordered_set<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) xs.insert(unif(rng));
    while ((signed)ys.size() < state.range(0)) ys.insert(unif(rng));

    state.ResumeTiming();
    auto z = benchunion::stduset_intersection(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithUSetInsert)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithVector(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};
    auto ys = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique(xs, unif(rng));
    while ((signed)ys.size() < state.range(0)) benchunion::insert_unique(ys, unif(rng));

    state.ResumeTiming();
    auto z = benchunion::vectorset_intersection(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithVector)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});

static void BM_IntersectionWithVectorNoBack(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    auto xs = std::vector<int>{};
    auto ys = std::vector<int>{};

    auto unif = std::uniform_int_distribution<int>();
    auto rng = std::mt19937_64(state.range(0));

    while ((signed)xs.size() < state.range(0)) benchunion::insert_unique_noback(xs, unif(rng));
    while ((signed)ys.size() < state.range(0)) benchunion::insert_unique_noback(ys, unif(rng));

    state.ResumeTiming();
    auto z = benchunion::vectorset_intersection_noback(xs, ys);
  }
}
BENCHMARK(BM_IntersectionWithVectorNoBack)
    ->Args({100})
    ->Args({1000})
    ->Args({10000})
    ->Args({100000});
