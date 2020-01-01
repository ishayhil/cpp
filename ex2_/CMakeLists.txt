cmake_minimum_required(VERSION 3.15)
project(ex2_)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/Users/ishayhil/huji/cpp/ex2_/boost_1_68_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/Users/ishayhil/huji/cpp/ex2_/boost_1_68_0/libs")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2_ main.cpp Fractal.h Fractal.cpp)