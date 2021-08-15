#ifndef throwing_algorithm_hpp
#define throwing_algorithm_hpp

#include "../../algorithm/protobuf_config.hpp"
#include "../../tests/mockable.hpp"
#include "../processor.hpp"

namespace mapp::core::algorithm {
/**
 * \class throwing_algorithm
 * \brief An algorithm implementation that functions like a dry-run and does nothing useful except throw an exception.
 */
class throwing_algorithm final : public mapp::core::algorithm::processor {
 public:
  throwing_algorithm() = default;
  ~throwing_algorithm() override = default;

  /**
   * \brief The name of the module.
   * \return The name of the module as a std::string.
   */
  [[nodiscard]] auto name() const noexcept -> const std::string override { return "throwing_algorithm"; }

  /**
   * \brief Initialize the module.
   * \return A \ref mapp::core::status indicating the result of this operation.
   */
  auto init(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) -> STATUS override;

  /**
   * \brief Execute the module.
   * \return A \ref mapp::core::status indicating the result of this operation.
   */
  auto exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS override;
};
}  // namespace mapp::core::algorithm

#endif
