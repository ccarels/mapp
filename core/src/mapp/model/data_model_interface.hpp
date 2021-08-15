#ifndef data_model_interface_hpp
#define data_model_interface_hpp

#include <iostream>
#include <memory>
#include <vector>

/**
 * \brief A namespace for data model interfaces.
 */
namespace mapp::core::model {
/**
 * \class data_model_interface
 * \brief Provides an interface to dynamically cast objects from a type T to a type U (e.g. a base class pointer to a derived class pointer).
 */
template <class T, class U>
class data_model_interface {
 public:
  data_model_interface() = delete;

  /**
   * \brief Perform a std::dynamic_pointer_cast on a std::shared_ptr<T> to a std::shared_ptr<U>.
   * \param data A std::shared_ptr<T> to the data to be dynamically converted to a std::shared_ptr<U>.
   * \return On success, a std::shared_ptr<U> for the provided std::shared_ptr<T>.
   */
  inline static auto get(const std::shared_ptr<T> data) noexcept -> std::shared_ptr<U> { return std::dynamic_pointer_cast<U>(data); }
};
}  // namespace mapp::core::model

#endif
