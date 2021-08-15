#ifndef null_algorithm_hpp
#define null_algorithm_hpp

#include "../../algorithm/protobuf_config.hpp"
#include "../../tests/mockable.hpp"
#include "../processor.hpp"

namespace mapp::core::algorithm {
/**
 * \class null_algorithm
 * \brief An algorithm implementation that functions like a dry-run and does nothing useful.
 */
class null_algorithm final : public mapp::core::algorithm::processor {
 public:
  null_algorithm() = default;
  ~null_algorithm() override = default;

  /**
   * \brief The name of the module.
   * \return The name of the module as a std::string.
   */
  [[nodiscard]] auto name() const noexcept -> const std::string override { return "null_algorithm"; }

  /**
   * \brief Execute the module.
   * \return A \ref mapp::core::status indicating the result of this operation.
   */
  auto exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS override;
};
}  // namespace mapp::core::algorithm

#endif
