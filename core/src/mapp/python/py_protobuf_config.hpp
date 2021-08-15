#ifndef py_protobuf_config_hpp
#define py_protobuf_config_hpp

#include "../algorithm/managed.hpp"
#include "../algorithm/processor.hpp"
#include "../python/py_shared_ptr.hpp"

namespace mapp::core::py {
extern "C" {
/**
 * \brief Add a Protobuf configuration object belonging to a \ref mapp::core::algorithm::processor to the runtime file system.
 * \param obj A base class pointer to a derived class algorithm which encapsulates the Protobuf object, and which is used to invoke the serialization routine of the relevant derived class.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the storage for the algorithm object that encapsulates the Protobuf configuration object.
 * \param path A human-readable reference to the location in the runtime file system to refer to the location where the derived class algorithm object is/shall be stored which encapsulates the Protobuf configuration object.
 * \param protobuf_string The serialized Protobuf configuration object represented as a std::string. A (Python) user should serialize the Protobuf object and provide it in this parameter.
 * \exception std::logic_error A std::logic_error is thrown if the provided obj does not conform to the \ref mapp::core::algorithm::protobuf_config class.
 */
void py_set_protobuf_config(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc, char const *const path, char const *const protobuf_string);

/**
 * \brief Retrieve a serialized Protobuf configuration object from the runtime file system represented as a std::string.
 * \param obj A base class pointer to a derived class algorithm which encapsulates the Protobuf object, and which is used to invoke the serialization routine of the relevant derived class.
 * \param loc The \ref mapp::core::services::service_locator that is used to provide an interface to the storage for the algorithm object that encapsulates the Protobuf configuration object.
 * \param path A human-readable reference to the location in the runtime file system to refer to the location where the derived class algorithm object is stored which encapsulates the Protobuf configuration object.
 * \return A pointer to an array containing the serialized Protobuf object. A (Python) user should deserialize the returned array to obtain a Protobuf object.
 * \exception std::logic_error A std::logic_error is thrown if the provided obj does not conform to the \ref mapp::core::algorithm::protobuf_config class.
 */
auto py_get_protobuf_config(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc, char const *const path) -> py_shared_ptr<std::string> *;

/**
 * \brief Obtain a char buffer from a \ref mapp::core::py::py_shared_ptr < std::string >.
 * \param obj A pointer to a \ref mapp::core::py::py_shared_ptr< std::string >.
 * \return A char buffer representation of the std::string that is contained inside obj.
 */
auto py_shared_ptr_c_str(py_shared_ptr<std::string> const *const obj) -> char const *;
}
}  // namespace mapp::core::py

#endif
