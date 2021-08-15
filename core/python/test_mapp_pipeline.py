##
# @package test_mapp_pipeline.py
# \brief Coverage tests for \ref py_mapp_core.
#
import sys
sys.path.insert(1, '@CMAKE_BINARY_DIR@')
sys.path.insert(1, '@DATA_MODELS_DIR@/mymodule/')
import py_mapp_core as mapp
import generated.py.mymodule_config_data_model_pb2 as mymodule_config

##
# \brief Test the functions of \ref py_mapp_core.
#
def test_mapp_pipeline():
    # Create a runtime data store service locator
    mapp.basic_info.print()
    
    svc = mapp.service_locator()

    # Locations of the modules
    provide = mapp.provider("@CMAKE_BINARY_DIR@/config.txt")
    load = mapp.loader(provide.get("mymodule", svc))
    obj = mapp.processor(load)

    # Configure \ref processor
    config = mymodule_config.mymodule_config()
    config.param = 1
    mymodule_cnf = "/mymodule/config"

    mapp.protobuf_processor_config(
        obj,
        svc,
        mymodule_cnf,
        config.SerializeToString())

    obj.init(mymodule_cnf, svc)
    obj.exec(mymodule_cnf, svc)

    # Test the \ref pipeline_sequence class
    pipeline = mapp.pipeline_sequence()
    pipeline.put_module_init(obj, mymodule_cnf, svc)
    pipeline.put_module_exec(obj, mymodule_cnf, svc)
    pipeline.execute()

    mymodule_config_str = mapp.protobuf_processor_config.get(
        obj, svc, mymodule_cnf)
    rconfig = config.FromString(mymodule_config_str)
