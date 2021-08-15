#ifndef py_service_locator_hpp
#define py_service_locator_hpp

#include "../python/py_shared_ptr.hpp"
#include "../services/service_locator.hpp"

namespace mapp::core::py {
extern "C" {
/**
 * \brief A (Python) interface to obtain a \ref mapp::core::services::service_locator.
 * \return A \ref mapp::core::py::py_shared_ptr to a \ref mapp::core::services::service_locator.
 */
auto py_service_locator() -> mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>*;

/**
 * \brief A (Python) interface to destruct a mapp::core::services::service_locator.
 * \param obj A \ref mapp::core::py::py_shared_ptr to a \ref mapp::core::services::service_locator.
 */
void py_service_locator_dtr(mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> const* const obj);
}
}  // namespace mapp::core::py

#endif
