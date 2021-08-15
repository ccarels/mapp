#include "../python/py_pipeline_sequence.hpp"

namespace mapp::core::py {
extern "C" {
auto py_pipeline_sequence() -> py_shared_ptr<mapp::core::pipeline::sequence> * {
  auto p = std::make_shared<mapp::core::pipeline::sequence>();
  return new py_shared_ptr<mapp::core::pipeline::sequence>(p);
}

void py_pipeline_sequence_dtr(py_shared_ptr<mapp::core::pipeline::sequence> *sequence) { delete sequence; }
void py_pipeline_sequence_put_module_init(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence, mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, char const *const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc) { sequence->_p->put_module_init(obj->_p, path, loc->_p); }
void py_pipeline_sequence_put_module_exec(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence, mapp::core::py::py_shared_ptr<mapp::core::algorithm::managed<mapp::core::algorithm::processor>> *const obj, char const *const path, mapp::core::py::py_shared_ptr<mapp::core::services::service_locator> *const loc) { sequence->_p->put_module_exec(obj->_p, path, loc->_p); }
void py_pipeline_sequence_execute(py_shared_ptr<mapp::core::pipeline::sequence> *const sequence) { sequence->_p->execute(); }
}
}  // namespace mapp::core::py
