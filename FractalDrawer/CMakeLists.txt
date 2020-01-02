cmake_minimum_required(VERSION 3.12.3)
project(FractalDrawer)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(FractalDrawer FractalDrawer.cpp Fractal.cpp Fractal.h)
target_link_libraries(FractalDrawer ${Boost_LIBRARIES})