##
# @package py_mapp_core.py
# \brief Python wrapper classes for mapp functionality.
#
import ctypes
from datetime import datetime
import getpass
import socket
import os
from tabulate import tabulate
import GPUtil

if os.name == 'nt':
    lib = ctypes.CDLL('@CMAKE_BINARY_DIR@/libmapp-core.dll')
else:
    lib = ctypes.CDLL('@CMAKE_BINARY_DIR@/libmapp-core.so')

##
# \class basic_info
# \brief A class to print basic information about the running script


class basic_info:
    ##
    # \brief Print basic information
    @staticmethod
    def print(script_name="script_name"):
        i = [
            [1, "Datetime [UTC]", datetime.utcnow()],
            [2, "Local time", datetime.now()],
            [3, "User", getpass.getuser()],
            [4, "Host", socket.gethostname()],
            [5, "OS type", os.name],
            [6, "Workdir", os.getcwd()],
            [7, "Script", script_name],
            ]
        print("=============== ====================== ===============")
        print("=============== STARTING MAPP PIPELINE ===============")
        print("=============== ====================== ===============")
        print(tabulate(i, headers=["#", "Description", "Value"]))
        print("")
        print("GPU information")
        gpu_info = []
        gpus = GPUtil.getGPUs()
        for g in gpus:
            gg = [g.id, g.name, g.driver, g.memoryTotal, 100.0*g.memoryUtil, 100.0*g.load]
            gpu_info.append(gg)
        print("")
        print(tabulate(gpu_info, headers=["ID", "Name", "Driver", "Total memory [MB]", "Memory utilized (%)", "Load [%]"]))
        print("=============== ====================== ===============")

##
# \class service_locator
# \brief A Python wrapper for a \ref mapp::core::services::service_locator.


class service_locator:
    ##
    # \brief Constructor for \ref service_locator.
    def __init__(self):
        lib.py_service_locator.argtypes = []
        lib.py_service_locator.restype = ctypes.c_void_p
        self._locator = lib.py_service_locator()
    ##
    # \brief Destructor for \ref service_locator.
    def __del__(self):
        lib.py_service_locator_dtr.argtypes = [ctypes.c_void_p]
        lib.py_service_locator_dtr(self._locator)

##
# \class provider
# \brief A Python wrapper for a \ref mapp::core::library::provider.


class provider:
    ##
    # \brief Constructor for \ref provider.
    # \param path a str to the location of a configuration text file
    # that the mapp::core::library::provider will parse
    # in order to find the names and locations on the file system
    # of shared library object files for modules that can be
    # dynamically loaded and which comply with the
    # \ref mapp::core::algorithm::processor interface.
    def __init__(self, path: str):
        lib.py_library_provider.argtypes = [ctypes.c_char_p]
        lib.py_library_provider.restype = ctypes.c_void_p
        c_string = ctypes.c_char_p(path.encode('utf-8'))
        # Gets a library::provider for the module
        self._provider = lib.py_library_provider(c_string)
    ##
    # \brief Destructor for \ref provider.
    def __del__(self):
        lib.py_library_provider_dtr.argtypes = [ctypes.c_void_p]
        lib.py_library_provider_dtr(self._provider)
    ##
    # \brief Look for a module by name and
    # return a \ref mapp::core::library::loader for that module.
    # \param module_name The name of the module for which to retrieve
    # a \ref mapp::core::library::loader.
    # \param svc A service locator that is used to access the
    # runtime file system.
    # \return Get a pointer to a \ref mapp::core::library::loader for a module.

    def get(self, module_name: str, svc: service_locator):
        lib.py_library_provider_get.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        lib.py_library_provider_get.restype = ctypes.c_void_p
        c_string = ctypes.c_char_p(module_name.encode('utf-8'))
        # Uses the library::provider to get a library::loader for the module
        return lib.py_library_provider_get(self._provider, c_string, svc._locator)
