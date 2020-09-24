cmake_minimum_required(VERSION 3.8)
project(ex1_C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES my_cos.c)
add_executable(ex1_C ${SOURCE_FILES})