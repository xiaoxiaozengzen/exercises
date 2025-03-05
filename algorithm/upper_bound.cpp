// template <class ForwardIterator, class T>
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);

// template <class ForwardIterator, class T, class Compare>
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low=std::lower_bound (v.begin(), v.end(), 20); // 返回第一个不小于20的元素位置
  up= std::upper_bound (v.begin(), v.end(), 20); // 返回第一个大于20的元素位置

  std::cout << "lower_bound at position " << (low- v.begin()) << '\n';
  std::cout << "upper_bound at position " << (up - v.begin()) << '\n';

  return 0;
}
