// The class any describes a type-safe container for single values of any copy constructible type.

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <memory>

void ConFUn(){
  std::any a;
  std::any a1(a);
  std::any a2(std::move(a));

  std::any a3(42);
  std::any a4(std::string("STR"));
  std::any a5(std::in_place_type<std::string>, 10, 'a');
  std::any a6(std::in_place_type<std::string>, {'a', 'b', 'c'});
}

void MemFun() {
  // 1. modifiers
  std::any a{std::string{"STR"}};
  a.emplace<std::string>("SSSS");
  std::any a1{std::string{"STR"}};
  a.swap(a1);
  a.reset();

  // 2. observers
  bool ret = a.has_value();
  if(ret){
    std::cout << "a has_value" << std::endl;
  } else {
    std::cout << "a no value" << std::endl;
  }
  ret = a1.has_value();
  if(ret){
    std::cout << "a1 has_value" << std::endl;
  } else {
    std::cout << "a1 no value" << std::endl;
  }
  const std::type_info& ti1 = a1.type();
  std::cout << "type: " << ti1.name() << std::endl;
  std::cout << "std::string: " << typeid(std::string).name() << std::endl;
  std::cout << "int: " << typeid(int).name() << std::endl;
}

void NonMemFun() {
  std::any a{std::string{"STR"}};
  std::string ret = std::any_cast<std::string>(a);
  std::cout << "ret: " << ret << std::endl;
  try {
    int ret1 = std::any_cast<int>(a);
    std::cout << "ret1: " << ret1 << std::endl;
  } catch (const std::bad_any_cast& e) {
    std::cout << e.what() << std::endl;
  }

  std::any a1 = std::make_any<int>(42);
  std::cout << "a1: " << std::any_cast<int>(a1) << std::endl;
  std::any a2 = std::make_any<std::vector<int>>({1, 2, 3, 4, 5});
  std::cout << "a2: ";
  for(auto& i : std::any_cast<std::vector<int>>(a2)){
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main(){
  std::cout << "===============ConFun===============" << std::endl;
  ConFUn();
  std::cout << "===============MemFun===============" << std::endl;
  MemFun();
  std::cout << "===============NonMemFun===============" << std::endl;
  NonMemFun();
  return 0;
}