#include "null_algorithm.hpp"

MAPP_EXPORT_MODULE(mapp::core::algorithm::null_algorithm)

auto mapp::core::algorithm::null_algorithm::exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS { return STATUS_CODE(status_code::success); }