##
# \class loader
# \brief A Python wrapper for a \ref mapp::core::library::loader.


class loader:
    ##
    # \brief Constructor for \ref loader.
    # \param ptr A pointer to the underlying \ref mapp::core::library::loader.
    def __init__(self, ptr: ctypes.c_void_p):
        self._loader = ptr
    ##
    # \brief Destructor for \ref loader.
    def __del__(self):
        lib.py_library_loader_dtr.argtypes = [ctypes.c_void_p]
        lib.py_library_loader_dtr(self._loader)
##
# \class processor
# \brief A Python wrapper for a
# \ref mapp::core::algorithm::managed<\ref mapp::core::algorithm::processor >.


class processor:
    ##
    # \brief Constructor for \ref processor.
    # \param proc The \ref loader that is used to obtain
    # instances of managed \ref processor classes.
    def __init__(self, proc: loader):
        lib.py_managed_processor_instance.argtypes = [ctypes.c_void_p]
        lib.py_managed_processor_instance.restype = ctypes.c_void_p
        # Uses the loader to provide an instance of a managed algorithm class
        self._processor = lib.py_managed_processor_instance(proc._loader)
    ##
    # \brief Destructor for \ref processor.
    def __del__(self):
        lib.py_managed_processor_dtr.argtypes = [ctypes.c_void_p]
        lib.py_managed_processor_dtr(self._processor)
    ##
    # \brief Calls the \ref mapp::core::algorithm::managed::init
    # method on the current class instance.
    # \param path A human-readable reference to a location in the
    # runtime file system where the configuration data for this
    # managed class should be stored/retrieved.
    # \param svc A service locator that is used to access the
    # runtime file system.
    def init(self, path: str, svc: service_locator):
        lib.py_managed_processor_init.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        lib.py_managed_processor_init.restype = ctypes.c_void_p
        c_string = ctypes.c_char_p(path.encode('utf-8'))
        # Runs the init function of the managed class instance
        lib.py_managed_processor_init(self._processor, c_string, svc._locator)
    ##
    # \brief Calls
    # \ref mapp::core::algorithm::managed::exec
    # on the current class instance.
    # \param path A human-readable reference to a location in the
    # runtime file system where the configuration data for this
    # managed class should be stored/retrieved.
    # \param svc A service locator that is used to
    # access the runtime file system.

    def exec(self, path: str, svc: service_locator):
        lib.py_managed_processor_exec.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        lib.py_managed_processor_exec.restype = ctypes.c_void_p
        c_string = ctypes.c_char_p(path.encode('utf-8'))
        # Runs the exec function of the managed class instance
        lib.py_managed_processor_exec(self._processor, c_string, svc._locator)

##
# \class protobuf_processor_config
# \brief A Python wrapper for setting configuration data
# using the \ref mapp::core::algorithm::protobuf_config interface.


