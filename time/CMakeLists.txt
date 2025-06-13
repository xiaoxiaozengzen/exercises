cmake_minimum_required(VERSION 3.14)
project(time)

add_executable(chrono chrono.cpp)

add_executable(linux_time_example linux_time_example.cpp)
target_link_libraries(linux_time_example PUBLIC pthread rt)

add_executable(posix_dynamic_clock posix_dynamic_clock.cpp)