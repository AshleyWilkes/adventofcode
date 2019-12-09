cmake_minimum_required(VERSION 3.13)
project(AdventOfCode_2019_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(main_04)
target_sources(main_04 PRIVATE src/main.cpp)
