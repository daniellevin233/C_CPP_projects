cmake_minimum_required(VERSION 3.12.0)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3  big_integer.cpp
                    big_integer.h
                    my_set.h
                    my_set.cpp)