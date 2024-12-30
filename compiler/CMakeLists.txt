project(compiler)

set(CMAKE_CXX_STANDARD 14)

if(NO_OPTIMIZATION)
    add_compile_options(-Wall -Wextra -pedantic -fno-elide-constructors)
endif()

add_executable(RVO RVO.cpp)

add_executable(question_1 question_1.cpp)
target_link_libraries(question_1 PUBLIC pthread)

add_executable(return return.cpp)