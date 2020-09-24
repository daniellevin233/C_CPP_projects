cmake_minimum_required(VERSION 3.13)
project(ex1)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS -Wall -Wextra -pthread -g)

add_executable(ex1 osm.cpp)