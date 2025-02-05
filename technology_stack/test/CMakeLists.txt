project(technology_stack_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(object_pool_test
object_pool_test.cpp
)
target_link_libraries(object_pool_test PUBLIC
  pthread
)

add_executable(thread_pool_version_2 thread_pool_version_2.cpp)
target_link_libraries(thread_pool_version_2 PUBLIC
  pthread
)