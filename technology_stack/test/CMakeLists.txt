project(technology_stack_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(object_pool_test
object_pool_test.cpp
)
target_link_libraries(object_pool_test PUBLIC
  pthread
)