cmake_minimum_required(VERSION 3.12)
project(test_benchmark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wno-unused -pedantic")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/test_mapp_core.dir/tests/src)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS}")

find_package(benchmark REQUIRED)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

set(SRC 
        src/main.cpp
        ../../src/
    )

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
  set(MYMODULE_CONFIG_DATA_MODEL_LIB "" CACHE STRING "Path to configuration shared object library of the configuration data.")
endif()
message(STATUS "MYMODULE_CONFIG_DATA_MODEL_LIB ${MYMODULE_CONFIG_DATA_MODEL_LIB}")

if("${MYMODULE_CONFIG_DATA_MODEL_LIB}" STREQUAL "")
  message(FATAL_ERROR "MYMODULE_CONFIG_DATA_MODEL_LIB not set")
endif()

# Locate libmymodule.so
if(DEFINED ENV{MYMODULE_LIB})
  set(MYMODULE_LIB $ENV{MYMODULE_LIB})
else()
  set(MYMODULE_LIB "" CACHE STRING "Path to the shared object library being tested.")
endif()
message(STATUS "MYMODULE_LIB ${MYMODULE_LIB}")

if("${MYMODULE_LIB}" STREQUAL "")
  message(FATAL_ERROR "MYMODULE_LIB not set")
endif()

include_directories(src/ ../../src/)
include_directories(/usr/include)
link_directories(/usr/lib)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES)

enable_testing()
add_executable(${PROJECT_NAME} ${SRC})
add_test(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/test_mapp_core)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${MYMODULE_LIB})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${MYMODULE_CONFIG_DATA_MODEL_LIB})
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
