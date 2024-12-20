project(compiler)

set(CMAKE_CXX_STANDARD 14)

if(NO_OPTIMIZATION)
    add_compile_options(-Wall -Wextra -pedantic -fno-elide-constructors)
endif()

add_executable(RVO RVO.cpp)