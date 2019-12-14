cmake_minimum_required(VERSION 3.13)
project(AdventOfCode_2019_06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(test)
target_include_directories(test PRIVATE src)
target_include_directories(test PRIVATE test)
target_include_directories(test PRIVATE /usr/include)
target_link_libraries(test PRIVATE gtest)
target_link_libraries(test PRIVATE gtest_main)
target_link_libraries(test PRIVATE gmock)
target_link_libraries(test PRIVATE gmock_main)
target_link_libraries(test PRIVATE pthread)

target_sources(test PRIVATE src/orbit_map.cpp)
target_sources(test PRIVATE test/orbit_map.cpp)

add_executable(main_06)
target_sources(main_06 PRIVATE src/main.cpp)
target_sources(main_06 PRIVATE src/orbit_map.cpp)
