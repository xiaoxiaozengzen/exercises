cmake_minimum_required(VERSION 3.14)

set(EXEC_NAME pingpangbuffer)
add_executable(${EXEC_NAME}
    ${EXEC_NAME}.cpp
)
target_include_directories(
    ${EXEC_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../utility
)
target_link_libraries(
    ${EXEC_NAME} PRIVATE 
    pthread
)