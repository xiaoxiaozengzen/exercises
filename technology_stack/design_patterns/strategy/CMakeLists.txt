set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(dp_strategy ${SRCS})