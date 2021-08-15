cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(pymodule_template_config_data_model VERSION 0.0.0 DESCRIPTION "pymodule_template_config_data_model")

set(CMAKE_CXX_STANDARD 20)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})
add_library(${PROJECT_NAME} SHARED ./generated/cpp/${PROJECT_NAME}.pb.cc ./generated/cpp/${PROJECT_NAME}.pb.h)
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARY})
