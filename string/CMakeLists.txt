cmake_minimum_required(VERSION 3.23)
project(string_view)

add_executable(string_view string_view.cpp)
target_link_libraries(string_view PUBLIC pthread)