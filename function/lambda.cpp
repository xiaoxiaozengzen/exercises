#include <iostream>

/**
 * lambda表达式的底层实现是一个闭包类
 *
 * 对于 [a, &b](int x) { return a + b + x; };
 * 其实现的类类似于
 */
class __lambda_123 {
 private:
  int a;   // 按值捕获
  int& b;  // 按引用捕获
 public:
  __lambda_123(int a_, int& b_) : a(a_), b(b_) {}
  int operator()(int x) const {
#if 0
    // 编译报错，尝试修改成员变量
    a++;
#endif
    return a + b + x;
  }
};

void lambda_example() {
  int a = 1;
  int b = 2;
  auto f = [a, &b](int x) { return a + b + x; };
  std::cout << "f(3): " << f(3) << std::endl;  // f(3): 6
  b = 3;
  std::cout << "f(3): " << f(3) << std::endl;  // f(3): 7

  // 等价于
  __lambda_123 f2(a, b);
  std::cout << "f2(3): " << f2(3) << std::endl;  // f2(3): 7
}

void mutable_lambda() {
  int a = 1;
  int b = 2;
  int c = 3;
  auto f = [a, &b](int c) mutable {
    // operator()修改成了 mutable，修改按值捕获的变量不会编译报错了
    a++; 
  };

  f(c);
  std::cout << "a: " << a << std::endl;  // a
  std::cout << "b: " << b << std::endl;  // b
  std::cout << "c: " << c << std::endl;  // c
}

int main() {
  std::cout << "=================lambda_example=================" << std::endl;
  lambda_example();
  std::cout << "=================mutable_lambda=================" << std::endl;
  mutable_lambda();

  return 0;
}