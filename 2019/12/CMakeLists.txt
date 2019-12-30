cmake_minimum_required(VERSION 3.13)
project(AdventOfCode_2019_12)

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

target_sources(test PRIVATE src/n_body_engine.cpp)
target_sources(test PRIVATE test/n_body_engine.cpp)

add_executable(main_12)
target_sources(main_12 PRIVATE src/main.cpp)
target_sources(main_12 PRIVATE src/n_body_engine.cpp)
