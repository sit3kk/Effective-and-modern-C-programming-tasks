cmake_minimum_required(VERSION 3.10)

project(StringTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(string_tests String.h string_tests.cpp)

target_link_libraries(string_tests ${GTEST_LIBRARIES} pthread)
