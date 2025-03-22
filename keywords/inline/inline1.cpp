#include "inline1.hpp"

void fun1() {
    std::cout << "fun1: " 
    << "value_global: " << value_global << ", "
    << "value_global address: " << &value_global << ", "
    << "value_global1: " << value_global1 << ", "
    << "value_global1 address: " << &value_global1 << ", "
    << "value_global2: " << value_global2 << ", "
    << "value_global2 address: " << &value_global2
    << std::endl;
}