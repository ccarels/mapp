#ifndef py_shared_ptr_hpp
#define py_shared_ptr_hpp

#include <memory>

/**
 * \brief A namespace for Python wrapper functions.
 */
namespace mapp::core::py {
/**
 * \class py_shared_ptr
 * \brief A wrapper class for a C++ std::shared_ptr instance so that std::shared_ptr objects can be passed to and from Python.
 */
template <class T>
class py_shared_ptr final {
 public:
  /**
   * \brief Constructor for \ref py_shared_ptr.
   * \param p A std::shared_ptr<T> that will be wrapped by this class.
   */
  explicit py_shared_ptr(const std::shared_ptr<T> &p) : _p(p) {}
  std::shared_ptr<T> _p; /**< The underlying std::shared_ptr<T> that is wrapped by this class. */
};
}  // namespace mapp::core::py

#endif
