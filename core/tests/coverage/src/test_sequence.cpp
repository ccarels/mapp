#include "gmock/gmock.h"
#include "mapp/algorithm/managed.hpp"
#include "mapp/algorithm/processor.hpp"
#include "mapp/algorithm/throwing_algorithm/throwing_algorithm.hpp"
#include "mapp/pipeline/sequence.hpp"
#include "mapp/services/service_locator.hpp"

using namespace mapp::core::filesystem;
using namespace mapp::core::services;
using namespace mapp::core::algorithm;
using namespace mapp::core::pipeline;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::pipeline::sequence.
 */
TEST(mapp_core_coverage, test_sequence) {
  auto svc_fs = std::make_shared<fs<fs<service>>>();
  auto svc = std::make_shared<service_locator>(svc_fs);
  auto p = std::make_shared<processor>();
  auto m = std::make_shared<managed<processor>>(p);
  auto pipeline = new sequence();
  pipeline->put_module_init(m, "", svc);
  pipeline->put_module_exec(m, "", svc);
  pipeline->execute();
  delete pipeline;
}
}  // namespace mapp::core::tests::coverage_tests
