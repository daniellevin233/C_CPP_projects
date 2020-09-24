cmake_minimum_required(VERSION 3.8)
project(ex1C__)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES big_integer.cpp
                big_integer.h
                my_set.cpp
                my_set.h
                big_int_tester.cpp)
#                my_set_tester.cpp)
add_executable(ex1C__ ${SOURCE_FILES})