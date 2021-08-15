#ifndef protobuf_config_hpp
#define protobuf_config_hpp

#include "../services/service_locator.hpp"
#include "../status_code/status_code.hpp"

namespace mapp::core::algorithm {
/**
 * \class protobuf_config
 * \brief A base class interface for Protocol buffer based configuration of a module. Modules can use this interface to provide configurability.
 */
class protobuf_config {
 public:
  protobuf_config() noexcept = default;
  virtual ~protobuf_config() noexcept = default;

  /**
   * \brief Parse a Protocol buffer object from a std::string.
   * Derived classes must implement the parsing, setting, and storage of the resulting object in the runtime file system.
   * \param config_string A serialized std::string representation of a Protocol buffer object.
   * \param svc_path A std::string which is a human-readable reference in the runtime file system for the location where the parsed Protocol buffer object should be stored.
   * \param svc The std::shared_ptr to the \ref mapp::core::services::service_locator that should be used by the implementation to store the parsed Protocol buffer object.
   * \return A \ref mapp::core::status_code indicating the result of the call to this method.
   */
  virtual auto from_string(const std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code = 0;

  /**
   * \brief Serialize a Protocol buffer object from the runtime file system to a std::string representation that can be used elsewhere.
   * Derived classes must implement the serialization process.
   * \param config_string A serialized std::string representation of a Protocol buffer object which derived classes must set to the serialized Protocol buffer object.
   * \param svc_path A std::string which is a human-readable reference in the runtime file system for the location from where the parsed Protocol buffer object should be retrieved.
   * \param svc The std::shared_ptr to the \ref mapp::core::services::service_locator that should be used by the implementation to retrieve the Protocol buffer object that should be serialized to a std::string by this method.
   * \return A \ref mapp::core::status_code indicating the result of the call to this method.
   */
  virtual auto to_string(std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code = 0;
};
}  // namespace mapp::core::algorithm

#endif
