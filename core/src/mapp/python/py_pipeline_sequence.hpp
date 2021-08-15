#ifndef py_pipeline_sequence_hpp
#define py_pipeline_sequence_hpp

#include "../algorithm/managed.hpp"
#include "../algorithm/processor.hpp"
#include "../pipeline/sequence.hpp"
#include "../python/py_shared_ptr.hpp"
#include "../services/service_locator.hpp"

namespace mapp::core::py {
extern "C" {
/**
 * \brief Create a new \ref mapp::core::pipeline::sequence instance.
 * \return A \ref mapp::core::py::py_shared_ptr pointer to a new \ref mapp::core::pipeline::sequence.
 */
auto py_pipeline_sequence() -> mapp::core::py::py_shared_ptr<mapp::core::pipeline::sequence> *;

/**
 * \brief Destructor method for \ref mapp::core::pipeline::sequence instance.
 * \param sequence A \ref mapp::core::py::py_shared_ptr pointer to a std::shared_ptr to a \ref mapp::core::pipeline::sequence instance.
 */
void py_pipeline_sequence_dtr(py_shared_ptr<mapp::core::pipeline::sequence> *sequence);

/**
 * \brief Calls the \ref mapp::core::pipeline::sequence::put_module_init method on the provided \ref mapp::core::pipeline::sequence with the provided parameters.
 * \param sequence A pointer to the \ref mapp::core::pipeline::sequence for which the \ref mapp::core::pipeline::sequence::put_module_init method will be called.
 * \param obj A pointer to the \ref mapp::core::algorithm::managed < \ref mapp::core::algorithm::processor > that will be passed to the \ref mapp::core::pipeline::sequence::put_module_init method.
 * \param path A human-readable reference to the location in the runtime file system to refer to the location where configuration data for the underlying algorithm should be stored.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the runtime file system storage.
 */
void py_pipeline_sequence_put_module_init(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence, mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, char const *const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc);

/**
 * \brief Calls the \ref mapp::core::pipeline::sequence::put_module_exec method on the provided \ref mapp::core::pipeline::sequence with the provided parameters.
 * \param sequence A pointer to the \ref mapp::core::pipeline::sequence for which the \ref mapp::core::pipeline::sequence::put_module_exec method will be called.
 * \param obj A pointer to the \ref mapp::core::algorithm::managed < \ref mapp::core::algorithm::processor > that will be passed to the \ref mapp::core::pipeline::sequence::put_module_exec method.
 * \param path A human-readable reference to the location in the runtime file system to refer to the location where configuration data for the underlying algorithm should be stored.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the runtime file system storage.
 */
void py_pipeline_sequence_put_module_exec(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence, mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, char const *const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc);

/**
 * \brief Calls the \ref mapp::core::pipeline::sequence::execute method on the provided \ref mapp::core::pipeline::sequence with the provided parameters.
 * \param sequence A pointer to the \ref mapp::core::pipeline::sequence for which the \ref mapp::core::pipeline::sequence::execute method will be called.
 */
void py_pipeline_sequence_execute(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence);
}
}  // namespace mapp::core::py

#endif
