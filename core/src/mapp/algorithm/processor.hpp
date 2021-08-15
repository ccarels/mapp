#ifndef processor_hpp
#define processor_hpp

#include <memory>
#include <string>
#include <vector>

#include "../filesystem/fs.hpp"
#include "../model/data_model.hpp"
#include "../services/service.hpp"
#include "../services/service_locator.hpp"
#include "../status_code/status_code.hpp"

/**
 * \def MAPP_EXPORT_MODULE
 * \brief A macro that modules use in order to provide the required dynamic shared object library interface to the \ref mapp::core::library::loader.
 * The names of the functions defined in this macro are required by the \ref mapp::core::library::loader.
 */

#if defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__) || defined(__MACH__)
#define MAPP_EXPORT_MODULE(NAME)                                                         \
  extern "C" auto construct()->mapp::core::algorithm::processor * { return new NAME(); } \
  extern "C" void destruct(mapp::core::algorithm::processor *p) { delete p; }
#elif defined(WIN32) || defined(_WIN32__) || defined(__WIN32__) || defined(_WIN64)
#define MAPP_EXPORT_MODULE(NAME)                                                                               \
  extern "C" __declspec(dllexport) auto construct()->mapp::core::algorithm::processor * { return new NAME(); } \
  extern "C" __declspec(dllexport) void destruct(mapp::core::algorithm::processor *p) { delete p; }
#endif

using STATUS = mapp::core::status;
#define STATUS_CODE(CODE) STATUS({std::vector<mapp::core::status_code>({CODE})})

namespace mapp::core::algorithm {
/**
 * \class processor
 * \brief A base class interface for algorithms.
 */
class processor : public mapp::core::services::service {
 public:
  processor() noexcept = default;
  ~processor() noexcept override = default;

  /**
   * \brief Initializes an algorithm, setting up any required (default) configuration and/or checking potential user-provided configuration objects.
   * Derived classes wishing to implement this type of configurability should override this method.
   * This method should ordinarily not be computationally demanding.
   * The first parameter is a std::string that is a human-readable reference to a location in the runtime file system to a location where the algorithm's configuration data should be stored or retrieved from.
   * The second parameter is a service locator to access the runtime file system.
   * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
   * \exception std::invalid_argument A std::invalid_argument may be raised if the implementation does not catch it.
   */
  virtual auto init(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) -> STATUS { return STATUS_CODE(mapp::core::status_code::success); };

  /**
   * \brief Executes an algorithm, for example performing any required computations, getting and setting data objects as needed.
   * Derived classes should expect the \ref exec method to be reentrant.
   * Derived classes should use the \ref mapp::core::services::service_locator that is provided in order to retrieve configuration data and to store resulting output data.
   * \return A \ref mapp::core::status object containing details about the outcome of calling this method.
   * \exception std::invalid_argument A std::invalid_argument may be raised if the implementation does not catch it.
   */
  virtual auto exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS { return STATUS_CODE(mapp::core::status_code::success); };
};
}  // namespace mapp::core::algorithm

#endif
