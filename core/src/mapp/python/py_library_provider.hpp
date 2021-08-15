#ifndef py_library_provider_hpp
#define py_library_provider_hpp

#include "../algorithm/managed.hpp"
#include "../algorithm/processor.hpp"
#include "../library/provider.hpp"
#include "../python/py_shared_ptr.hpp"

/**
 * \def MANAGED_PROCESSOR_PROVIDER
 * \brief A shorthand for a \ref mapp::core::library::provider object for a \ref mapp::core::algorithm::managed<\ref mapp::core::algorithm::processor>.
 */
#define MANAGED_PROCESSOR_PROVIDER mapp::core::library::provider<mapp::core::algorithm::processor, mapp::core::algorithm::managed<mapp::core::algorithm::processor>>

/**
 * \def MANAGED_PROCESSOR_LOADER
 * \brief A shorthand for a \ref mapp::core::library::loader object for a \ref mapp::core::algorithm::managed<\ref mapp::core::algorithm::processor>.
 */
#define MANAGED_PROCESSOR_LOADER mapp::core::library::loader<mapp::core::algorithm::processor, mapp::core::algorithm::managed<mapp::core::algorithm::processor>>

namespace mapp::core::py {
extern "C" {
/**
 * \brief Obtain a \ref mapp::core::library::provider for a \ref mapp::core::algorithm::managed \ref mapp::core::algorithm::managed<\ref mapp::core::algorithm::processor>.
 * \return A \ref MANAGED_PROCESSOR_PROVIDER.
 */
auto py_library_provider(char const* const path) -> MANAGED_PROCESSOR_PROVIDER*;

/**
 * \brief Calls the destructor on the given \ref mapp::core::library::provider pointer.
 */
void py_library_provider_dtr(MANAGED_PROCESSOR_PROVIDER const* const obj);

/**
 * \brief Obtain a pointer to a \ref mapp::core::library::loader for a \ref mapp::core::algorithm::managed \ref mapp::core::algorithm::managed<\ref mapp::core::algorithm::processor>.
 * \return A \ref py_shared_ptr < \ref MANAGED_PROCESSOR_LOADER >.
 */
auto py_library_provider_get(MANAGED_PROCESSOR_PROVIDER const* const obj, char const* const m, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> const* const svc_locator) -> py_shared_ptr<MANAGED_PROCESSOR_LOADER>*;

/**
 * \brief Calls the destructor on the given \ref mapp::core::library::loader pointer.
 */
void py_library_loader_dtr(py_shared_ptr<MANAGED_PROCESSOR_LOADER>* obj);
}
}  // namespace mapp::core::py

#endif
