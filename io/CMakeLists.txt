cmake_minimum_required(VERSION 3.23)
project(io_example)

add_executable(io_buffer buffer.cpp)

add_executable(filebuf filebuf.cpp)
add_executable(ifstream ifstream.cpp)
add_executable(ofstream ofstream.cpp)

add_executable(stringbuf stringbuf.cpp)
add_executable(stringstream stringstream.cpp)

add_executable(ios ios.cpp)
target_link_libraries(ios pthread)
target_compile_options(ios PRIVATE -O0)

add_executable(locale locale.cpp)

add_executable(iomanip iomanip.cpp)