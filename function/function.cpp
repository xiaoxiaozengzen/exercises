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

int my_plus (int a, int b) {return a+b;}
int my_minus (int a, int b) {return a-b;}

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

  // constructor
  std::function<int(int, int)> f0; // 默认构造函数
  std::function<int(int, int)> f0_1 = nullptr; // nullptr构造函数
  if(f0_1) {
    std::cout << "f0_1 is valid" << std::endl;
  } else {
    std::cout << "f0_1 is not valid" << std::endl;
  }
  std::function<int(int, int)> f0_2 = [](int, int) { return 0; }; // lambda表达式构造函数
  if(f0_2) {
    std::cout << "f0_2 is valid" << std::endl;
  } else {
    std::cout << "f0_2 is not valid" << std::endl;
  }
  std::function<int(int, int)> f0_3 = f0_2; // 拷贝构造函数
  std::function<int(int, int)> f0_4 = std::move(f0_2); // 移动构造函数
  if(f0_4) {
    std::cout << "f0_4 is valid" << std::endl;
  } else {
    std::cout << "f0_4 is not valid" << std::endl;
  }
  if(f0_2) {
    std::cout << "f0_2 is valid" << std::endl;
  } else {
    std::cout << "f0_2 is not valid" << std::endl;
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
  std::cout << "f1 target_type: " << f1.target_type().name() << std::endl;
  std::function<int(int, int)> fun2 = my_plus;
  /**
   * target_type.name == PFiiiE
   * c++filt -t PFiiiE == int (*)(int, int)
   */
  std::cout << "fun2 target_type: " << fun2.target_type().name() << std::endl;
  std::cout << (*fun2.target<int(*)(int,int)>())(100, 20) << std::endl; // 120
#if 0
  // 会报错，因为当前target的实际参数是std::_Bind<int(int, int)>
  std::function<int(int, int)> fun3 = std::bind(my_plus, std::placeholders::_1, std::placeholders::_2);
  std::cout << (*fun3.target<int(*)(int,int)>())(100, 20) << std::endl; // 120
#endif
  *fun2.target<int(*)(int,int)>() = my_minus;
  int ret = fun2(100, 20);
  std::cout << "ret: " << ret << std::endl; // fun2: 80
  typedef int(*fun_ptr)(int, int);
  fun_ptr* fun4_ptr = fun2.target<fun_ptr>();
  if(fun4_ptr) {
    std::cout << "fun4_ptr is valid" << std::endl;
    std::cout << "fun4_ptr: " << (*fun4_ptr)(100, 20) << std::endl; // fun4_ptr: 80
  } else {
    std::cout << "fun4_ptr is not valid" << std::endl;
  }

  /**
   * @brief 绑定带有静态变量的函数
   * 
   * @note std::function本质上是存储对应可调用对象地址，因此以下调用会导致静态变量i被多次调用
   */
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