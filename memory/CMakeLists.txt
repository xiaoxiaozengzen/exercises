cmake_minimum_required(VERSION 3.0)
project(memory)

add_executable(shared_ptr shared_ptr.cpp)
add_executable(unique_ptr unique_ptr.cpp)
add_executable(weak_ptr weak_ptr.cpp)
target_link_libraries(weak_ptr pthread)