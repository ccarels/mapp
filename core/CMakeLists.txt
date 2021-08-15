cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(mapp-core DESCRIPTION "MAPP CORE")

#SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS log REQUIRED)
message(STATUS "Boost_LOG_LIBRARY ${Boost_LOG_LIBRARY}")
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  set(CMAKE_CXX_FLAGS "-W -O0 -Wall -Wno-unused -Wpedantic -Wextra -g -ggdb3 -pthread")
endif()

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

# Doxygen
option(DOCS "Enable building documentation with Doxygen" OFF)
if(${DOCS})
	include(cmake/doxygen.cmake)
endif()

include_directories(src/mapp/library)

# Detect OS for library config file
if(UNIX)
	set(LIB_EXT "so")
elseif(APPLE)
	set(LIB_EXT "dylib")
elseif(MSVC)
	set(LIB_EXT "dll")
endif()

# Library config file
get_filename_component(MODULES_DIR "${CMAKE_BINARY_DIR}/../../modules/" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(MODULES_DIR ${MODULES_DIR} CACHE STRING "Directory to the modules directory.")
configure_file("${PROJECT_SOURCE_DIR}/cmake/config.txt" "${CMAKE_CURRENT_BINARY_DIR}/config.txt")

# Python tests file
get_filename_component(DATA_MODELS_DIR "${CMAKE_BINARY_DIR}/../../data_models/" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(DATA_MODELS_DIR ${DATA_MODELS_DIR} CACHE STRING "Directory to the data_models directory required for Python coverage tests.")
configure_file("${PROJECT_SOURCE_DIR}/python/test_mapp_pipeline.py" "${CMAKE_CURRENT_BINARY_DIR}")
configure_file("${PROJECT_SOURCE_DIR}/python/py_mapp_core.py" "${CMAKE_CURRENT_BINARY_DIR}/")

set(LIBRARY_SOURCE_FILES src/mapp/python/py_library_provider.cpp
						 src/mapp/python/py_managed_processor.cpp
						 src/mapp/python/py_protobuf_config.cpp
						 src/mapp/python/py_service_locator.cpp
						 src/mapp/python/py_pipeline_sequence.cpp
						 src/mapp/filesystem/fs_setup.cpp)
add_library(${PROJECT_NAME} SHARED ${LIBRARY_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LOG_LIBRARY} dl)
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES BUILD_SHARED_LIBS ON)

# Compile null_algorithm, non_compliant_algorithm, and throwing_algorithm for tests
add_library(null_algorithm SHARED src/mapp/algorithm/null_algorithm/null_algorithm.cpp)
add_library(non_compliant_algorithm SHARED src/mapp/algorithm/non_compliant_algorithm/non_compliant_algorithm.cpp)
add_library(throwing_algorithm SHARED src/mapp/algorithm/throwing_algorithm/throwing_algorithm.cpp)
add_executable(exec-core-test src/mapp/library/loader.hpp src/main.cpp)
target_link_libraries(exec-core-test ${Boost_LOG_LIBRARY} ${PROTOBUF_LIBRARY} ${CMAKE_DL_LIBS} ${PYTHON_LIBRARIES})
