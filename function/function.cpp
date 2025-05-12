#include <iostream>
#include <string>

#include <functional>

/**
 * std::function是一个可调用对象的封装，可以**存储**任何可调用对象，包括函数指针、lambda表达式、bind表达式等
 */

/**
 * @brief 函数含有静态变量
 */
void fun_test(int a, int b) {
  static int i = 0;
  i++;
  std::cout << "fun_test: " << i << ", " << a << ", " << b << std::endl;
}

/**
 * template <class Ret, class... Args> 
 * class function<Ret(Args...)>;
 */
void function_test() {
  // member type
  if(std::is_same<std::function<int(int, int)>::result_type, int>::value) {
    std::cout << "std::function<int(int, int)>::result_type is int" << std::endl;
  } else {
    std::cout << "std::function<int(int, int)>::result_type is not int" << std::endl;
  }
  if(std::is_same<std::function<int(int)>::argument_type, int>::value) {
    std::cout << "std::function<int(int)>::argument_type is int" << std::endl;
  } else {
    std::cout << "std::function<int(int)>::argument_type is not int" << std::endl;
  }
#if 0
  // 只有一个参数的函数，std::function的argument_type是第一个参数的类型，否则未定义
  if(std::is_same<std::function<int(int, int)>::argument_type, int>::value) {
    std::cout << "std::function<int(int, int)>::argument_type is int" << std::endl;
  } else {
    std::cout << "std::function<int(int, int)>::argument_type is not int" << std::endl;
  }
#endif
  if(std::is_same<std::function<int(int, int)>::first_argument_type, int>::value) {
    std::cout << "std::function<int(int, int)>::first_argument_type is int" << std::endl;
  }
  if(std::is_same<std::function<int(int, int)>::second_argument_type, int>::value) {
    std::cout << "std::function<int(int, int)>::second_argument_type is int" << std::endl;
  }

  // member function
  std::function<int(int, int)> f1 = [](int a, int b) { return a + b; };
  std::cout << "f1: " << f1(1, 2) << std::endl; // f1: 3
  if(f1) {
    std::cout << "f1 is valid" << std::endl;
  } else {
    std::cout << "f1 is not valid" << std::endl;
  }
  if(f1.target_type() == typeid(int(int, int))) {
    std::cout << "f1 target_type is int(int, int)" << std::endl;
  } else {
    std::cout << "f1 target_type is not int(int, int)" << std::endl;
  }

  // 绑定含有静态变量的函数
  std::function<void(int, int)> f2 = std::bind(fun_test, std::placeholders::_1, std::placeholders::_2);
  std::function<void(int, int)> f3 = std::bind(fun_test, 1, 2);
  std::function<void(int, int)> f4 = std::bind(fun_test, std::placeholders::_1, 2);
  f2(3, 4); // fun_test: 1, 3, 4
  f3(3, 4); // fun_test: 2, 1, 2
  f4(3, 4); // fun_test: 3, 3, 2
  std::function<void(int, int)> f5 = f2;
  f5(5, 6); // fun_test: 4, 5, 6
}

/**
 * template <class T> 
 * class reference_wrapper;
 */
void reference_wrapper_test() {
  if(std::is_same<std::reference_wrapper<int>::type, int>::value) {
    std::cout << "std::reference_wrapper<int>::type is int" << std::endl;
  } else {
    std::cout << "std::reference_wrapper<int>::type is not int" << std::endl;
  }

  // member function
  int a = 1;
  std::reference_wrapper<int> r1(a);
  std::reference_wrapper<int> r2(r1);
  int& r3 = r1.get();
  std::cout << "r1: " << r1.get() << ", r2: " << r2.get() << ", r3: " << r3 << std::endl; // r1: 1, r2: 1, r3: 1
  a = 2;
  std::cout << "r1: " << r1.get() << ", r2: " << r2.get() << ", r3: " << r3 << std::endl; // r1: 2, r2: 2, r3: 2
}

void fun1(int a, int b) {
    std::cout << "fun1: " << a << ", " << b << std::endl;
}

/**
 * template <class Fn, class... Args>
 * bind (Fn&& fn, Args&&... args);
 * 
 * template <class Ret, class Fn, class... Args> 
 * bind (Fn&& fn, Args&&... args);
 * 
 * bind函数返回一个基于fn的函数对象，fn是一个可调用对象，并且将args绑定到其参数上
 * 
 * 每个参数可以是值，或者是placeholder
 * 如果参数是值，则会在调用时拷贝
 * 如果参数是placeholder，则会在调用时传递，并且参数调用顺序也要按照placeholder的顺序
 */
void bind_test() {
  std::function<void(int, int)> f1 = std::bind(fun1, 1, 2);
  f1(3, 4); // fun1: 1, 2

  std::function<void(int, int)> f2 = std::bind(fun1, std::placeholders::_1, 2);
  f2(3, 4); // fun1: 3, 2

  std::function<void(int, int)> f3 = std::bind(fun1, 1, std::placeholders::_1);
  f3(3, 4); // fun1: 1, 3

  std::function<void(int, int)> f4 = std::bind(fun1, std::placeholders::_2, std::placeholders::_1);
  f4(3, 4); // fun1: 4, 3

}

/**
 * template <class T>
 * reference_wrapper<const T> cref (const T& elem) noexcept;
 * 
 * template <class T>
 * reference_wrapper<const T> cref (reference_wrapper<T>& x) noexcept;
 * 
 * template <class T>
 * void cref (const T&&) = delete;
 */
void cerf_test() {
  int a = 1;
  std::reference_wrapper<int> r1 = std::ref(a);
  std::cout << "r1: " << r1.get() << std::endl; // r1: 1
  a = 2;
  std::cout << "r1: " << r1.get() << std::endl; // r1: 2
}

int main() {
  std::cout << "=================function_test=================" << std::endl;
  function_test();
  std::cout << "=================reference_wrapper_test=================" << std::endl;
  reference_wrapper_test();
  std::cout << "=================bind_test=================" << std::endl;
  bind_test();
  std::cout << "=================cerf_test=================" << std::endl;
  cerf_test();

  return 0;
}