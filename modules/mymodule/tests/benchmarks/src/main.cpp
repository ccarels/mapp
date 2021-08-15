#include <string>
#include <benchmark/benchmark.h>

#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service.hpp"
#include "mymodule.hpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;

/**
 * \brief A benchmark test for \ref mapp::algorithm::mymodule.
 */
static void BM_MYMODULE(benchmark::State& state) {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems
  mapp::algorithm::mymodule m;
  m._config = std::make_shared<mapp::mymodule_config>();
  m._config->set_param(1.0);

  for(const auto &i : state) {
    m.init("/mymodule/config", svc_locator);
    m.exec("/mymodule/config", svc_locator);
  }
}

BENCHMARK(BM_MYMODULE);

BENCHMARK_MAIN();
