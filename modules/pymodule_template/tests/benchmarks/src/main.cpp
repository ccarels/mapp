#include <string>
#include <Python.h>
#include <benchmark/benchmark.h>

#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service.hpp"
#include "pymodule_template.hpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;

/**
 * \brief A benchmark test for \ref mapp::algorithm::pymodule_template.
 */
static void BM_PYMODULE_TEMPLATE(benchmark::State& state) {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems
  mapp::algorithm::pymodule_template m;
  m._config = std::make_shared<mapp::pymodule_template_config>();
  m._config->set_script_path("../../../python/pymodule_template.py");

  Py_Initialize();
  for(const auto &i : state) {
    m.init("/pymodule_template/config", svc_locator);
    PyThreadState *_save;
    _save = PyEval_SaveThread();
    m.exec("/pymodule_template/config", svc_locator);
    PyEval_RestoreThread(_save);
  }

  auto gstate = PyGILState_Ensure();
  if(gstate == PyGILState_LOCKED) { Py_FinalizeEx(); }
}

BENCHMARK(BM_PYMODULE_TEMPLATE);

BENCHMARK_MAIN();
