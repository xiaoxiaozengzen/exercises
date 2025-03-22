#include "inline2.hpp"

void fun2() {
  std::cout << "fun2: " 
  << "value_global: " << value_global << ", "
  << "value_global address: " << &value_global << ", "
  << "value_global1: " << value_global1 << ", "
  << "value_global1 address: " << &value_global1 << ", "
  << "value_global2: " << value_global2 << ", "
  << "value_global2 address: " << &value_global2
  << std::endl;
}