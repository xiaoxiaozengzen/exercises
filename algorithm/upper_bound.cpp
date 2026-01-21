#include <iostream>
#include <algorithm>
#include <vector>

/**
 * template <class ForwardIterator, class T>
 * ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);
 * 
 * template <class ForwardIterator, class T, class Compare>
 * ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
 * 
 * @brief 在[first, last)范围内查找第一个大于val的元素位置，并返回指向该元素的迭代器。
 *        第一个版本默认使用operator<进行比较，第二个版本使用用户自定义的比较函数comp。
 *        容器中的元素也必须提前按照operator<或comp进行排序，否则结果未定义。
 */

/**
 * Compare comp
 * @note 接收两个参数，返回bool值
 * @param first 容器的迭代器指向的元素
 * @param second 用于比较的值val
 * @return 如果first小于second，返回true；否则返回false。等价于 operator<
 */

class Data {
 public:
  explicit Data(int v) : value(v) {}
  int value;

  bool operator<(const Data& other) const {
    return value < other.value;
  }

  friend std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << data.value;
    return os;
  }

  friend bool operator<(const Data& lhs, const int& rhs) {
    return lhs.value < rhs;
  }

  friend bool operator<(const int& lhs, const Data& rhs) {
    return lhs < rhs.value;
  }
};

void normal() {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

  std::sort(v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  std::vector<int>::iterator low,up;
  low = std::lower_bound (v.begin(), v.end(), 20); // 返回第一个不小于20的元素位置
  up = std::upper_bound (v.begin(), v.end(), 20); // 返回第一个大于20的元素位置

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
  low = std::lower_bound (v.begin(), v.end(), 9); // 返回第一个不小于9的元素位置
  low2 =std::lower_bound (v.begin(), v.end(), 31); // 返回第一个不小于31的元素位置
  up = std::upper_bound (v.begin(), v.end(), 31); // 返回第一个大于31的元素位置

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
  bool operator() (const Data& first, const int& second) {
    std::cout << "first: " << first << ", second: " << second << std::endl;
    return (first < second);
  }
};

void custom_compare() {
  std::vector<Data> vec;
  vec.reserve(10);
  vec.emplace_back(10);
  vec.emplace_back(20);
  vec.emplace_back(30);
  vec.emplace_back(20);
  vec.emplace_back(10);
  vec.emplace_back(30);
  vec.emplace_back(10);
  vec.emplace_back(40);
  vec.emplace_back(50);
  vec.emplace_back(20);

  std::sort(vec.begin(), vec.end()); // 使用 Data 类的 operator< 进行排序
  std::cout << "Sorted vector: ";
  for(const auto& item : vec) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  // 查找第一个大于 30 的元素位置
  std::vector<Data>::iterator low;
  low = std::lower_bound(vec.begin(), vec.end(), Data(30)); // 查找第一个不小于 30 的元素位置
  if (low != vec.end()) {
    std::cout << "lower_bound at position " << (low - vec.begin()) << ", value is " << (*low) << std::endl;
  } else {
    std::cout << "lower_bound not found" << std::endl;
  }

  // 使用int类型
  std::vector<Data>::iterator low2;
  low2 = std::lower_bound(vec.begin(), vec.end(), 20); // 查找第一个不小于 20 的元素位置
  if (low2 != vec.end()) {
    std::cout << "lower_bound at position " << (low2 - vec.begin()) << ", value is " << (*low2) << std::endl;
  } else {
    std::cout << "lower_bound not found" << std::endl;
  }

  // 使用自定义比较函数 MyLess 查找第一个不小于 20 的元素位置
  std::vector<Data>::iterator low3;
  low3 = std::lower_bound(vec.begin(), vec.end(), 20, MyLess());
  if (low3 != vec.end()) {
    std::cout << "lower_bound with custom compare at position " << (low3 - vec.begin()) << ", value is " << (*low3) << std::endl;
  } else {
    std::cout << "lower_bound with custom compare not found" << std::endl;
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
