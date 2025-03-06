project(keywords)

add_executable(thread_local thread_local.cpp)
target_link_libraries(thread_local pthread)

add_executable(mutabel mutabel.cpp)

set(CMAKE_CXX_STANDARD 17)
add_executable(constexpr constexpr.cpp)