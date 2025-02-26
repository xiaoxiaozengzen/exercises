/**
 * https://stackoverflow.com/questions/41793355/macro-redefined-warning
 */

#include <iostream>
#include <stdio.h>

// 重复定义宏在编译的时候会报warning：warning: "ADD" redefined
// 并且最下面的宏会覆盖最上面的，即使用最后一个找到的宏
#define ADD(x, y) (x * y)
#define ADD(x, y) (x + y)
#define ADD(x, y) (x - y)

// 可以先判断下是否有定义
#ifndef ADD
#define ADD(x, y) (x + y + y)
#endif

// 也可以直接error，编译的时候就会报错
#ifdef ADD
  # error Macro ADD has been defined
#else
  #define ADD(x, y) (x + y + y + y)
#endif

int main() {
  int a = ADD(1, 3);
  std::cout << a << std::endl;
}