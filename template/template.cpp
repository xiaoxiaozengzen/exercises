#include <iostream>

template <typename T, size_t n>
size_t array_size(const T (&)[n]) {
  return n;
}

void array_test() {
  int a[] = {1, 2, 3};

  int *ap = a;      // a pointer, size is lost
  int(&ar)[3] = a;  // a reference to the array, size is not lost
  // 错误：invalid initialization of reference of type ‘int (&)[2]’ from expression of type ‘int[3]’ 
  // int (&ar2)[2] = a;

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
    std::cout << t << std::endl;
  }
};

void template_fun() {
  A a;
  a.print(1);
  // 显示指定模板参数
  a.template print<int>(2);
}

int main() {
  std::cout << "===================== array_test=====================" << std::endl;
  array_test();
  std::cout << "===================== template_fun=====================" << std::endl;
  template_fun();
  return 0;
}