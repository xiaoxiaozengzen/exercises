project(compiler)

set(CMAKE_CXX_STANDARD 14)

if(NO_OPTIMIZATION)
    add_compile_options(-Wall -Wextra -pedantic -fno-elide-constructors)
endif()

add_executable(RVO RVO.cpp)

add_executable(const_auto const_auto_&.cpp)
target_link_libraries(const_auto PUBLIC pthread)

add_executable(no_return no_return.cpp)