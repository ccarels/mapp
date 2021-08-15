#ifndef py_managed_processor_hpp
#define py_managed_processor_hpp

#include "../algorithm/managed.hpp"
#include "../algorithm/processor.hpp"
#include "../library/provider.hpp"
#include "../python/py_shared_ptr.hpp"
#include "../services/service_locator.hpp"

namespace mapp::core::py {
extern "C" {
/**
 * \brief Dynamically loads a new instance of a class using the provided loader.
 * \param load A pointer to a loader instance for the requested class instance.
 * \return A py_shared_ptr to a \ref mapp::core::algorithm::managed< \ref mapp::core::algorithm::processor >>
 */
auto py_managed_processor_instance(py_shared_ptr<mapp::core::library::loader<mapp::core::algorithm::processor, mapp::core::algorithm::managed<mapp::core::algorithm::processor>>>* load) -> mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>*;

/**
 * \brief Calls the destructor of a managed class.
 * \param obj A pointer to a managed class instance for which to call the destructor.
 */
void py_managed_processor_dtr(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj);

/**
 * \brief Calls the \ref mapp::core::algorithm::managed::init() method of the managed class.
 * \param obj A pointer to a managed class instance for which to call this method.
 * \param path A human-readable reference to the location in the runtime file system to refer to the location where configuration data for the underlying algorithm should be stored.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the runtime file system storage.
 */
void py_managed_processor_init(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj, char const* const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>* loc);

/**
 * \brief Calls the \ref mapp::core::algorithm::managed::exec() method of a managed class.
 * \param obj A pointer to a managed class instance for which to call this method.
 * \param path A human-readable reference to a location in the runtime file system to refer to the location where configuration data for the underlying algorithm should be stored.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the runtime file system storage.
 */
void py_managed_processor_exec(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>>* const obj, char const* const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator>* const loc);
}
}  // namespace mapp::core::py

#endif
