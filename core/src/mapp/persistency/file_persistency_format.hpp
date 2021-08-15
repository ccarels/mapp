#ifndef file_persistency_format_hpp
#define file_persistency_format_hpp

#include <memory>
#include <string>
#include <vector>

#include "../model/data_model.hpp"
#include "../status_code/status_code.hpp"

/**
 * \brief A namespace for persistent data interfaces.
 */
namespace mapp::core::persistency {
/**
 * \class file_persistency_format
 * \brief An interface for reading/writing persistency data.
 */
class file_persistency_format {
 public:
  file_persistency_format() noexcept = default;
  virtual ~file_persistency_format() noexcept = default;
  /**
   * \brief Read data from disk. Derived classes must implement the conversion from the persistency data to the runtime data format.
   * \param path The path on disk to write the data to.
   * \return A \ref mapp::core::status_code indicating the outcome of calling this method.
   */
  [[nodiscard]] virtual auto wr(const std::string &path) const -> mapp::core::status_code = 0;

  /**
   * \brief Read data from disk. Derived classes must implement the conversion from the persistency data to the runtime data format.
   * \param path The path on disk to read the data from.
   * \param ptr A std::shared_ptr that will point to the data that will be read by this method.
   * \return A \ref mapp::core::status_code indicating the outcome of calling this method.
   */
  virtual auto rd(const std::string &path, std::shared_ptr<mapp::core::model::data_model> &ptr) const -> mapp::core::status_code = 0;
};
}  // namespace mapp::core::persistency

#endif
