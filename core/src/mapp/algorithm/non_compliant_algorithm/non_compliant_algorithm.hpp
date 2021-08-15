#ifndef non_compliant_algorithm_hpp
#define non_compliant_algorithm_hpp

#include "../processor.hpp"

namespace mapp::core::algorithm {
/**
 * \class non_compliant_algorithm
 * \brief An algorithm implementation that is non-compliant with the dynamic loading interface of \ref mapp::core::library::loader.
 * This class is used for coverage tests and debugging purposes.
 */
class non_compliant_algorithm final : public mapp::core::algorithm::processor {
 public:
  non_compliant_algorithm() = default;
  ~non_compliant_algorithm() override = default;

  /**
   * \brief The name of the module.
   * \return The name of the module as a std::string.
   */
  [[nodiscard]] auto name() const noexcept -> const std::string override { return "non_compliant_algorithm"; }

  /**
   * \brief Execute the module.
   * \return A \ref mapp::core::status indicating the result of this operation.
   */
  auto exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS override;
};
}  // namespace mapp::core::algorithm

#endif
