#include <benchmark/benchmark.h>

#include <string>

#include "mapp/algorithm/managed.hpp"
#include "mapp/algorithm/null_algorithm/null_algorithm.hpp"
#include "mapp/algorithm/processor.hpp"
#include "mapp/filesystem/fs.hpp"
#include "mapp/library/locator.hpp"
#include "mapp/library/provider.hpp"
#include "mapp/services/service.hpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;
using namespace mapp::core::library;
using namespace mapp::core::algorithm;

/**
 * \brief A benchmark test for \ref mapp::core::filesystem::fs< \ref mapp::core::services::service >.
 */
static void BM_MAPP_CORE(benchmark::State& state) {
  auto algo_fs = fs<service>();
  auto s0 = std::make_shared<service>();
  unsigned long long idx = 0;
  for (auto _ : state) {
    auto p = "/module/" + std::to_string(idx++);
    benchmark::DoNotOptimize(algo_fs.put(p, s0));
    benchmark::DoNotOptimize(algo_fs.get(p));
  }
  state.SetComplexityN(state.range(0));
}

/**
 * \brief A benchmark test for \ref mapp::core::library::loader.
 */
static void BM_MAPP_LIBRARY_LOADER(benchmark::State& state) {
  auto l = std::make_shared<locator>();
  l->load_config_file("../../../build/config.txt");
  const auto p = provider<processor, managed<processor>>(l);
  auto m0 = p.get("null_algorithm");
  for (auto _ : state) { const auto m0_ptr = m0->instance(); }
}

/**
 * \brief A benchmark test for \ref mapp::core::algorithm::processor allocations, to compare to \ref mapp::core::library::loader allocations.
 */
static void BM_MAPP_ALGORITHM_PROCESSOR_ALLOCATIONS(benchmark::State& state) {
  for (auto _ : state) { const auto m0_ptr = std::make_shared<null_algorithm>(); }
}

// Register the function as a benchmark
BENCHMARK(BM_MAPP_CORE)->RangeMultiplier(2)->Range(1 << 10, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_MAPP_LIBRARY_LOADER);
BENCHMARK(BM_MAPP_ALGORITHM_PROCESSOR_ALLOCATIONS);

BENCHMARK_MAIN();
