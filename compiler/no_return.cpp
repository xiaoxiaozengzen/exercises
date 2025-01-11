#include <iostream>

std::uint32_t fun() {
  std::cout << "fun" << std::endl;
}

std::uint32_t fun1() { 
  std::cout << "fun1" << std::endl;
  int * a = nullptr;
  *a = 10;
  fun();
}

// 未定义行为
std::uint32_t fun2(std::uint32_t a) {
  std::cout << "fun2" << std::endl;
  fun1();
}

std::uint32_t fun3(std::uint32_t a) {
  std::cout << "fun3" << std::endl;
  fun2(1); 
  return 10;
}

/**
 * 没有返回值的函数，如果调用的函数也没有返回值，那么会导致未定义行为。并且程序奔溃时，查看调用栈可能会返现调用栈不正确。
 */
int main() {
  std::uint32_t a = 15;

  std::uint32_t ret3 = fun3(a);
  std::cout << "ret3: " << ret3 << std::endl;

  std::uint32_t ret2 = fun2(a);
  std::cout << "ret2: " << ret2 << std::endl;
}