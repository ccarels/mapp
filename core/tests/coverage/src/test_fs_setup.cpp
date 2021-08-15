#include "gmock/gmock.h"
#include "mapp/filesystem/fs_setup.hpp"

using namespace mapp::core::filesystem;

namespace mapp::core::tests::coverage_tests {
/**
 * \brief A coverage test for \ref mapp::core::filesystem::fs_setup.
 */
TEST(mapp_core_coverage, test_fs_setup) { auto m = fs_setup(); }
}  // namespace mapp::core::tests::coverage_tests
