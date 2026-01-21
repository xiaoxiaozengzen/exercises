#include <iostream>
#include <algorithm>
#include <vector>

/**
 * template <class RandomAccessIterator>
 * void sort (RandomAccessIterator first, RandomAccessIterator last);
 * 
 * template <class RandomAccessIterator, class Compare>
 * void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
 *
 * @note 按照升序排序范围 [first, last) 之间的元素。默认使用 operator< 进行比较。
 * @note 如果提供了比较函数 comp，则使用该函数进行排序。比较函数应该接受两个参数，并返回一个布尔值，表示第一个参数是否应排在第二
 * @note 相等的元素在排序后相对位置会变化（不稳定排序）。
 */

bool myfunction (int i,int j) {
  std::cout << "comparing " << i << " and " << j << std::endl;
  return (i<j); 
}

struct myclass {
  bool operator() (int i,int j) { 
    std::cout << "comparing " << i << " and " << j << std::endl;
    return (i<j);
  }
} myobject;

void sort_exmaple() {
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

  // using default comparison (operator <):
  std::sort(myvector.begin(), myvector.end());
  std::cout << "myvector contains: ";
  for(auto i : myvector) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  // using object as comp
  std::sort(myvector.begin(), myvector.end(), myobject);
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

/**
 * template <class RandomAccessIterator>
 * void stable_sort (RandomAccessIterator first, RandomAccessIterator last);
 * template <class RandomAccessIterator, class Compare>
 * void stable_sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
 * @note 按照升序排序范围 [first, last) 之间的元素。默认使用 operator< 进行比较。
 * @note 如果提供了比较函数 comp，则使用该函数进行排序。比较函数应该接受两个参数，并返回一个布尔值，表示第一个参数是否应排在第二
 * @note 相等的元素在排序后相对位置保持不变（稳定排序）。
 *
 */
void stable_sort_example() {

  // 可以通过int转换来比较double值。例如：1.xx都会被转换成1，认为是一样的值，
  // 可以方便查看排序后1.xx的相对位置是否保持不变
  auto compare_as_ints = [](double a, double b) {
    return int(a) < int(b);
  };

  double mydoubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};

  std::vector<double> myvector;

  myvector.assign(mydoubles,mydoubles+8);

  std::cout << "using default comparison:";
  std::stable_sort (myvector.begin(), myvector.end());
  for (std::vector<double>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  myvector.assign(mydoubles,mydoubles+8);

  std::cout << "using 'compare_as_ints' :";
  std::stable_sort (myvector.begin(), myvector.end(), compare_as_ints);
  for (std::vector<double>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

int main() {
  std::cout << "========== Sort Example ==========" << std::endl;
  sort_exmaple();
  std::cout << "======= Stable Sort Example ======" << std::endl;
  stable_sort_example();

  return 0;  
}
