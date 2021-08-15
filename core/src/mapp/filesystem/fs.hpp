#ifndef fs_hpp
#define fs_hpp

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "../library/loader.hpp"
#include "../model/data_model_interface.hpp"
#include "../status_code/status_code.hpp"

/**
 * \brief A namespace for runtime file system interfaces.
 */
namespace mapp::core::filesystem {
/**
 * \class fs
 * \brief A file system that uses std::string to retrieve and add/update std::shared_ptr<T> to an object.
 */
template <class T>
class fs final {
 public:
  fs() noexcept = default;
  ~fs() noexcept = default;

  /**
   * \struct path
   * \brief A path in the file system and a std::shared_ptr<T> to the data it refers to.
   */
  struct path {
    const std::string _url;        /**< A human-readable location as a std::string. */
    const std::shared_ptr<T> _res; /**< A std::shared_ptr<T> to some data referred to by \ref _url. */
  };

  /**
   * \brief Retrieve a \ref path at the location given by a url.
   * \param url A string that refers to a human-readable location in the runtime file system.
   * \return On success: a \ref path object with the url and the pointer to the data on success. On failure: a \ref path object with an empty url and a nullptr is returned.
   * \exception std::invalid_argument A std::invalid_argument is raised if a resource at the specified url does not exist.
   */
  template <class U>
  auto get(const U &url) -> const path {
    std::shared_lock lock(_mutex);
    const auto it = _fs.find(url);
    if (it != _fs.end()) { return path({url, it->second}); }
    else { throw std::invalid_argument("Resource: \"" + std::string(url) + "\" does not exist."); }
  }

  /**
   * \brief Add or update the location given by \ref path::_url with the data pointed to by ptr.
   * \param url A string that refers to a human-readable location in the runtime file system.
   * \param ptr A std::shared_ptr<T> that is a pointer to an object that will be referred to by the runtime file system with the provided url.
   * \return On success: a \ref path object with the url and the pointer to the data on success is returned. On failure: a \ref path object with an empty url and a nullptr is returned.
   */
  template <class U>
  auto put(const U &url, std::shared_ptr<T> ptr) -> const path {
    std::unique_lock lock(_mutex);
    _fs[url] = ptr;
    return path{url, ptr};
  }

  /**
   * \brief Erase a \ref path at the location given by a url from the runtime file system.
   * \attention Erasing a path from the runtime file system does not automatically free the memory to which the underlying \ref path::_res pointer points -
   * this happens automatically when there are no std::shared_ptr instances pointing to a resource.
   * \param url A string that refers to a human-readable location in the runtime file system.
   * \return A \ref mapp::core::status_code indicating whether the operation:
   * succeeded (the resource specified by the url was found and erased from the runtime filesystem),
   * or failed (the resource specified by the url was not found).
   */
  template <class U>
  auto rm(const U &url) -> mapp::core::status_code {
    std::unique_lock lock(_mutex);
    auto it = _fs.find(url);
    if (it != _fs.end()) {
      _fs.erase(it);
      return mapp::core::status_code::success;
    }
    else { return mapp::core::status_code::failure; }
  }

  /**
   * \brief Add or update the location given by \ref path::_url with the data pointed to by the provided ptr parameter. If the provided type of ptr is of type U and it can be dynamically converted to a type T, this method performs that conversion
   * automatically. \param url A string that refers to a human-readable location in the runtime file system. \param ptr A std::shared_ptr<U> that is a pointer to an object that will be referred to by the runtime file system with the provided url
   * assuming it can be dynamically converted from type U to type T when this method is called. \return On success: a \ref path object with the url and the pointer to the data on success. On failure: a \ref path object with an empty url and a nullptr
   * is returned.
   */
  template <class U, class V>
  auto convert_put(const U &url, std::shared_ptr<V> ptr) -> const path {
    std::unique_lock lock(_mutex);
    _fs[url] = mapp::core::model::data_model_interface<V, T>::get(ptr);
    return path{url, ptr};
  }

  /**
   * \brief Couple the lifetime of a \ref mapp::core::library::loader instance
   * so that destructors of a dynamically loaded library remain available to objects in this store.
   * \param l A std::shared_ptr to a \ref mapp::core::library::loader instance.
   */
  void register_loader(const std::shared_ptr<void> &l) {
    std::unique_lock lock(_mutex);
    _loaders.emplace_back(l);
  }

 private:
  std::vector<std::shared_ptr<void>> _loaders;
  std::unordered_map<std::string, std::shared_ptr<T>> _fs;
  std::shared_mutex _mutex;
};
}  // namespace mapp::core::filesystem

#endif
