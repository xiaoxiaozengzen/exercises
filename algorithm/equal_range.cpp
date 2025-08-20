#include <iostream>
#include <vector>
#include <algorithm>

/**
 * template <class ForwardIterator, class T>
 * std::pair<ForwardIterator, ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);
 * 
 * @brief 在已排序的范围内查找与给定值相等的元素范围
 * 
 * @param first 范围的起始迭代器
 * @param last 范围的结束迭代器
 * @param val 要查找的值
 * @return
 *    如果val不等于范围内的任何元素，则子范围的长度是0，且两个迭代器都指向第一个大于val的元素。
 *    如果val等于范围内的某些元素，则第一个迭代器执行lower_bound返回的元素，第二个迭代器执行upper_bound返回的元素。
 */

/**
 * template <class ForwardIterator, class T, class Compare>
 * std::pair<ForwardIterator, ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
 */

bool mygreater (int i,int j) { return (i>j); }

int main() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);                         // 10 20 30 30 20 10 10 20
  std::pair<std::vector<int>::iterator,std::vector<int>::iterator> bounds;

  // using default comparison:
  std::sort (v.begin(), v.end());                              // 10 10 10 20 20 20 30 30
  bounds=std::equal_range(v.begin(), v.end(), 20);             //          ^        ^
  std::cout << "bounds at positions " << (bounds.first - v.begin());
  std::cout << " and " << (bounds.second - v.begin()) << '\n';
  if(bounds.first != v.end()) {
    std::cout << "bounds.first: " << *bounds.first << std::endl;
  }
  if(bounds.second != v.end()) {
    std::cout << "bounds.second: " << *bounds.second << std::endl;
  }

  // using "mygreater" as comp:
  std::sort (v.begin(), v.end(), mygreater);                   // 30 30 20 20 20 10 10 10
  bounds=std::equal_range (v.begin(), v.end(), 20, mygreater); //       ^        ^
  std::cout << "bounds at positions " << (bounds.first - v.begin());
  std::cout << " and " << (bounds.second - v.begin()) << '\n';

  return 0;
}
