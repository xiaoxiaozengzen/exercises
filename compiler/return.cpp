#include <iostream>

void fun1() {
  std::cout << "fun1" << std::endl;
}

// 未定义行为
std::uint32_t fun2(std::uint32_t a) {
  // std::cout << "fun2" << std::endl;
}

std::uint32_t fun3(std::uint32_t a) {
  // std::cout << "fun3" << std::endl;
  return 10;
}

int main() {
  std::uint32_t a = 15;

  std::uint32_t ret3 = fun3(a);
  std::cout << "ret3: " << ret3 << std::endl;

  std::uint32_t ret2 = fun2(a);
  std::cout << "ret2: " << ret2 << std::endl;
}