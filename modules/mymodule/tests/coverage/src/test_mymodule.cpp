#include <string>

#include "gmock/gmock.h"

#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service.hpp"
#include "mymodule.cpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;

/**
 * \brief A coverage test for \ref mapp::algorithm::mymodule.
 */
TEST(mapp_mymodule_coverage, test_mymodule) {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems
  auto m = new mapp::algorithm::mymodule();
  m->name();
  m->_config = std::make_shared<mapp::mymodule_config>();
  m->_config->set_param(1.0);
  m->init("/mymodule/config", svc_locator); // The first time this line runs, data is not in the store,
  m->init("/mymodule/config", svc_locator); // so call this method again to achieve complete coverage in the try block of this method.
  m->exec("/mymodule/config", svc_locator); // Test try block in exec method
  m->exec("", svc_locator); // Test catch block in exec method.
  m->set_mock_data("", svc_locator);

  // Test success cases
  auto rconfig = std::make_shared<mapp::mymodule_config>();
  std::string serialized = "";
  m->to_string(serialized, "/mymodule/config", svc_locator);
  m->from_string(serialized, "/mymodule/config", svc_locator);

  // Test failure cases
  try { m->to_string(serialized, "", svc_locator); } // Test failure to get a resource which results in a throw
  catch(std::invalid_argument &) {}
  m->from_string(serialized, "", svc_locator); // Test failure to parse

  // Put a generic service in the file system store
  auto s0 = std::make_shared<service>();
  auto algo_svc_path = svc_locator->_svc_fs->get("algo_svc");
  algo_svc_path._res->put("", s0);
  m->to_string(serialized, "", svc_locator); // Test failure to obtain the correct resource, resulting in failure to serialize the data to a string

  delete m;
}

TEST(mapp_mymodule_coverage, test_mymodule_export) {
  auto m = construct();
  destruct(m);
}