class protobuf_processor_config:
    ##
    # \brief Serialize a Protobuf object to a str and then
    # store it in the runtime file system.
    # \param proc The \ref processor that will be used to
    # deserialize the Protobuf string into the correct Protobuf object.
    # \param locator A service locator that is used to
    # access the runtime file system.
    # \param path A human-readable reference to a location in the
    # runtime file system where the Protobuf data should be stored.
    # \param protobuf_data A str containing the serialized Protobuf object.
    def __init__(
            self,
            proc: processor,
            locator: service_locator,
            path: str,
            protobuf_data: str):
        lib.py_set_protobuf_config.argtypes = [
            ctypes.c_void_p, ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        lib.py_set_protobuf_config.restype = ctypes.c_void_p
        path_c_string = ctypes.c_char_p(path.encode('utf-8'))
        lib.py_set_protobuf_config(
            proc._processor,
            locator._locator,
            path_c_string,
            protobuf_data)  # Sets processor config data into a store at a path
    ##
    # \brief Retrieve a serialized str for a Protobuf object
    # that is currently stored in the runtime file system.
    # \param proc The \ref processor that should be used to serialize
    # the Protobuf object from the runtime file system as a string.
    # \param locator A service locator that is used to
    # access the runtime file system.
    # \param path A human-readable reference to a location in the
    # runtime file system where the Protobuf data are stored.
    # \return A string representation of the Protobuf configuration
    # data object recovered from the runtime file system.

    @staticmethod
    def get(proc: processor, locator: service_locator, path: str):
        lib.py_get_protobuf_config.argtypes = [
            ctypes.c_void_p, ctypes.c_void_p, ctypes.c_char_p]
        lib.py_get_protobuf_config.restype = ctypes.c_void_p
        path_c_string = ctypes.c_char_p(path.encode('utf-8'))
        py_shared_ptr_obj = lib.py_get_protobuf_config(proc._processor, locator._locator, path_c_string)  # Get processor config data from a store
        lib.py_shared_ptr_c_str.argtypes = [ctypes.c_void_p]
        lib.py_shared_ptr_c_str.restype = ctypes.c_char_p
        return lib.py_shared_ptr_c_str(py_shared_ptr_obj) # Get str from py_shared_ptr_obj

##
# \class pipeline_sequence
# \brief A Python wrapper for a \ref mapp::core::pipeline::sequence
# which will be initialized and executed in a deferred manner.


class pipeline_sequence:
    ##
    # \brief Constructor for \ref pipeline_sequence.
    def __init__(self):
        lib.py_pipeline_sequence.argtypes = []
        lib.py_pipeline_sequence.restype = ctypes.c_void_p
        self._pipeline = lib.py_pipeline_sequence()
    ##
    # \brief Destructor for \ref pipeline_sequence.
    def __del__(self):
        lib.py_pipeline_sequence_dtr.argtypes = [ctypes.c_void_p]
        lib.py_pipeline_sequence_dtr(self._pipeline)
    ##
    # \brief Add a \ref processor (a \ref mapp::core::algorithm::managed instance) to
    # the \ref pipeline_sequence to eventually call its
    # \ref mapp::core::algorithm::managed::init method.
    # \param module The \ref processor to be added to the pipeline_sequence.
    # \param path A human-readable reference to a location in the
    # runtime file system where the Protobuf data are stored.
    # \param svc A service locator that is used to
    # access the runtime file system.
    def put_module_init(self, module: processor, path: str, svc: service_locator):
        lib.py_pipeline_sequence_put_module_init.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        path_c_string = ctypes.c_char_p(path.encode('utf-8'))
        lib.py_pipeline_sequence_put_module_init(self._pipeline, module._processor, path_c_string, svc._locator)
    ##
    # \brief Add a \ref processor (a \ref mapp::core::algorithm::managed instance) to
    # the \ref pipeline_sequence to eventually call its
    # \ref mapp::core::algorithm::managed::exec method.
    # \param module The \ref processor to be added to the pipeline_sequence.
    # \param path A human-readable reference to a location in the
    # runtime file system where the Protobuf data are stored.
    # \param svc A service locator that is used to
    # access the runtime file system.
    def put_module_exec(self, module: processor, path: str, svc: service_locator):
        lib.py_pipeline_sequence_put_module_exec.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_char_p, ctypes.c_void_p]
        path_c_string = ctypes.c_char_p(path.encode('utf-8'))
        lib.py_pipeline_sequence_put_module_exec(self._pipeline, module._processor, path_c_string, svc._locator)
    ##
    # \brief Execute the \ref pipeline_sequence,
    # calling \ref mapp::core::pipeline::sequence::execute.
    # This method will call all module steps added by
    # \ref put_module_init and \ref put_module_exec.
    def execute(self):
        lib.py_pipeline_sequence_execute.argtypes = [ctypes.c_void_p]
        lib.py_pipeline_sequence_execute(self._pipeline)
