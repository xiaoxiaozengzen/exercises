cmake_minimum_required(VERSION 3.14)
project(syntactic_sugar)

set(CMAKE_CXX_STANDARD 17)

add_executable(optional optional.cpp)
add_executable(variant variant.cpp)
