#include "py_protobuf_config.hpp"

#include <boost/log/trivial.hpp>

#include "../algorithm/protobuf_config.hpp"
#include "../model/data_model_interface.hpp"
#include "../services/service.hpp"

namespace mapp::core::py {
extern "C" {
void py_set_protobuf_config(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc, char const *const path, char const *const protobuf_string) {
  auto configurable = mapp::core::model::data_model_interface<mapp::core::services::service, mapp::core::algorithm::protobuf_config>::get(obj->_p->algorithm());
  try {
    if (configurable == nullptr) { throw std::logic_error("Please check the module you provided supports protobuf_config"); }
    else { configurable->from_string(protobuf_string, path, loc->_p); }
  }
  catch (std::logic_error &i) { BOOST_LOG_TRIVIAL(error) << i.what() << " - " << obj->_p->algorithm()->name(); }
}

auto py_get_protobuf_config(mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc, char const *const path)
    -> py_shared_ptr<std::string> * {
  auto configurable = mapp::core::model::data_model_interface<mapp::core::services::service, mapp::core::algorithm::protobuf_config>::get(obj->_p->algorithm());
  std::string protobuf_string = "";
  try {
    if (configurable != nullptr) { configurable->to_string(protobuf_string, path, loc->_p); }
    else { throw std::logic_error("Please check the module you provided supports protobuf_config"); }
  }
  catch (std::logic_error &i) { BOOST_LOG_TRIVIAL(error) << i.what() << " - " << obj->_p->algorithm()->name(); }
  auto ptr = new py_shared_ptr<std::string>(std::make_shared<std::string>(protobuf_string));
  return ptr;
}

auto py_shared_ptr_c_str(py_shared_ptr<std::string> const *const obj) -> char const * { return obj->_p->c_str(); }
}
}  // namespace mapp::core::py
