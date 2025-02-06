cmake_minimum_required(VERSION 3.23)
project(io_example)

add_executable(io_file_example file_example.cpp)
target_link_libraries(io_file_example PUBLIC pthread)

add_executable(io_buffer buffer.cpp)