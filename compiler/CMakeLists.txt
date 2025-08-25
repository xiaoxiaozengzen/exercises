project(compiler)

set(CMAKE_CXX_STANDARD 14)

if(NO_OPTIMIZATION)
  message(STATUS "Disable optimization")
  # -fno-elide-constructors // 禁止返回值优化跟拷贝消除，减少不必要的构造、拷贝、移动
  add_compile_options(-Wall -Wextra -pedantic -fno-elide-constructors)
endif()

add_executable(RVO RVO.cpp)

add_executable(const_auto const_auto_&.cpp)
target_link_libraries(const_auto PUBLIC pthread)

add_executable(no_return no_return.cpp)

add_executable(macro_redefined macro_redefined.cpp)