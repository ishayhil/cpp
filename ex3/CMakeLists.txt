cmake_minimum_required(VERSION 3.15)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(ex3 HashMap.cpp HashMap.hpp)
target_compile_options(ex3 PRIVATE -Wall -Wextra -Werror -Wvla)