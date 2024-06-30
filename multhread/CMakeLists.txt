cmake_minimum_required(VERSION 3.14)
project(multhread)

add_executable(pod_type pod_type.cpp)

add_executable(atomic_example atomic_example.cpp)
target_link_libraries(atomic_example PUBLIC pthread)