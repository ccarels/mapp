#include "gmock/gmock.h"
#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service.hpp"

using namespace mapp::core::services;
using namespace mapp::core::filesystem;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::filesystem::fs< \ref mapp::core::services::service >.
 */
TEST(mapp_core_coverage, test_fs) {
  auto algo_fs = fs<service>();
  auto s0 = std::make_shared<service>();
  s0->name();

  algo_fs.put("/service/", s0);
  algo_fs.convert_put("/service/", s0);
  algo_fs.get("/service/");
  algo_fs.rm("/service/");
  algo_fs.rm("");

  try { algo_fs.get(""); }  // mapp::core::filesystem::fs will throw if this resource does not exist.
  catch (const std::invalid_argument&) {}

  /// Test the dynamic branch of mapp::core::services::service.
  auto s1 = new service();
  delete s1;
}
}  // namespace mapp::core::tests::coverage_tests
