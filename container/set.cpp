#include <set>
#include <iostream>

void BasicSet() {
  std::set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(5);

  for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main() {
  BasicSet();
  return 0;
} 