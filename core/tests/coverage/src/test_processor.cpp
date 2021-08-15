#include "gmock/gmock.h"
#include "mapp/algorithm/processor.hpp"
#include "mapp/filesystem/fs.hpp"
#include "mapp/services/service_locator.hpp"

using namespace mapp::core::filesystem;
using namespace mapp::core::services;
using namespace mapp::core::algorithm;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::algorithm::processor.
 */
TEST(mapp_core_coverage, test_processor) {
  auto svc_fs = std::make_shared<fs<fs<service>>>();
  auto svc = std::make_shared<service_locator>(svc_fs);

  // Dynamic base class branch
  processor* aba = new processor();
  aba->init("", svc);
  aba->exec("", svc);
  delete aba;
}
}  // namespace mapp::core::tests::coverage_tests
