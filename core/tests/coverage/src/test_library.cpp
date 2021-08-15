#include "gmock/gmock.h"
#include "mapp/algorithm/managed.hpp"
#include "mapp/algorithm/processor.hpp"
#include "mapp/library/locator.hpp"
#include "mapp/library/provider.hpp"

using namespace mapp::core::algorithm;
using namespace mapp::core::library;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::library::locator, \ref mapp::core::library::provider, \ref mapp::core::library::loader.
 */
TEST(mapp_core_coverage, test_library) {
  auto l = std::make_shared<locator>();
  l->load_config_file("../../../build/config.txt");
  const auto p = provider<processor, managed<processor>>(l);

  auto m0 = p.get("null_algorithm");
  const auto m0_ptr = m0->instance();

  try { auto m2 = p.get("non_compliant_algorithm"); }
  catch (std::invalid_argument&) {}

  auto m1 = p.get("");
  const auto m1_ptr = m1->instance();

  // Test case where config file cannot be opened
  try { l->load_config_file(""); }
  catch(std::invalid_argument&) {}
}
}  // namespace mapp::core::tests::coverage_tests
