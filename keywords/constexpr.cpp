#include <iostream>
#include <array>

/**
 * 注意：
 * C++ 11标准中，为了解决 const 关键字的双重语义问题，保留了 const 表示“只读”的语义，而将“常量”的语义划分给了新添加的 constexpr 关键字。
 * 因此 C++11 标准中，建议将 const 和 constexpr 的功能区分开，即凡是表达“只读”语义的场景都使用 const，表达“常量”语义的场景都使用 constexpr。
 */

/**
 * “只读”和“不允许被修改”之间并没有必然的联系；const变量只是不能通过自身修改自己的值，但是可以通过其他途径修改自己的值。
 */
void ReadonlyTest() {
  int a = 10;
  const int& b = a;
  std::cout << "before: b = " << b << std::endl;
  a = 20;
  std::cout << "after: b = " << b << std::endl;
}

/**
 * constexpr 修饰的函数，要求函数的返回值和参数都是字面值类型，且函数体中只能有一条 return 语句。
 * 此时不能使用 const 修饰函数，因为 const 修饰的函数不一定是字面值类型。
 */
constexpr int sqr1(int arg) {
    return arg*arg;
} 
const int sqr2(int arg) {
    return arg*arg;
}
void ArrayTest(const std::size_t size) {
  // 编译报错：error: ‘size’ is not a constant expression
  // std::array<int, size> arr;

  const std::size_t arr_size = 10;
  std::array<int, arr_size> arr1;

  std::array<int, sqr1(10)> arr2;

  // 编译报错： error: call to non-‘constexpr’ function ‘const int sqr2(int)’
  // std::array<int, sqr2(10)> arr3;
}

class Example {
 public:
  Example():x_(0), y_(0) {
    std::cout << "Example()" << std::endl;
  }

  /**
   * constexpr还能修饰类的构造函数，即保证传递给该构造函数的所有参数都是constexpr，
   * 那么产生的对象的所有成员都是constexpr。该对象是constexpr对象了，可用于只使用constexpr的场合。 
   */
  constexpr Example(int x) : x_(x), y_(0) {
    std::cout << "Example(int x)" << std::endl;
  }

  void setX(int x) {
    std::cout << "setX(int x)" << std::endl;
    x_ = x;
  }

  void getX(int x) const {
    std::cout << "getX(int x) const" << std::endl;
  }

  // 编译报错：error: static member function ‘static void Example::print()’ cannot have cv-qualifier
  // static void print() const{
  //   std::cout << "print()" << std::endl;
  // }

  constexpr int print() {
    // 编译报错：只能有简单的一个rerurn语句，否则报错调用非constexpr函数。比如下面的std::cout打印
    // std::cout << "print() constexpr" << std::endl;
    return x_;
  }

  void setY(int y) const {
    std::cout << "print() mutable" << std::endl;
    y_ = y;
  }

 private:
  int x_;
  mutable int y_;
};

void example() {
  Example e;
  Example e1(10);

  e.setY(10);
  e1.setX(20);
}

// 重载
// 不注释函数的话，编译报错：error: call of overloaded ‘my_print(const int&)’ is ambiguous
// void my_print(int a) {
//   std::cout << "my_print(int a)" << std::endl;
// }
// void my_print(const int a) {
//   std::cout << "my_print(const int a)" << std::endl;
// }
void my_print(const int& a) {
  std::cout << "my_print(const int a)" << std::endl;
}

void PrintTest() {
  int a = 10;
  const int& b = a;
  my_print(b);
  // my_print(10);
}

int main() {
  std::cout << "==================== ArrayTest ====================" << std::endl;
  ArrayTest(10);
  std::cout << "==================== example ====================" << std::endl;
  example();
  std::cout << "==================== ReadonlyTest ====================" << std::endl;
  ReadonlyTest();
  std::cout << "==================== PrintTest ====================" << std::endl;
  PrintTest();
}