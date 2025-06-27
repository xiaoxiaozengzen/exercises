cmake_minimum_required(VERSION 3.14)
project(algorithm)

add_executable(algorithm_binary_search binary_search.cpp)
add_executable(algorithm_equal_range equal_range.cpp)
# add_executable(algorithm_lower_bound lower_bound.cpp)
add_executable(algorithm_upper_bound upper_bound.cpp)
add_executable(algorithm_sort sort.cpp)

add_executable(non_modifying_operation non_modifying_operation.cpp)
add_executable(modifying_operation modifying_operation.cpp)