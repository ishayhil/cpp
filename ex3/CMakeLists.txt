cmake_minimum_required(VERSION 3.12.3)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#add_subdirectory(cpp_ex3_tests)
add_executable(SpamDetector SpamDetector.cpp HashMap.hpp)
target_link_libraries(SpamDetector ${Boost_LIBRARIES})
target_compile_options(SpamDetector PRIVATE -Wall -Wextra -Werror -Wvla)

add_subdirectory(tests)

#
#cmake_minimum_required(VERSION 3.12.3)
#project(FractalDrawer)
#
#set(CMAKE_CXX_STANDARD 14)
#
#find_package(Boost COMPONENTS filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#
#add_executable(FractalDrawer FractalDrawer.cpp Fractal.cpp Fractal.h)
#target_link_libraries(FractalDrawer ${Boost_LIBRARIES})