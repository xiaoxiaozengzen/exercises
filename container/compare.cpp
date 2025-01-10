#include <iostream>

template <class T>
struct MyLess {
  bool operator()(const T& x, const T& y) const { return x < y; }
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};

int main() {
  int a = 10;
  int b = 20;

  MyLess<int> myLess;
  std::cout << myLess(a, b) << std::endl;
}