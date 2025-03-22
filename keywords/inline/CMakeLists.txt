project(inline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)


file(GLOB_RECURSE inline_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(inline ${inline_SRCS})
