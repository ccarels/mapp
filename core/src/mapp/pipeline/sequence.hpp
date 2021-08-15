#ifndef sequence_hpp
#define sequence_hpp

#include <boost/log/trivial.hpp>
#include <thread>
#include <vector>

#include "../algorithm/managed.hpp"
#include "../status_code/status_code.hpp"

/**
 * \brief A namespace for pipelines.
 */
namespace mapp::core::pipeline {
/**
 * \class sequence
 * \brief A pipeline sequence of \ref mapp::core::algorithm::managed class specialization instances.
 * Pipeline sequences are configured in advance, offering deferred initialization and deferred execution.
 */
class sequence final {
 public:
  sequence() noexcept = default;
  ~sequence() noexcept = default;

  /**
   * \enum module_mode
   * \brief Specify in what way a module should be added to the sequence.
   */
  enum class module_mode : int {
    next = 0,  //!< Insert the instance at the current end of the sequence (the current end may change if further modules are added).
  };

  /**
   * \brief Put a module in the pipeline sequence for eventual initialization.
   * This method does not call any methods belonging to any parameters given to it.
   * \param i A pointer to a \ref mapp::core::algorithm::managed instance.
   * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
   * \param svc A service locator that is used to access the runtime file system.
   * \param mode The \ref module_mode by which the module will be added to the pipeline.
   * \exception std::invalid_argument A std::invalid_argument exception is raised if the module mode is invalid.
   * \warning The caller is responsible for the continued availability of the objects passed as parameters to this method.
   */
  template <class T>
  void put_module_init(std::shared_ptr<mapp::core::algorithm::managed<T>> i, std::string path, std::shared_ptr<mapp::core::services::service_locator> svc, const module_mode mode = module_mode::next) {
    BOOST_LOG_TRIVIAL(info) << "=== Added init() within a managed context to a pipeline sequence - " << i->algorithm()->name();
    switch (mode) {
      case module_mode::next:
        _pipeline.emplace_back(deferred_init(i, path, svc));
        break;
    }
  }

  /**
   * \brief Put a module in the pipeline sequence for eventual execution.
   * This method does not call any methods belonging to any parameters given to it.
   * \param i A pointer to a \ref mapp::core::algorithm::managed instance.
   * \param path A human-readable reference to a location in the runtime file system where the configuration data for this managed class should be stored/retrieved.
   * \param svc A service locator that is used to access the runtime file system.
   * \param mode The \ref module_mode by which the module will be added to the pipeline.
   * \warning The caller is responsible for the continued availability of the objects passed as parameters to this method.
   */
  template <class T>
  void put_module_exec(std::shared_ptr<mapp::core::algorithm::managed<T>> i, std::string path, std::shared_ptr<mapp::core::services::service_locator> svc, const module_mode mode = module_mode::next) {
    BOOST_LOG_TRIVIAL(info) << "=== Added exec() within a managed context to a pipeline sequence - " << i->algorithm()->name();
    switch (mode) {
      case module_mode::next:
        _pipeline.emplace_back(deferred_exec(i, path, svc));
        break;
    }
  }

  /**
   * \brief Execute all modules in the pipeline in the sequence that was configured.
   * \exception std::logic_error A std::logic_error may be thrown if a module throws an uncaught error.
   * \warning The caller is responsible for the continued availability of the objects in the pipeline.
   */
  void execute() {
    std::thread::id this_id = std::this_thread::get_id();
    BOOST_LOG_TRIVIAL(info) << "=== Running a pipeline sequence on thread " << this_id;
    std::for_each(_pipeline.begin(), _pipeline.end(), [&](std::function<void(void)> &f) { f(); });
    BOOST_LOG_TRIVIAL(info) << "=== Finished a pipeline sequence";
  }

 private:
  std::vector<std::function<void(void)>> _pipeline;

  /**
   * \brief Configure the initialization step through a copy captured lambda.
   * \param obj The object whose init method will be called.
   * \param path The first parameter passed to the init method.
   * \param svc The second parameter passed to the init method.
   * \return A std::function instance representing the configured call.
   */
  template <typename T, typename U, typename V>
  inline auto deferred_init(T obj, U path, V svc) noexcept -> std::function<void(void)> { return [=]() { if (obj) { obj->init(path, svc); } }; }

  /**
   * \brief Configure the execution step through a copy captured lambda.
   * \param obj The object whose exec method will be called.
   * \param path The first parameter passed to the exec method.
   * \param svc The second parameter passed to the exec method.
   * \return A std::function instance representing the configured call.
   */
  template <typename T, typename U, typename V>
  inline auto deferred_exec(T obj, U path, V svc) noexcept -> std::function<void(void)> { return [=]() { if (obj) { obj->exec(path, svc); } }; }
};
}  // namespace mapp::core::pipeline

#endif
