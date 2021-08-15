cmake_minimum_required(VERSION 3.12)
project(test_pymodule_template_coverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wno-unused -pedantic")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

add_definitions(-fprofile-arcs -ftest-coverage)
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/test_mapp_core.dir/tests/src)

find_package(Boost COMPONENTS log REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS}")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
message(STATUS "${PROTOBUF_LIBRARY}")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Look for core
if(DEFINED ENV{MAPP_CORE_PATH})
  include_directories($ENV{MAPP_CORE_PATH}src)
  set(MAPP_CORE_PATH $ENV{MAPP_CORE_PATH}src)
else()
  set(MAPP_CORE_PATH "" CACHE STRING "Path to mapp-core top-level directory")
  include_directories(${MAPP_CORE_PATH}/src/)
endif()
message(STATUS "MAPP_CORE_PATH: ${MAPP_CORE_PATH}")

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

# Locate libpymodule_template_config_data_model.so
if(DEFINED ENV{CONFIG_DATA_MODEL_LIB})
  set(CONFIG_DATA_MODEL_LIB $ENV{CONFIG_DATA_MODEL_LIB})
else()
  set(CONFIG_DATA_MODEL_LIB "" CACHE STRING "Path to configuration shared object library of the configuration data.")
endif()
message(STATUS "CONFIG_DATA_MODEL_LIB ${CONFIG_DATA_MODEL_LIB}")
if("${CONFIG_DATA_MODEL_LIB}" STREQUAL "")
  message(FATAL_ERROR "CONFIG_DATA_MODEL_LIB not set")
endif()

# Locate .so
if(DEFINED ENV{MODULE_LIB})
  set(MODULE_LIB $ENV{MODULE_LIB})
else()
  set(MODULE_LIB "" CACHE STRING "Path to the shared object library being tested.")
endif()
message(STATUS "MODULE_LIB ${MODULE_LIB}")
if("${MODULE_LIB}" STREQUAL "")
  message(FATAL_ERROR "MODULE_LIB not set")
endif()

set(SRC 
        src/test_pymodule_template.cpp
        src/main.cpp
    )

include_directories(src/ ../../src/)
include_directories(/usr/include)
link_directories(/usr/lib)

add_custom_target(lcov COMMAND mkdir -p lcoverage)
add_custom_command(TARGET lcov
    COMMAND lcov --capture --directory ../ --output-file lcoverage/unfiltered_coverage.info
    COMMAND lcov --remove lcoverage/unfiltered_coverage.info '/usr/include/*' 'src/*' '/usr/local/include/*' '${MAPP_CORE_PATH}*' '${MAPP_DATA_MODELS_PATH}*' -o lcoverage/filtered_coverage.info
    COMMAND genhtml lcoverage/filtered_coverage.info --output-directory lcoverage
)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

enable_testing()
add_executable(${PROJECT_NAME} ${SRC})
add_test(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${Boost_LOG_LIBRARY})
target_link_libraries(${PROJECT_NAME} -fprofile-arcs)
target_link_libraries(${PROJECT_NAME} -ftest-coverage)
target_link_libraries(${PROJECT_NAME} -ldl)
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CONFIG_DATA_MODEL_LIB})
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})
