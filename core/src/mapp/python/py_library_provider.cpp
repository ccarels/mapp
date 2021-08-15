#include "py_library_provider.hpp"

#include <iostream>

#include "../algorithm/managed.hpp"
#include "../library/locator.hpp"
#include "../library/provider.hpp"

namespace mapp::core::py {
extern "C" {
auto py_library_provider(char const *const path) -> MANAGED_PROCESSOR_PROVIDER * {
  auto lloc = std::make_shared<mapp::core::library::locator>();
  lloc->load_config_file(path);
  return new MANAGED_PROCESSOR_PROVIDER(lloc);  // Tells the provider where to find libraries
}

void py_library_provider_dtr(MANAGED_PROCESSOR_PROVIDER const *const obj) { delete obj; }
auto py_library_provider_get(MANAGED_PROCESSOR_PROVIDER const *const obj, char const *const m, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> const *const svc_locator) -> py_shared_ptr<MANAGED_PROCESSOR_LOADER> * {
  auto l = new py_shared_ptr<MANAGED_PROCESSOR_LOADER>(obj->get(m));
  svc_locator->_p->_svc_fs->get("algo_svc")._res->register_loader(l->_p);
  return l;
}
void py_library_loader_dtr(py_shared_ptr<MANAGED_PROCESSOR_LOADER> *obj) { delete obj; }
}
}  // namespace mapp::core::py
