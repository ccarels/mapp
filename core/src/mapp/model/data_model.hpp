#ifndef data_model_hpp
#define data_model_hpp

#include "../services/service.hpp"

namespace mapp::core::model {
/**
 * \class data_model
 * \brief A base class interface for data models.
 * \brief A \ref data_model is a service, it can be stored in the \ref mapp::core::filesystem::fs.
 */
class data_model : public mapp::core::services::service {
 public:
  data_model() noexcept = default;
  ~data_model() noexcept override = default;
};
}  // namespace mapp::core::model

#endif
