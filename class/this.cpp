#include <iostream>

class A {
public:
  A() {
    std::cout << "A construct" << std::endl;
  }
#if 0
  // error: call of overloaded ‘A()’ is ambiguous
  A(int a = 10):a(a) {
    std::cout << "A construct 2" << std::endl;
  }
#endif
  A(int a):a(a) {
    std::cout << "A construct 3" << std::endl;
  }

  void fun1() { std::cout << "A::fun1" << std::endl; }

  void fun1(int a) { std::cout << "A::fun1: " << a << std::endl; }

  void fun2() { std::cout << "A::fun2: " << this->a << std::endl; }

 public:
  int a = 10;
};

int main() {
  A a;
  a.fun1(2);
  a.fun2();
  return 0;
}