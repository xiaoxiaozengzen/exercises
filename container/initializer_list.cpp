#include <initializer_list>
#include <iostream>

// template<class T> class initializer_list;

void MemberTypes() {
  std::initializer_list<int> il = {1, 2, 3, 4, 5};

  if (std::is_same<std::initializer_list<int>::value_type, int>::value) {
    std::cout << "initializer_list<int>::value_type is int" << std::endl;
  }
  if (std::is_same<std::initializer_list<int>::reference, const int&>::value) {
    std::cout << "initializer_list<int>::reference is const int&" << std::endl;
  }
  if (std::is_same<std::initializer_list<int>::const_reference, const int&>::value) {
    std::cout << "initializer_list<int>::const_reference is const int&" << std::endl;
  }
  if (std::is_same<std::initializer_list<int>::iterator, const int*>::value) {
    std::cout << "initializer_list<int>::iterator is const int*" << std::endl;
  }
  if (std::is_same<std::initializer_list<int>::const_iterator, const int*>::value) {
    std::cout << "initializer_list<int>::const_iterator is const int*" << std::endl;
  }
  if (std::is_same<std::initializer_list<int>::size_type, size_t>::value) {
    std::cout << "initializer_list<int>::size_type is size_t" << std::endl;
  }

  std::cout << "il.size: " << il.size() << std::endl;
  std::cout << "il.begin: " << *il.begin() << std::endl;
  std::cout << "il.end: " << *(il.end() - 1) << std::endl;
}

int main() { MemberTypes(); }