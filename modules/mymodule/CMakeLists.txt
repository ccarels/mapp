cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(mymodule DESCRIPTION "mymodule")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
message(STATUS "${PROTOBUF_LIBRARY}")

# Doxygen
option(DOCS "Enable building documentation with Doxygen" OFF)
if(${DOCS})
	include(cmake/doxygen.cmake)
endif()

set(CMAKE_CXX_STANDARD 20)
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  set(CMAKE_CXX_FLAGS "-W -Wall -Wno-unused -Wpedantic -Wextra")
endif()

# CUDA settings
#enable_language(CUDA)
#include(CheckLanguage)

#if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
#  set(CMAKE_CUDA_ARCHITECTURES 75)
#endif()

# Locate mapp-core
if(DEFINED ENV{MAPP_CORE_PATH})
  set(MAPP_CORE_PATH $ENV{MAPP_CORE_PATH})
  include_directories(${MAPP_CORE_PATH}/src/)
else()
  set(MAPP_CORE_PATH "" CACHE STRING "Path to mapp-core top-level directory")
  include_directories(${MAPP_CORE_PATH}/src/)
endif()
message(STATUS "MAPP_CORE_PATH ${MAPP_CORE_PATH}")

if("${MAPP_CORE_PATH}" STREQUAL "")
  message(FATAL_ERROR "MAPP_CORE_PATH not set")
endif()

# Locate data models
if(DEFINED ENV{MAPP_DATA_MODELS_PATH})
  set(MAPP_DATA_MODELS_PATH $ENV{MAPP_DATA_MODELS_PATH})
  include_directories(${MAPP_DATA_MODELS_PATH})
else()
  set(MAPP_DATA_MODELS_PATH "" CACHE STRING "Path to data models top-level directory")
  include_directories(${MAPP_DATA_MODELS_PATH})
endif()
message(STATUS "MAPP_DATA_MODELS_PATH ${MAPP_DATA_MODELS_PATH}")

if("${MAPP_DATA_MODELS_PATH}" STREQUAL "")
  message(FATAL_ERROR "MAPP_DATA_MODELS_PATH not set")
endif()

# Locate libmymodule_config_data_model.so
if(DEFINED ENV{MYMODULE_CONFIG_DATA_MODEL_LIB})
  set(MYMODULE_CONFIG_DATA_MODEL_LIB $ENV{MYMODULE_CONFIG_DATA_MODEL_LIB})
else()
  set(MYMODULE_CONFIG_DATA_MODEL_LIB "" CACHE STRING "Path to data models top-level directory")
endif()
message(STATUS "MYMODULE_CONFIG_DATA_MODEL_LIB ${MYMODULE_CONFIG_DATA_MODEL_LIB}")

if("${MYMODULE_CONFIG_DATA_MODEL_LIB}" STREQUAL "")
  message(FATAL_ERROR "MYMODULE_CONFIG_DATA_MODEL_LIB not set")
endif()

#add_library(mymodule_kernels SHARED src/mymodule_kernels.cu)
#set_property(TARGET mymodule_kernels PROPERTY CUDA_SEPARABLE_COMPILATION ON)
#set_target_properties(mymodule_kernels PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(mymodule_kernels PROPERTIES BUILD_SHARED_LIBS ON)

add_library(mymodule SHARED ${MAPP_CORE_PATH}/src/mapp/algorithm/processor.hpp src/mymodule.cpp)
target_link_libraries(mymodule ${PROTOBUF_LIBRARY} ${MYMODULE_CONFIG_DATA_MODEL_LIB})
#target_link_libraries(mymodule ${PROTOBUF_LIBRARY} ${MYMODULE_CONFIG_DATA_MODEL_LIB} mymodule_kernels)
