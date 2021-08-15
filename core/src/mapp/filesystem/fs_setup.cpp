#include "../filesystem/fs_setup.hpp"

namespace mapp::core::filesystem {
auto fs_setup() -> std::shared_ptr<mapp::core::services::service_locator> {
  auto svc_fs = std::make_shared<fs<fs<mapp::core::services::service>>>();
  auto svc_locator = std::make_shared<mapp::core::services::service_locator>(svc_fs);

  // Create the algorithm service filesystem
  auto algo_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("algo_svc", algo_fs);  // Put the algorithm filesystem in the filesystem of filesystems

  // Create the data service filesystem
  auto data_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("data_svc", data_fs);

  // Create the data metadata service filesystem
  auto meta_fs = std::make_shared<fs<mapp::core::services::service>>();
  svc_locator->_svc_fs->put("meta_svc", meta_fs);  // Add the service to the service filesystem
  return svc_locator;
}
}  // namespace mapp::core::filesystem
