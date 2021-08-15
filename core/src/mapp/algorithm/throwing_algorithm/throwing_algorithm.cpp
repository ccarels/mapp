#include "throwing_algorithm.hpp"

#include <iostream>
using namespace mapp::core::algorithm;
#define MODULE throwing_algorithm
MAPP_EXPORT_MODULE(MODULE)

auto mapp::core::algorithm::throwing_algorithm::init(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) -> STATUS {
  std::cout << "Running: throwing_algorithm::init()" << std::endl;
  throw std::invalid_argument("throwing_module throws an invalid_argument exception.");
}

auto mapp::core::algorithm::throwing_algorithm::exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS {
  std::cout << "Running: throwing_algorithm::exec()" << std::endl;
  throw std::invalid_argument("throwing_module throws an invalid_argument exception.");
}
