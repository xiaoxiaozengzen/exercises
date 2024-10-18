cmake_minimum_required(VERSION 3.23)
project(file_example)

add_executable(file_example file_example.cpp)
target_link_libraries(file_example PUBLIC pthread)