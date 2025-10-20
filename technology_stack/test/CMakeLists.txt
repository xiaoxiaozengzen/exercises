project(technology_stack_test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

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


file(GLOB_RECURSE LWRB_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../ring_buffer/*.c)
add_library(lwrb ${LWRB_SOURCE_FILES})
target_include_directories(lwrb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ring_buffer/lwrb/src/include)
target_compile_definitions(lwrb PUBLIC
  -DLWRB_DISABLE_ATOMIC
)
target_compile_definitions(lwrb PRIVATE
  -DLWRB_DEV
)

add_executable(lwrb_test lwrb_test.cpp)
target_link_libraries(lwrb_test PUBLIC
  lwrb
)

add_executable(rate_test rate_test.cpp)
