cmake_minimum_required(VERSION 3.23)
project(io_example)

add_executable(io_file_example file_example.cpp)
target_link_libraries(io_file_example PUBLIC pthread)

add_executable(io_buffer buffer.cpp)

add_executable(filebuf filebuf.cpp)
add_executable(ifstream ifstream.cpp)
add_executable(ofstream ofstream.cpp)

add_executable(stringbuf stringbuf.cpp)
add_executable(stringstream stringstream.cpp)

add_executable(ios ios.cpp)

add_executable(locale locale.cpp)