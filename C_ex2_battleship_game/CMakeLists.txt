cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES battleships.c battleships_game.c battleships.h)
add_executable(untitled ${SOURCE_FILES})