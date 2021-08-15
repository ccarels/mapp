#!/usr/bin/env python3

##
# @package mapp-pipeline.py
#
import sys
sys.path.insert(1, '/absolute/path/to/mapp/core/build/') # Path to /absolute/path/to/mapp/core/build/
sys.path.insert(1, '/absolute/path/to/data_models/mymodule') # Path to /absolute/path/to/data_models/mymodule
sys.path.insert(1, '/absolute/path/to/data_models/pymodule_template') # Path to /absolute/path/to/data_models/pymodule_template
import py_mapp_core as mapp
import generated.py.pymodule_template_config_data_model_pb2 as pymodule_config
import generated.py.mymodule_config_data_model_pb2 as mymodule_config
import logging
import argparse

parser = argparse.ArgumentParser(
    description="A basic mapp pipeline.",
    epilog="See the README for more information.")
parser.add_argument('--param', type=int, default=42,
                    help='A demo parameter value')
args = parser.parse_args()

mapp.basic_info.print(__file__)
logging.debug("=== MAPP pipeline started")

# Create runtime data store services and a service locator
svc = mapp.service_locator()

# Locations of the modules
provide = mapp.provider("/absolute/path/to/mapp/core/build/config.txt") # /absolute/path/to/mapp/core/build/config.txt

# Use the provider to get a loader for mymodule instances
load = mapp.loader(provide.get("mymodule", svc))
obj = mapp.processor(load)

# Configure mymodule algorithm
config = mymodule_config.mymodule_config()
config.param = args.param
mymodule_cnf = "/mymodule/config"

# Store the settings in the data store
mapp.protobuf_processor_config(
    obj,
    svc,
    mymodule_cnf,
    config.SerializeToString())

# Initialize and execute the module
obj.init("/mymodule/config", svc)
obj.exec("", svc)

logging.debug("=== MAPP pipeline finished")
