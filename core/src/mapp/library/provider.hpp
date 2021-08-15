#ifndef provider_hpp
#define provider_hpp

#include <boost/log/trivial.hpp>

#include "loader.hpp"

namespace mapp::core::library {
/**
 * \class provider
 * \brief A class that uses a \ref library::locator to obtain a \ref library::loader class instance for a named module.
 */
template <class T, class U>
class provider final {
 public:
  /**
   * \brief Constructor that uses a \ref library::locator instances.
   * \param loc The \ref library::locator to use for searching for modules.
   */
  explicit provider(std::shared_ptr<library::locator> loc) noexcept : _loc(std::move(loc)) {}

  /**
   * \brief Search the \ref library::locator to find a module by name.
   * \param module The name of a module to search for as an all-lowercase std::string containing only UTF-8 characters.
   * \return A \ref library::loader object that can be used to load a library object of type T and, if T can be dynamically cast to type U, provide the object of type T as an object of type U.
   * \exception std::invalid_argument If no library can be opened, underlying exceptions raised by \ref mapp::core::library::loader must be caught by the caller of this method.
   */
  auto get(const std::string &module) const -> const std::shared_ptr<library::loader<T, U>> {
    auto l = _loc->name(module);
    if (l.path.empty()) {  // Fallback to a module that does nothing
      BOOST_LOG_TRIVIAL(info) << "=== Module not found: \"" << module << "\"";
      l = _loc->name("null_algorithm");
    }
    auto m = std::make_unique<library::loader<T, U>>(l);
    m->open();
    return m;
  }

 private:
  const std::shared_ptr<library::locator> _loc; /**< \brief The class instance internal storage for the \ref library::locator. */
};
}  // namespace mapp::core::library

#endif
