#include <iostream>

template <typename T, size_t n>
size_t array_size(const T (&)[n]) {
  return n;
}

void array_test() {
  int a[] = {1, 2, 3};

  // a pointer, size is lost
  int *ap = a;

  // a reference to the array, size is not lost
  int(&ar)[3] = a;

#if 0
  // 错误：invalid initialization of reference of type ‘int (&)[2]’ from expression of type ‘int[3]’ 
  int (&ar2)[2] = a;
#endif

  std::cout << "*ap: " << *ap << std::endl;
  std::cout << "ar: " << ar[0] << std::endl;

  std::cout << "arry_size: " << array_size<int>(ar) << std::endl;
}

class A {
 public:
  A() {
    std::cout << "A()" << std::endl;
  }
  ~A() {
    std::cout << "~A()" << std::endl;
  }

  template <typename T>
  void print(T t) {
    std::cout << "A: " << t << std::endl;
  }

  template <typename T>
  T get(T t) {
    return t;
  }
};

class B : public A {
  public:
   B() {
     std::cout << "B()" << std::endl;
   }
   ~B() {
     std::cout << "~B()" << std::endl;
   }

   template <typename T>
   static void print(T t) {
     std::cout << "B: " << t << std::endl;
   }
 };

void class_template_fun() {
  A a;
  a.print(1);
  // 显示指定模板参数
  a.template print<int>(2);
  int ret = a.template get<int>(3);
  std::cout << "ret: " << ret << std::endl;

  B b;
  b.A::template print<int>(4);
  b.template print<int>(5);
}

template <typename T>
void my_print(T t) {
  std::cout << "test: " << t << std::endl;
}

#if 0
/**
 * 模板特化函数会引起多重定义错误：
 * 1.模板特化函数就是一个普通函数，只是它的名字是模板名加上参数列表
 * 2.如果多个cpp文件中都引入了这个模板特化函数的定义，那么就会引起多重定义错误
 * 3.解决方法：
 *   a. 加inline关键字
 */
template <>
void my_print<int>(int t) {
  std::cout << "test int: " << t << std::endl;
}
#endif

template <>
inline void my_print<double>(double t) {
  std::cout << "test double: " << t << std::endl;
}

void spcecialization_test() {
  my_print(1);
  my_print(1.0);
}

int main() {
  std::cout << "===================== array_test=====================" << std::endl;
  array_test();
  std::cout << "===================== class_template_fun=====================" << std::endl;
  class_template_fun();
  std::cout << "===================== spcecialization_test=====================" << std::endl;
  spcecialization_test();
  return 0;
}