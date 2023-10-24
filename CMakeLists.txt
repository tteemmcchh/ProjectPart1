cmake_minimum_required(VERSION 3.21)
project(ProjectPart1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-1.14.0)
include_directories(lib/googletest-1.14.0/googletest/include)

add_executable(run_tests qa/account_tests.cpp internal/methods.h)
target_link_libraries(run_tests gtest gtest_main)

add_executable(run_app app.cpp internal/methods.h)
