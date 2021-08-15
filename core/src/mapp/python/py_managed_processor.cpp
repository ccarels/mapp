#include "py_managed_processor.hpp"

namespace mapp::core::py {
extern "C" {
auto py_managed_processor_instance(py_shared_ptr<mapp::core::library::loader<mapp::core::algorithm::processor, mapp::core::algorithm::managed<mapp::core::algorithm::processor>>>* load) -> mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* { return new mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>(load->_p->instance()); }
void py_managed_processor_dtr(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj) { delete obj; }
void py_managed_processor_init(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj, char const* const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>* loc) { obj->_p->init(path, loc->_p); }
void py_managed_processor_exec(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj, char const* const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>* const loc) { obj->_p->exec(path, loc->_p); }
}
}  // namespace mapp::core::py
