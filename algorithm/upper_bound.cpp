// template <class ForwardIterator, class T>
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);

// template <class ForwardIterator, class T, class Compare>
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);

/**
 * Compare comp
 * @note 接收两个参数，返回bool值
 * @param first 第一个参数是const T& val中的val
 * @param second 被迭代器指向的元素
 * @return true: first < second
 * @return false: first >= second
 */

#include <iostream>
#include <algorithm>
#include <vector>

void normal() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low=std::lower_bound (v.begin(), v.end(), 20); // 返回第一个不小于20的元素位置
  up= std::upper_bound (v.begin(), v.end(), 20); // 返回第一个大于20的元素位置

  if(low == v.end()) {
    std::cout << "lower_bound not found" << std::endl;
  } else {
    std::cout << "lower_bound at position " << (low- v.begin()) << ", value is " << *low << std::endl;
  }
  
  if(up == v.end()) {
    std::cout << "upper_bound not found" << std::endl;
  } else {
    std::cout << "upper_bound at position " << (up - v.begin()) << ", value is " << *up << std::endl;
  }
}

void abnormal() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low, up, low2;
  low=std::lower_bound (v.begin(), v.end(), 9); // 返回第一个不小于9的元素位置
  low2=std::lower_bound (v.begin(), v.end(), 31); // 返回第一个不小于31的元素位置
  up= std::upper_bound (v.begin(), v.end(), 31); // 返回第一个大于31的元素位置

  if(low == v.end()) {
    std::cout << "lower_bound not found" << std::endl;
  } else {
    std::cout << "lower_bound at position " << (low- v.begin()) << ", value is " << *low << std::endl;
  }

  if(low2 == v.end()) {
    std::cout << "lower_bound not found" << std::endl;
  } else {
    std::cout << "lower_bound at position " << (low2- v.begin()) << ", value is " << *low2 << std::endl;
  }
  
  if(up == v.end()) {
    std::cout << "upper_bound not found" << std::endl;
  } else {
    std::cout << "upper_bound at position " << (up - v.begin()) << ", value is " << *up << std::endl;
  }
}

struct MyLess {
  bool operator() (const int& first, const int& second) {
    return (first < second);
  }
};

void custom_compare() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low=std::lower_bound (v.begin(), v.end(), 20, MyLess()); // 返回第一个不小于20的元素位置
  up= std::upper_bound (v.begin(), v.end(), 20, MyLess()); // 返回第一个大于20的元素位置
  if(low == v.end()) {
    std::cout << "lower_bound not found" << std::endl;
  } else {
    std::cout << "lower_bound at position " << (low- v.begin()) << ", value is " << *low << std::endl;
  }
  if(up == v.end()) {
    std::cout << "upper_bound not found" << std::endl;
  } else {
    std::cout << "upper_bound at position " << (up - v.begin()) << ", value is " << *up << std::endl;
  }
}

int main() {
  std::cout << "==================== normal ====================" << std::endl;
  normal();
  std::cout << "==================== abnormal ====================" << std::endl;
  abnormal();
  std::cout << "==================== custom_compare ====================" << std::endl;
  custom_compare();

  return 0;
}
