#include "gmock/gmock.h"

/**
 * \brief A namespace for coverage tests.
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
