#ifndef fs_setup_hpp
#define fs_setup_hpp

#include "../filesystem/fs.hpp"
#include "../services/service_locator.hpp"

namespace mapp::core::filesystem {
/**
 * \brief Setup a file system of file systems and add various services such as an `algo_svc`, `meta_svc`, and a `data_svc`.
 * \return A std::shared_ptr to a \ref mapp::core::services::service_locator that contains various services.
 */
auto fs_setup() -> std::shared_ptr<mapp::core::services::service_locator>;
}  // namespace mapp::core::filesystem

#endif
