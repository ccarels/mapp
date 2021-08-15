#ifndef mymodule_hpp
#define mymodule_hpp

#include "mapp/algorithm/processor.hpp"
#include "mapp/algorithm/protobuf_config.hpp"
#include "mapp/services/service_locator.hpp"
#include "mapp/tests/mockable.hpp"
#include "mymodule/mymodule_data_model.hpp"
#include "mymodule/generated/cpp/mymodule_config_data_model.pb.h"

#define MODULE mymodule
#define MODULE_NAME_STRING "mymodule"

namespace mapp::algorithm {
/**
 * \brief An example module implementation.
 */
class MODULE final : public mapp::core::algorithm::processor, public mapp::core::algorithm::protobuf_config, public mapp::core::tests::mockable {
    public:
    MODULE() = default;
    ~MODULE() = default;

    /**
     * \brief The name of the module.
     * \return The name of the module as a std::string.
     */
    auto name() const noexcept -> const std::string override { return std::string(MODULE_NAME_STRING); }

    /**
    * \brief Initializes the module, checks and sets a valid configuration setting.
    * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
    * \param svc A service locator that is used to access the runtime file system.
    * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
    */
    auto init(const std::string &path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> STATUS override;

    /**
    * \brief Calls the exec method of the managed class.
    * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
    * \param svc A service locator that is used to access the runtime file system.
    * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
    */
    auto exec(const std::string &path, std::shared_ptr<mapp::core::services::service_locator> &svc) const -> STATUS override;

    /**
    * \brief Deserialize a serialized Protobuf string to a \ref mapp::mymodule_config object, placing it in the runtime file system store at the provided path.
    * \param config_string A serialized Protobuf string representation of a \ref mapp::mymodule_config object.
    * \param svc_path The location in the runtime file system where the deserialized \ref mapp::mymodule_config object should be placed.
    * \param svc A service locator that is used to access the runtime file system.
    * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
    */
    auto from_string(const std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code;

    /**
    * \brief Serialize a Protobuf object at a runtime file system location to a Protobuf std::string representation.
    * \param config_string A serialized Protobuf string representation of a \ref mapp::mymodule_config object that this method sets.
    * \param svc_path The location in the runtime file system where the deserialized \ref mapp::mymodule_config object is located.
    * \param svc A service locator that is used to access the runtime file system.
    * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
    */
    auto to_string(std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code;

    /// \todo Generate mock data and set it in the provided svc_path
    void set_mock_data(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const;

    std::shared_ptr<mapp::mymodule_config> _config;
};
}

#endif
