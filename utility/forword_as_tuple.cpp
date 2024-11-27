#include <iostream>
#include <utility>
#include <tuple>
#include <string>

// template<class... Types>
// std::tuple<Types&&...> forward_as_tuple(Types&&... args) noexcept;

// 等价
// template<class... Types>
// std::tuple<Types&&...> forward_as_tuple (Types&&... args) noexcept
// {
//   return std::tuple<Types&&...>(std::forward<Types>(args)...);
// }

void print_pack (std::tuple<std::string&&,int&&> pack) {
  std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << '\n';
}

int main() {
  std::string str ("John");
  print_pack (std::forward_as_tuple(str+" Smith",25));
  print_pack (std::forward_as_tuple(str+" Daniels",22));
  return 0;
}