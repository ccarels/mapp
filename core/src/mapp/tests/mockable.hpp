#ifndef mockable_hpp
#define mockable_hpp

#include <memory>

#include "../services/service_locator.hpp"

/**
 * \brief A namespace for test interfaces.
 */
namespace mapp::core::tests {
/**
 * \class mockable
 * \brief A base class that imposes the requirement on derived classes to be able to generate mock data.
 */
class mockable {
 public:
  mockable() noexcept = default;
  virtual ~mockable() noexcept = default;

  /**
   * \brief Generate and set mock data in the runtime file system.
   */
  virtual void set_mock_data(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const = 0;
};
}  // namespace mapp::core::tests

#endif
