project(keywords)

add_executable(thread_local thread_local.cpp)
target_link_libraries(thread_local pthread)