cmake_minimum_required(VERSION 3.13)
project(mapreduce)

# add_library(mapreduce MapReduceFramework.h MapReduceFramework.cpp)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# set_property(TARGET mapreduce PROPERTY CXX_STANDARD 11)
# target_compile_options(mapreduce PUBLIC -Wall -Wextra -pthread)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
set(GCC_COVERAGE_COMPILE_FLAGS -Wall -Wextra -g)
add_executable(mapreduce FileWordCounter.cpp MapReduceFramework.cpp Barrier.cpp)
