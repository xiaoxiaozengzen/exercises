cmake_minimum_required(VERSION 3.23)
project(template)

set(CMAKE_CXX_STANDARD 17)

add_executable(template_fun template_fun.cpp template_fun2.cpp)
add_executable(template_derive template_derive.cpp)
add_executable(template_class template_class.cpp)
add_executable(template_variable template_variable.cpp)