#ifndef loader_hpp
#define loader_hpp

#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
#include <dlfcn.h>
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
#include <windows.h>
#endif

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "locator.hpp"

/**
 * \brief A namespace for dynamic library loading of modules.
 */
namespace mapp::core::library {
/**
 * \class loader
 * \brief Dynamically load a dynamic shared object library (.so) file to obtain instances of classes that derive from class T.
 */
template <class T, class U>
class loader final {
 public:
  /**
   * \brief Constructor for \ref loader, sets the location of the dynamic shared object library (.so) file.
   * \param lib The \ref locator::lib containg the name and path to the dynamic shared object library (.so) file.
   */
  explicit loader(locator::lib lib) : _p(nullptr), _lib(std::move(lib)) {}
  loader(const loader &) = delete;
  auto operator=(const loader &) -> loader & = delete;

  /**
   * \brief Destructor for \ref loader.
   */
  ~loader() { close(); }

  /**
   * \brief Calls dlopen to load the library from the physical file system with the \ref locator::lib path provided in the constructor of this class.
   * \exception std::invalid_argument A std::invalid_argument exception is raised if the module does not conform to the required interface.
   */
  void open() {
#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
    _p = std::make_shared<void *>(dlopen(_lib.path.c_str(), RTLD_NOW | RTLD_LAZY));
    ctr_ = reinterpret_cast<T *(*)()>(dlsym(*_p, _ctr.c_str()));
    dtr_ = reinterpret_cast<void (*)(T *)>(dlsym(*_p, _dtr.c_str()));
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
    _p = std::make_shared<HINSTANCE>(LoadLibraryA(_lib.path.c_str()));
    ctr_ = reinterpret_cast<T *(*)()>(GetProcAddress(*_p, _ctr));
    dtr_ = reinterpret_cast<void (*)(T *)>(GetProcAddress(*_p, _dtr));
#endif

    if (_p == nullptr || ctr_ == nullptr || dtr_ == nullptr) {
#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
      std::cerr << dlerror() << std::endl;
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
      std::cerr << GetLastError() << std::endl;
#endif
      close();
      throw std::invalid_argument("Library \"" + _lib.path + "\" cannot be opened. You probably did not specify a path to a suitable library.");
    }
  }

  /**
   * \brief Calls dlclose on the dynamic shared object library (.so) file if possible.
   */
  void close() noexcept {
#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
    if (_p && *_p) dlclose(*_p);
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
    if (_p && *_p) FreeLibrary(*_p);
#endif
  }

  /**
   * \brief From the opened dynamic shared object library, construct a std::shared_ptr<T>.
   * \return A std::shared_ptr<U> from an object of type std::shared_ptr<T>.
   * \warning For performance reasons, this method does not check whether the class instance can indeed be allocated.
   * For this reason, callers of this class should first check that the call to \ref mapp::core::library::loader::open succeeded.
   * In the event of an exception, execution will terminate.
   */
  auto instance() noexcept -> const std::shared_ptr<U> {
    const auto T_ptr = std::shared_ptr<T>(ctr_(), [this](T *p) { dtr_(p); });
    return std::make_shared<U>(std::move(T_ptr));
  }

 private:
#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
  std::shared_ptr<void *> _p;  ///< A handle to the dymamically loaded shared object library (.so) file.
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
  std::shared_ptr<HINSTANCE> _p;    ///< A handle to the dymamically loaded shared object library (.so) file.
#endif
  locator::lib _lib;  ///< The name and path on the physical file system of a dynamic shared object library (.so) file.

#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
  const std::string _ctr = "construct";  ///< \brief Required exposed function name for the constructor for the dynamically loaded class.
  const std::string _dtr = "destruct";   ///< \brief Required exposed function name for the destructor for the dynamically loaded class.
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
  const LPCSTR _ctr = "construct";  ///< \brief Required exposed function name for the constructor for the dynamically loaded class.
  const LPCSTR _dtr = "destruct";   ///< \brief Required exposed function name for the destructor for the dynamically loaded class.
#endif

  std::function<T *()> ctr_;
  std::function<void(T *)> dtr_;
};
}  // namespace mapp::core::library

#endif
