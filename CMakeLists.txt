cmake_minimum_required(VERSION 3.21)
project(ProjectPart1)

set(CMAKE_CXX_STANDARD 14)

add_executable(run_app app.cpp internal/methods.h)
