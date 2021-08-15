#ifndef managed_hpp
#define managed_hpp

#include <boost/log/trivial.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../filesystem/fs.hpp"
#include "../services/service_locator.hpp"
#include "../status_code/status_code.hpp"

/**
 * \brief A namespace for algorithm interfaces.
 */
namespace mapp::core::algorithm {
/**
 * \class managed
 * \brief A wrapper class for any class T that implements the interface of this class.
 * This wrapper class forwards calls to the interface to instances of the class it wraps.
 * In practice, this wrapper class is used to wrap \ref mapp::core::algorithm::processor derived class instances.
 */
template <class T>
class managed final {
 public:
  /**
   * \brief Constructor for a \ref managed instance of a class T.
   * \param p The class of type T to be managed by this class.
   */
  explicit managed(const std::shared_ptr<T> &p) noexcept : _p(p) {}

  /**
   * \brief Calls the init method of the managed class.
   * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
   * \param svc A service locator that is used to access the runtime file system.
   * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
   * \exception std::logic_error A std::logic_error exception is raised if the managed module raises an uncaught std::invalid_argument exception.
   */
  auto init(const std::string &path, std::shared_ptr<mapp::core::services::service_locator> svc) -> mapp::core::status {
    BOOST_LOG_TRIVIAL(info) << "=== init() within managed context - " << _p->name();
    try { return _p->init(path, svc); }
    catch (std::invalid_argument &i) { throw std::logic_error("Uncaught invalid_argument exception in module \"" + _p->name() + "\". Perhaps a resource referred to in this module was not available? The exception raised was: " + i.what() + "\""); }
  }

  /**
   * \brief Calls the exec method of the managed class.
   * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
   * \param svc A service locator that is used to access the runtime file system.
   * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
   * \exception std::logic_error A std::logic_error exception is raised if the managed module raises an uncaught std::invalid_argument exception.
   */
  auto exec(const std::string &path, std::shared_ptr<mapp::core::services::service_locator> svc) -> mapp::core::status {
    BOOST_LOG_TRIVIAL(info) << "=== exec() within managed context - " << _p->name();
    try { return _p->exec(path, svc); }
    catch (std::invalid_argument &i) { throw std::logic_error("Uncaught invalid_argument exception in module \"" + _p->name() + "\". Perhaps a resource referred to in this module was not available? The exception raised was: \"" + i.what() + "\""); }
  }

  /**
   * \brief Obtain access to the object that this class manages.
   * \return A std::shared_ptr to the object that this class manages.
   */
  auto algorithm() noexcept -> std::shared_ptr<T> { return _p; }

 private:
  std::shared_ptr<T> _p; /**< A std::shared_ptr to the object that this class manages. */
};
}  // namespace mapp::core::algorithm

#endif
