#include <functional>
#include <iostream>
#include <string>

// template<class T>
// struct hash;

void MemberType() {
  std::hash<int> hash_int;
  if (std::is_same<std::hash<int>::result_type, std::size_t>::value) {
    std::cout << "std::hash<int>::result_type is std::size_t" << std::endl;
  }
  if (std::is_same<std::hash<int>::argument_type, int>::value) {
    std::cout << "std::hash<int>::argument_type is int" << std::endl;
  }
}

void MemFun() {
  // size_t
  // operator()(_Tp __val) const noexcept
  // {
  //     using __type = typename underlying_type<_Tp>::type;
  //     return hash<__type>{}(static_cast<__type>(__val));
  // }
  std::hash<int> hash_int;
  int a = 10;
  std::cout << "hash_int(a): " << hash_int(a) << std::endl;

  std::string str = "hello";
  std::hash<std::string> hash_str;
  std::cout << "hash_str(str): " << hash_str(str) << std::endl;
}

int main() {
  std::cout << "--------------------------------MemberType--------------------------------"
            << std::endl;
  MemberType();
  std::cout << "--------------------------------MemFun--------------------------------"
            << std::endl;
  MemFun();
}