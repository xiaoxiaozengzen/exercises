cmake_minimum_required(VERSION 3.14)
project(time)

add_executable(time_example main.cpp)
add_executable(linux_time_example linux_time_example.cpp)

target_link_libraries(linux_time_example PUBLIC pthread)