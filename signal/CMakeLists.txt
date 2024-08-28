cmake_minimum_required(VERSION 3.23)
project(signal)

add_executable(signal signal.cpp)
target_link_libraries(signal PUBLIC pthread)