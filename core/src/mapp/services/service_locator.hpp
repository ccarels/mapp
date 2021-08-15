#ifndef service_locator_hpp
#define service_locator_hpp

#include "../filesystem/fs.hpp"
#include "../services/service.hpp"

namespace mapp::core::services {
/**
 * \class service_locator
 * \brief A class that contains a \ref mapp::core::filesystem::fs of multiple \ref mapp::core::filesystem::fs, functioning like a filesystem of filesystems that contain pointers to \ref mapp::core::services::service objects, and functioning like a
 * service locator.
 */
class service_locator final {
 public:
  /**
   * \brief Constructor for \ref mapp::core::services::service_locator that wraps a runtime file system of runtime file systems for services.
   * \param svc_fs A std::shared_ptr to the file system of file systems encapsulating abstract services.
   */
  explicit service_locator(std::shared_ptr<mapp::core::filesystem::fs<mapp::core::filesystem::fs<mapp::core::services::service>>> svc_fs) : _svc_fs(std::move(svc_fs)) {}
  ~service_locator() = default;
  std::shared_ptr<mapp::core::filesystem::fs<mapp::core::filesystem::fs<mapp::core::services::service>>> _svc_fs; /**< A filesystem of filesystems to abstract services */
};
}  // namespace mapp::core::services

#endif
