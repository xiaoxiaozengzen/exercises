cmake_minimum_required(VERSION 3.14)

add_executable(multi_stage_pipeline
    multi_stage_pipeline.cpp
)
target_include_directories(
    multi_stage_pipeline PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../utility
)
target_link_libraries(
    multi_stage_pipeline PRIVATE 
    pthread
)