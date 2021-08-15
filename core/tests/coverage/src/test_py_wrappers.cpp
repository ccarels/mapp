#include "gmock/gmock.h"
#include "mapp/python/py_library_provider.hpp"
#include "mapp/python/py_managed_processor.hpp"
#include "mapp/python/py_pipeline_sequence.hpp"
#include "mapp/python/py_protobuf_config.hpp"
#include "mapp/python/py_service_locator.hpp"
#include "mymodule/generated/cpp/mymodule_config_data_model.pb.h"

using namespace mapp::core::py;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::algorithm::processor.
 */
TEST(mapp_core_coverage, test_py_wrappers) {
  auto svc = py_service_locator();
  auto p = py_library_provider("../../../build/config.txt");
  auto mp = py_library_provider_get(p, "mymodule", svc);
  auto m = py_managed_processor_instance(mp);

  /// Set Protobuf configuration
  auto config_path = "/mymodule/config";
  double test_value = 1.0;

  auto config = std::make_shared<mapp::mymodule_config>();
  config->set_param(test_value);
  std::string config_string = "";
  config->SerializeToString(&config_string);
  py_set_protobuf_config(m, svc, config_path, config_string.c_str());

  // Test a configuration that raises an exception
  auto mp2 = py_library_provider_get(p, "null_algorithm", svc);
  auto m2 = py_managed_processor_instance(mp2);
  py_set_protobuf_config(m2, svc, config_path, config_string.c_str());
  auto r2str = py_get_protobuf_config(m2, svc, config_path);

  delete m2;
  delete mp2;
  delete r2str;

  /// Get Protobuf configuration
  auto rconfig = std::make_shared<mapp::mymodule_config>();
  auto rstr = py_get_protobuf_config(m, svc, config_path);
  if (rstr->_p) { rconfig->ParseFromString(*rstr->_p); }

  /// Get Protobuf configuration from a char const*
  auto rstr_c_str = py_shared_ptr_c_str(rstr);
  auto rconfig_2 = std::make_shared<mapp::mymodule_config>();
  rconfig_2->ParseFromString(rstr_c_str);

  /// Test Protobuf configuration values
  EXPECT_EQ(config->param(), test_value);
  EXPECT_EQ(config->param(), rconfig->param());
  EXPECT_EQ(config->param(), rconfig_2->param());

  /// Run an algorithm
  py_managed_processor_init(m, config_path, svc);
  py_managed_processor_exec(m, config_path, svc);

  /// Test pipeline sequence
  auto pipeline = py_pipeline_sequence();
  py_pipeline_sequence_put_module_init(pipeline, m, config_path, svc);
  py_pipeline_sequence_put_module_exec(pipeline, m, config_path, svc);
  py_pipeline_sequence_execute(pipeline);
  py_pipeline_sequence_dtr(pipeline);

  // Test destructors
  py_library_loader_dtr(mp);
  py_managed_processor_dtr(m);
  py_library_provider_dtr(p);
  py_service_locator_dtr(svc);
  delete rstr;
}

}  // namespace mapp::core::tests::coverage_tests
