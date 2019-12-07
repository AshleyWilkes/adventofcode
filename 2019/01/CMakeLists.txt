cmake_minimum_required(VERSION 3.13)
project(AdventOfCode_2019_01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(main_01)
target_sources(main_01 PRIVATE src/main.cpp)
