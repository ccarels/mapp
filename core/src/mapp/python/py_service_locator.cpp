#include "py_service_locator.hpp"

#include "../filesystem/fs_setup.hpp"

namespace mapp::core::py {
extern "C" {
auto py_service_locator() -> mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>* {
  auto svc_locator = mapp::core::filesystem::fs_setup();
  return new mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>(svc_locator);
}

void py_service_locator_dtr(mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> const* const obj) { delete obj; }
}
}  // namespace mapp::core::py
