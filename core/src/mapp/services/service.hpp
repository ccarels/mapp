#ifndef service_hpp
#define service_hpp

#include <string>

/**
 * \brief A namespace for services.
 */
namespace mapp::core::services {
/**
 * \class service
 * \brief A base class so that derived classes can be located using the \ref service_locator.
 */
class service {
 public:
  service() = default;
  virtual ~service() = default;

  /**
   * \brief The name of the service.
   * \return The name of the service as a std::string.
   */
  [[nodiscard]] virtual auto name() const noexcept -> const std::string { return "unnamed service"; }
};
}  // namespace mapp::core::services

#endif
