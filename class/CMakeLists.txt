cmake_minimum_required(VERSION 3.14)
project(class_example)

add_executable(operator operator.cpp)
add_executable(virtual_exe virtual.cpp)
target_link_libraries(virtual_exe pthread)
add_executable(this_exe this.cpp)
add_executable(point point.cpp)
add_executable(friend_class friend_class.cpp)
add_executable(class_struct struct.cpp)
add_executable(enum enum.cpp)
add_executable(struct struct.cpp)
add_executable(con_decon_order con_decon_order.cpp)
target_link_libraries(con_decon_order pthread)