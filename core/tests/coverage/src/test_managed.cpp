#include "gmock/gmock.h"
#include "mapp/algorithm/managed.hpp"
#include "mapp/algorithm/processor.hpp"
#include "mapp/algorithm/throwing_algorithm/throwing_algorithm.hpp"
#include "mapp/services/service_locator.hpp"

using namespace mapp::core::filesystem;
using namespace mapp::core::services;
using namespace mapp::core::algorithm;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::algorithm::managed.
 */
TEST(mapp_core_coverage, test_managed) {
  auto svc_fs = std::make_shared<fs<fs<service>>>();
  auto svc = std::make_shared<service_locator>(svc_fs);
  auto p = std::make_shared<processor>();
  auto m = managed<processor>(p);
  m.algorithm();
  m.init("", svc);
  m.exec("", svc);

  auto p2 = std::make_shared<throwing_algorithm>();
  auto p2_name = p2->name().empty();
  auto m2 = managed<processor>(p2);
  try { m2.init("", svc); }
  catch (std::logic_error &) {}
  try { m2.exec("", svc); }
  catch (std::logic_error &) {}

  // Test the dynamic branch to achieve complete coverage of this class.
  auto p3 = new throwing_algorithm();
  auto p3_name = p3->name();
  try { p3->init("", svc); }
  catch (std::logic_error &) {}
  try { p3->exec("", svc); }
  catch (std::logic_error &) {}
  delete p3;
}
}  // namespace mapp::core::tests::coverage_tests
