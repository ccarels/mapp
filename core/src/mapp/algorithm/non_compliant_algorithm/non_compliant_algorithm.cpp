#include "non_compliant_algorithm.hpp"

#include <iostream>
// MAPP_EXPORT_MODULE(MODULE) /**< \brief Commenting out this line is one way to make this algorithm non-compliant with the dynamic loading interface of \ref mapp::core::library::loader. */

auto mapp::core::algorithm::non_compliant_algorithm::exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS {
  std::cout << "Running: non_compliant_algorithm::exec()" << std::endl;
  return STATUS_CODE(status_code::success);
}
