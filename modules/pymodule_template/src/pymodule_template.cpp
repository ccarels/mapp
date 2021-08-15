#include <iostream>

#include <Python.h>

#include "pymodule_template.hpp"

using namespace mapp::core;
using namespace mapp::algorithm;
using namespace mapp::core::model;
MAPP_EXPORT_MODULE(MODULE)

auto MODULE::init(const std::string &path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> STATUS {
    try {
        auto algo_svc_path = svc->_svc_fs->get("algo_svc");
        auto from_algo_svc = algo_svc_path._res->get(path);
        const auto _m = data_model_interface<mapp::core::services::service, MODULE>::get(from_algo_svc._res);
        this->_config = _m->_config;
    }
    catch(std::invalid_argument &) {
        auto _m = std::make_shared<MODULE>();
        _m->_config = std::make_shared<mapp::pymodule_template_config>();
        _m->_config->set_script_path("../../../python/pymodule_template.py"); /// Enter a default script path.
        auto algo_obj = data_model_interface<MODULE, mapp::core::services::service>::get(_m);
        auto algo_svc_path = svc->_svc_fs->get("algo_svc");
        if(algo_svc_path._res) {
            algo_svc_path._res->put(path, algo_obj);
            this->_config = _m->_config;
        }
    }
    return STATUS_CODE(status_code::success);
}

auto MODULE::exec(const std::string &, std::shared_ptr<mapp::core::services::service_locator> &) const -> STATUS {
    const std::string py_path = _config->script_path();
    FILE *fd = fopen(py_path.c_str(), "r+");
    if(fd != NULL) {
      auto gstate = PyGILState_Ensure();
      PyRun_SimpleFile(fd, py_path.c_str());
      PyGILState_Release(gstate);
      fclose(fd);
    }
    return STATUS_CODE(status_code::success);
}

auto MODULE::from_string(const std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code {
    auto _m = std::make_shared<MODULE>();
    mapp::pymodule_template_config c;
    if(c.ParseFromString(config_string)) {_m->_config = std::make_shared<mapp::pymodule_template_config>(c);}
    auto algo_obj = mapp::core::model::data_model_interface<MODULE, mapp::core::services::service>::get(_m);
    auto algo_svc_path = svc->_svc_fs->get("algo_svc");
    if(algo_svc_path._res && !svc_path.empty()) {
        algo_svc_path._res->put(svc_path, algo_obj);
        return mapp::core::status_code::success;
    }
    return mapp::core::status_code::failure; 
}

auto MODULE::to_string(std::string &config_string, const std::string &svc_path, std::shared_ptr<mapp::core::services::service_locator> &svc) -> mapp::core::status_code {
    mapp::pymodule_template_config c;
    auto algo_svc_path = svc->_svc_fs->get("algo_svc");
    auto from_algo_svc = algo_svc_path._res->get(svc_path);
    const auto _m = mapp::core::model::data_model_interface<mapp::core::services::service, MODULE>::get(from_algo_svc._res);
    if(_m && _m->_config->SerializeToString(&config_string)) {return mapp::core::status_code::success;}
    else { return mapp::core::status_code::failure; }
}
