########################################################
# 文件位于统一开发环境目录src
# 功能：动态自动添加目录add_subdirectory
# 条件：目录下必须有CMakeLists.txt文件，否则不添加
########################################################
cmake_minimum_required(VERSION 3.14)
project(EXERCISE)

find_program(CCACHE_FOUND ccache REQUIRED)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

## 获取当前目录下文件夹
macro(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

## 获取当前目录下所有文件(包含文件和文件夹)
macro(SUBFILELIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        LIST(APPEND dirlist ${child})
    endforeach()
    set(${result} ${dirlist})
endmacro()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})
## ADD
foreach(subdir ${SUBDIRS})
    SUBFILELIST(SUBSUBFILES ${CMAKE_CURRENT_LIST_DIR}/${subdir})
    foreach(subsubdir ${SUBSUBFILES})
        if ("CMakeLists.txt" STREQUAL ${subsubdir})
            message("-- Add subdir : " ${subdir})
            add_subdirectory(${subdir})
        endif()
    endforeach()
endforeach()