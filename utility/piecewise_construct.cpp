#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// piecewise_construct 分段构造
// constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();

int main() {
  std::pair<std::string, std::vector<int>> foo(
      std::piecewise_construct,
      std::tuple<std::string>(
          "test"),  // 找到对应类型的。和当前tuple数量相等的参数的构造函数。找不到就报错
      std::tuple<int>{10});
  std::cout << "foo.first: " << foo.first << '\n';
  std::cout << "foo.second:";
  for (int& x : foo.second) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}