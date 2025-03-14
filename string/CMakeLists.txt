cmake_minimum_required(VERSION 3.23)
project(string_view)

set(CMAKE_CXX_STANDARD 17)

add_executable(string string.cpp)
add_executable(char_traits char_traits.cpp)