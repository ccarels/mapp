#include <string>

#include <Python.h>
#include "gmock/gmock.h"

#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service.hpp"
#include "pymodule_template.cpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;

/**
 * \brief A coverage test for \ref mapp::algorithm::pymodule_template.
 */
TEST(mapp_pymodule_template_coverage, test_pymodule_template) {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems
  auto m = new mapp::algorithm::pymodule_template();
  m->name();
  m->_config = std::make_shared<mapp::pymodule_template_config>();
  m->_config->set_script_path("../../../python/pymodule_template.py");
  const std::string pymodule_template_config_path = "/pymodule_template/config";

  // Put config object in store
  auto m_configured = std::make_shared<mapp::algorithm::pymodule_template>();
  m_configured->_config = m->_config;
  auto algo_svc_path = svc_locator->_svc_fs->get("algo_svc");
  auto algo_obj = data_model_interface<MODULE, mapp::core::services::service>::get(m_configured);
  algo_svc_path._res->put(pymodule_template_config_path, algo_obj);

  m->init(pymodule_template_config_path, svc_locator);
  Py_Initialize();
  PyThreadState *_save;
  _save = PyEval_SaveThread();
  m->exec(pymodule_template_config_path, svc_locator);
  PyEval_RestoreThread(_save);
  auto gstate = PyGILState_Ensure();
  if(gstate == PyGILState_LOCKED) { Py_FinalizeEx(); }

  // Test success cases
  auto rconfig = std::make_shared<mapp::pymodule_template_config>();
  std::string serialized = "";
  m->to_string(serialized, pymodule_template_config_path, svc_locator);
  m->from_string(serialized, pymodule_template_config_path, svc_locator);

  // Test failure cases
  try { m->to_string(serialized, "", svc_locator); } // Test failure to get a resource which results in a throw
  catch(std::invalid_argument &) {}
  m->from_string(serialized, "", svc_locator); // Test failure to parse

  // Put a generic service in the file system store
  auto s0 = std::make_shared<service>();
  algo_svc_path._res->put("", s0);
  m->to_string(serialized, "", svc_locator); // Test failure to obtain the correct resource, resulting in failure to serialize the data to a string

  delete m;
}

/**
 * \brief A coverage test for \ref mapp::algorithm::pymodule_template where configuration happens internal to the class.
 */
TEST(mapp_pymodule_template_coverage, test_pymodule_template_internal_configuration) {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems
  auto m = new mapp::algorithm::pymodule_template();
  m->name();
  m->_config = std::make_shared<mapp::pymodule_template_config>();
  m->_config->set_script_path("../../../python/pymodule_template.py");
  const std::string pymodule_template_config_path = "/pymodule_template/config";

  m->init(pymodule_template_config_path, svc_locator);

  delete m;
}

/**
 * \brief A coverage test for \ref mapp::algorithm::pymodule_template for the exported constructor and destructor functions for the module.
 */
TEST(mapp_pymodule_template_coverage, test_pymodule_template_export) {
  auto m = construct();
  destruct(m);
}
