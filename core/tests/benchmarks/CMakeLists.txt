cmake_minimum_required(VERSION 3.12)
project(test_benchmark_mapp_core)

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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -O1 -Wall -Wno-unused -Wpedantic -Wextra")
endif()
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

add_definitions(-fprofile-arcs -ftest-coverage)
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/test_mapp_core.dir/tests/src)


find_package(benchmark REQUIRED)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

set(SRC 
        src/main.cpp
        ../../../src/mapp/algorithm/null_algorithm/null_algorithm.cpp
    )

include_directories(src/ ../../src/)
include_directories(/usr/include)
link_directories(/usr/lib)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

enable_testing()
add_executable(${PROJECT_NAME} ${SRC})
add_test(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/test_mapp_core)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${Boost_LOG_LIBRARY})
target_link_libraries(${PROJECT_NAME} -fprofile-arcs)
target_link_libraries(${PROJECT_NAME} -ftest-coverage)
target_link_libraries(${PROJECT_NAME} -ldl)
target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
