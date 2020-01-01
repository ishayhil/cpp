cmake_minimum_required(VERSION 3.15)
project(ex2_)

set(Boost_path "/usr/local/Cellar/boost")
set(Boost_INCLUDE_DIR "${Boost_path}/1.72.0/include")
find_package(Boost 1.72.0)

if (Boost_FOUND)
    message(STATUS "It works!")
    include_directories(${Boost_INCLUDE_DIR})
endif ()

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/Users/ishayhil/huji/cpp/ex2_/boost_1_68_0")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/Users/ishayhil/huji/cpp/ex2_/boost_1_68_0/libs")
#
#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2_ Fractal.h Fractal.cpp FractalDrawer.cpp)