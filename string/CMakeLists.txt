cmake_minimum_required(VERSION 3.23)
project(string_view)

set(CMAKE_CXX_STANDARD 17)

add_executable(string_view string_view.cpp)
target_link_libraries(string_view PUBLIC pthread)

add_executable(string string.cpp)