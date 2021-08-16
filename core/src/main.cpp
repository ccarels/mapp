#include <Python.h>
#include <google/protobuf/api.pb.h>

#include <future>
#include <iostream>

#include "mapp/algorithm/managed.hpp"
#include "mapp/algorithm/processor.hpp"
#include "mapp/filesystem/fs.hpp"
#include "mapp/library/locator.hpp"
#include "mapp/library/provider.hpp"
#include "mapp/model/data_model_interface.hpp"
#include "mapp/pipeline/sequence.hpp"
#include "mapp/services/service_locator.hpp"

/**
 * \brief main executable to try out features during development.
 * \return 0 on success, 1 otherwise.
 */
auto main() -> int {
  using mapp::core::algorithm::managed;
  using mapp::core::algorithm::processor;
  using mapp::core::filesystem::fs;
  using mapp::core::library::loader;
  using mapp::core::library::locator;
  using mapp::core::library::provider;
  using mapp::core::model::data_model;
  using mapp::core::pipeline::sequence;
  using mapp::core::services::service;
  using mapp::core::services::service_locator;

  GOOGLE_PROTOBUF_VERIFY_VERSION;

  /// Create a service filesystem that contains service locators
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<service_locator>(svc_fs);

  /// Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  /// Put the algorithm filesystem in the filesystem of filesystems

  /// Configure the provider for library locators
  auto lloc = std::make_shared<locator>();
  lloc->load_config_file("./config.txt");
  const auto provide = provider<processor, managed<processor>>(lloc);  /// Tells the provider where to find libraries

  /// Configure a pipeline
  auto pipeline = sequence();
  auto mymodule = provide.get("mymodule");
  svc_locator->_svc_fs->get("algo_svc")._res->register_loader(mymodule);
  auto mymodule_ptr = mymodule->instance();
  pipeline.put_module_init(mymodule_ptr, "", svc_locator);
  pipeline.put_module_exec(mymodule_ptr, "", svc_locator);

  auto null_module = provide.get("null_algorithm");
  svc_locator->_svc_fs->get("algo_svc")._res->register_loader(null_module);
  auto null_module_ptr = null_module->instance();
  pipeline.put_module_init(null_module_ptr, "", svc_locator);
  pipeline.put_module_exec(null_module_ptr, "", svc_locator);

  // Uncomment these lines to run a Python module
  //auto pymodule = provide.get("pymodule_template");
  //svc_locator->_svc_fs->register_loader(pymodule);
  //auto pyptr = pymodule->instance();

  //pipeline.put_module_init(pyptr, "/pymodule_template/config", svc_locator);
  //pipeline.put_module_exec(pyptr, "", svc_locator);

  /// Run two pipelines on separate threads
  // Py_Initialize();
  // PyThreadState *_save = nullptr;
  //_save = PyEval_SaveThread();
  auto p2 = pipeline;
  auto f1 = std::async(std::launch::async, &sequence::execute, &pipeline);
  auto f2 = std::async(std::launch::async, &sequence::execute, &p2);
  f1.get();
  f2.get();
  // PyEval_RestoreThread(_save);

  // auto gstate = PyGILState_Ensure();
  // if(gstate == PyGILState_LOCKED) { Py_FinalizeEx(); }

  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
