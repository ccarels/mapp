cmake_minimum_required(VERSION 3.16)
project(test_mapp_core)

find_package(Boost COMPONENTS log REQUIRED)
message(STATUS "Boost_LOG_LIBRARY ${Boost_LOG_LIBRARY}")
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS}")

set(CMAKE_CXX_STANDARD 20)
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  set(CMAKE_CXX_FLAGS "-W -O1 -Wall -Wno-unused -Wpedantic -Wextra -g -ggdb3 -pthread")
endif()
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

add_definitions(-fprofile-arcs -ftest-coverage)
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/test_mapp_core.dir/tests/src)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Locate libthrowing_algorithm.so
if(DEFINED ENV{THROWING_ALGORITHM_LIB})
  set(THROWING_ALGORITHM_LIB $ENV{THROWING_ALGORITHM_LIB})
else()
  set(THROWING_ALGORITHM_LIB "" CACHE STRING "Path to throwing_algorithm shared object library")
endif()
message(STATUS "THROWING_ALGORITHM_LIB ${THROWING_ALGORITHM_LIB}")

if("${THROWING_ALGORITHM_LIB}" STREQUAL "")
  message(FATAL_ERROR "THROWING_ALGORITHM_LIB not set")
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

set(SRC 
        src/test_mapp_core.cpp
        src/test_processor.cpp
        src/test_managed.cpp
        src/test_fs_setup.cpp
        ../../../src/mapp/filesystem/fs_setup.cpp
        src/test_library.cpp
        src/test_py_wrappers.cpp
        ../../../src/mapp/python/py_library_provider.cpp
        ../../../src/mapp/python/py_managed_processor.cpp
        ../../../src/mapp/python/py_protobuf_config.cpp
        ../../../src/mapp/python/py_service_locator.cpp
        ../../../src/mapp/python/py_pipeline_sequence.cpp
        src/test_sequence.cpp
        src/main.cpp
    )

include_directories(src/ ../../src/)
include_directories(/usr/include)
link_directories(/usr/lib)

add_custom_target(lcov COMMAND mkdir -p lcoverage)
add_custom_command(TARGET lcov
    COMMAND lcov --capture --directory ../ --output-file lcoverage/unfiltered_coverage.info
    COMMAND lcov --remove lcoverage/unfiltered_coverage.info '/usr/include/*' '/usr/local/*' 'src/*' '/usr/local/include/*' -o lcoverage/filtered_coverage.info
    COMMAND genhtml lcoverage/filtered_coverage.info --output-directory lcoverage
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

enable_testing()
add_executable(${PROJECT_NAME} ${SRC})
add_test(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/test_mapp_core)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} -fprofile-arcs)
target_link_libraries(${PROJECT_NAME} -ftest-coverage)
target_link_libraries(${PROJECT_NAME} dl)
target_link_libraries(${PROJECT_NAME} ${MYMODULE_CONFIG_DATA_MODEL_LIB})
target_link_libraries(${PROJECT_NAME} ${THROWING_ALGORITHM_LIB})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LOG_LIBRARY})
