cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(pymodule_template DESCRIPTION "pymodule_template")

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

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

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

add_library(pymodule_template SHARED ${MAPP_CORE_PATH}/src/mapp/algorithm/processor.hpp src/pymodule_template.hpp src/pymodule_template.cpp ${MAPP_DATA_MODELS_PATH}/pymodule_template/generated/cpp/pymodule_template_config_data_model.pb.cc)
target_link_libraries(pymodule_template ${PYTHON_LIBRARIES} ${PROTOBUF_LIBRARY})
