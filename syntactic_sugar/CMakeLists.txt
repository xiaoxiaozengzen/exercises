cmake_minimum_required(VERSION 3.14)
project(syntactic_sugar)

set(CMAKE_CXX_STANDARD 17)

add_executable(optional optional.cpp)

add_executable(variant variant.cpp)

add_executable(any any.cpp)

add_executable(string_view string_view.cpp)
target_link_libraries(string_view PRIVATE pthread)

add_executable(filesystem filesystem.cpp)
