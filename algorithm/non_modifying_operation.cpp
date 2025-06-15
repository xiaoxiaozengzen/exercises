#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <functional>

/**
 * @brief: all_of() checks if unary predicate pred returns true for all elements in the range [first, last).
 */
void all_of() {
#if 0
template <
    class InputIterator,
    class UnaryPredicate>  
bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {3,5,7,11,13,17,19,23};

  if ( std::all_of(foo.begin(), foo.end(), [](int i){return i%2;}) ) {
    std::cout << "All the elements are odd numbers.\n";
  }
}

/**
 * @brief: any_of() checks if unary predicate pred returns true for at least one element in the range [first, last).
 */
void any_of() {
#if 0
template <class InputIterator, class UnaryPredicate>  
bool any_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {0,0,0,0,1,0,0,0};

  if ( std::any_of(foo.begin(), foo.end(), [](int i){return i;}) ) {
    std::cout << "There is at least one element different from zero.\n";
  }
}

/**
 * @brief: none_of() checks if unary predicate pred returns true for no elements in the range [first, last).
 */
void none_of() {
#if 0
template <class InputIterator, class UnaryPredicate>
bool none_of (InputIterator first, InputIterator last, UnaryPredicate pred);
#endif

  std::array<int,8> foo = {0,0,0,0,0,0,0,0};

  if ( std::none_of(foo.begin(), foo.end(), [](int i){return i;}) ) {
    std::cout << "There is no element different from zero.\n";
  }
}

/**
 * @brief: for_each() applies function fn to each of the elements in the range [first, last).
 */
void for_each() {
#if 0
  template <class InputIterator, class Function>
  Function for_each (InputIterator first, InputIterator last, Function fn);
#endif

  std::vector<int> foo = {10,20,30,40,50};

  std::function<void(int&)> fun = std::for_each(foo.begin(), foo.end(), [](int &n){ n++; });

  std::cout << "foo contains:";
  for (int &x : foo) std::cout << ' ' << x;
  std::cout << '\n';

  int a = 10;
  fun(a);
  std::cout << "a = " << a << std::endl;
}

/**
 * template <class InputIterator, class T>
 * InputIterator find (InputIterator first, InputIterator last, const T& val);
 * 
 * @brief 返回指向第一个等于 val 的元素的迭代器，如果没有找到，则返回 last。
 */
void find_test() {
  std::vector<int> foo = {10,20,30,40,50};
  std::vector<int>::iterator it = std::find(foo.begin(), foo.end(), 30);
  if (it != foo.end()) {
    std::cout << "Element found: " << *it << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }
}

/**
 * template <class InputIterator, class UnaryPredicate>
 * InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
 * 
 * @brief 返回指向第一个满足条件的元素的迭代器，如果没有找到，则返回 last。
 */
void find_if_test() {
  std::vector<int> foo = {10,20,30,40,50};
  std::vector<int>::iterator it = std::find_if(foo.begin(), foo.end(), [](int i){ return i > 30; });
  if (it != foo.end()) {
    std::cout << "Element found: " << *it << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }
}

/**
 * template <class ForwardIterator1, class ForwardIterator2>
 * ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2);
 * 
 * template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
 * ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred);
 * 
 * @brief 在[first1, last1)范围内查找[first2, last2)这个子序列的最后一次出现，并返回指向该子序列的第一个元素的迭代器。
 */
void find_end_test() {
  std::vector<int> foo1 = {10,20,30,40,50,60,70,80,90};
  std::vector<int> foo2 = {30,40,50};
  std::vector<int>::iterator it = std::find_end(foo1.begin(), foo1.end(), foo2.begin(), foo2.end());
  if (it != foo1.end()) {
    std::cout << "Last occurrence of the subsequence found at position: " << (it - foo1.begin()) << std::endl;
    std::cout << "Subsequence starts with: " << *it << std::endl;
  } else {
    std::cout << "Subsequence not found" << std::endl;
  }
}

/**
 * template <class InputIterator, class ForwardIterator>
 * InputIterator find_first_of (InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2);
 * 
 * template <class InputIterator, class ForwardIterator, class BinaryPredicate>
 * InputIterator find_first_of (InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate pred);
 * 
 * @brief 在[first1, last1)范围内查找是否有元素等于[first2, last2)范围内的任意一个元素，并返回第一个匹配元素的迭代器，如果没有找到，则返回 last1。
 */
void find_first_of_test() {
  std::vector<int> foo1 = {10,20,30,40,50}; 
  std::vector<int> foo2 = {30,40,50,60,70};
  std::vector<int>::iterator it = std::find_first_of(foo1.begin(), foo1.end(), foo2.begin(), foo2.end());
  if (it != foo1.end()) {
    std::cout << "First matching element found: " << *it << std::endl;
  } else {
    std::cout << "No matching element found" << std::endl;
  }
}

/**
 * template <class ForwardIterator>
 * ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last);
 * 
 * template <class ForwardIterator, class BinaryPredicate>
 * ForwardIterator adjacent_find (ForwardIterator first, ForwardIterator last, BinaryPredicate pred);
 * 
 * @brief 查找容器中第一对相邻且相等得元素，并返回第一个元素的迭代器，若没有找到，则返回 last。
 */
void adjacent_find_text() {
  std::vector<int> foo = {10,15,20,30,40,50,50};
  std::vector<int>::iterator it = std::adjacent_find(foo.begin(), foo.end());
  if (it != foo.end()) {
    std::cout << "Element found first: " << *it << std::endl;
    std::cout << "Element found second: " << *(it + 1) << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }

  std::vector<int>::iterator it2 = std::adjacent_find(foo.begin(), foo.end(), [](int a, int b) { return std::abs(a-b) <= 5; });
  if (it2 != foo.end()) {
    std::cout << "Element found first: " << *it2 << std::endl;
    std::cout << "Element found second: " << *(it2 + 1) << std::endl;
  } else {
    std::cout << "Element not found" << std::endl;
  }
}

/**
 * template <class InputIterator1, class InputIterator2>
 * pair<InputIterator1, InputIterator2> mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2);
 * 
 * template <class InputIterator1, class InputIterator2, class BinaryPredicate>
 * pair<InputIterator1, InputIterator2>    mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred);
 * 
 * @brief 比较两个集合以发现值是否不匹配。该函数返回两个不匹配的集合的第一个元素。
 * 
 * @return 
 *  - 如果函数发现一对不匹配的元素，则它将返回第一对这样的元素，每个集合中都有一个。
 *  - 如果没有找到不相等的元素，则返回last1和first2+(last1-first1)。
 * 
 */
void mismatch_test() {
#if 0
  // 等价如下
  template <class InputIterator1, class InputIterator2>
    pair<InputIterator1, InputIterator2>
      mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
  {
    while ( (first1!=last1) && (*first1==*first2) )  // or: pred(*first1,*first2), for version 2
    { ++first1; ++first2; }
    return std::make_pair(first1,first2);
  }
#endif

  // 大小一致
  std::vector<int> foo1 = {10,20,30,40,50};
  int foo2[5] = {10,20,30,40,60};
  std::pair<std::vector<int>::iterator, int*> it = std::mismatch(foo1.begin(), foo1.end(), foo2);
  std::cout << "it->first: " << *(it.first) << ", diff: " << (it.first - foo1.begin()) << std::endl;
  std::cout << "it->second: " << *(it.second) << ", diff: " << (it.second - foo2) << std::endl;

  // 没有不匹配的
  std::vector<int> foo3 = {10,20,30,40,50};
  int foo4[5] = {10,20,30,40,50};
  std::pair<std::vector<int>::iterator, int*> it2 = std::mismatch(foo3.begin(), foo3.end(), foo4);
  if(it2.first == foo3.end()) {
    std::cout << "foo3 is same foo4" << std::endl;
    std::cout << "it2->first: " << *(it2.first) << " diff: " << (it2.first - foo3.begin()) << std::endl;
    std::cout << "it2->second: " << *(it2.second) << " diff: " << (it2.second - foo4) << std::endl;
  } else {
    std::cout << "it2->first: " << *(it2.first) << " diff: " << (it2.first - foo3.begin()) << std::endl;
    std::cout << "it2->second: " << *(it2.second) << " diff: " << (it2.second - foo4) << std::endl;
  }

  // 大小不一致
  std::vector<int> foo5 = {10,20,30,40,50};
  int foo6[3] = {10,20,30};
  std::pair<std::vector<int>::iterator, int*> it3 = std::mismatch(foo5.begin(), foo5.end(), foo6);
  if(it3.first == foo5.end()) {
    std::cout << "foo5 is same foo6" << std::endl;
    std::cout << "it3->first: " << *(it3.first) << " diff: " << (it3.first - foo5.begin()) << std::endl;
    std::cout << "it3->second: " << *(it3.second) << " diff: " << (it3.second - foo6) << std::endl;
  } else {
    std::cout << "it3->first: " << *(it3.first) << " diff: " << (it3.first - foo5.begin()) << std::endl;
    std::cout << "it3->second: " << *(it3.second) << " diff: " << (it3.second - foo6) << std::endl;
  }

  // none match
  std::vector<int> foo7 = {11,20,30,40,50};
  int foo8[5] = {10,22,33,44,55};
  std::pair<std::vector<int>::iterator, int*> it4 = std::mismatch(foo7.begin(), foo7.end(), foo8);
  if(it4.first == foo7.end()) {
    std::cout << "foo7 is same foo8" << std::endl;
    std::cout << "it4->first: " << *(it4.first) << " diff: " << (it4.first - foo7.begin()) << std::endl;
    std::cout << "it4->second: " << *(it4.second) << " diff: " << (it4.second - foo8) << std::endl;
  } else {
    std::cout << "it4->first: " << *(it4.first) << " diff: " << (it4.first - foo7.begin()) << std::endl;
    std::cout << "it4->second: " << *(it4.second) << " diff: " << (it4.second - foo8) << std::endl;
  }
}

/**
 * template <class InputIterator, class T>
 * typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& val);
 * 
 * template <class InputIterator, class UnaryPredicate>
 * typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, UnaryPredicate pred);
 */
void count_test() {
  // count() 和 count_if() 函数用于计算范围内满足特定条件的元素数量。
  std::vector<int> foo = {10,20,50,30,40,50,60,70,80,90};
  int count = std::count(foo.begin(), foo.end(), 50);
  std::cout << "Count of 50: " << count << std::endl;

  int count_if = std::count_if(foo.begin(), foo.end(), [](int i){ return i > 50; });
  std::cout << "Count of elements greater than 50: " << count_if << std::endl;
}

/**
 * template <class InputIterator1, class InputIterator2>
 * bool is_permutation (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2， InputIterator2 last2);
 * 
 * template <class InputIterator1, class InputIterator2, class BinaryPredicate>
 * bool is_permutation (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred);
 * 
 * @brief 检查[first1, last1)范围内的元素是否和从first2开始的同长度区间中元素完全一样(顺序可以不同)。
 * @note 如果两个范围的元素数量不同，则返回false。
 */
void is_permutation_test() {
  std::vector<int> foo1 = {10,20,30,40,50};
  std::vector<int> foo2 = {30,20,10,50,40};
  std::vector<int> foo3 = {10,20,30,40,50,60};
  bool is_perm1 = std::is_permutation(foo1.begin(), foo1.end(), foo2.begin(), foo2.end());
  bool is_perm2 = std::is_permutation(foo1.begin(), foo1.end(), foo3.begin(), foo3.end());
  std::cout << "foo1 and foo2 are permutations: " << (is_perm1 ? "true" : "false") << std::endl;
  std::cout << "foo1 and foo3 are permutations: " << (is_perm2 ? "true" : "false") << std::endl;
}

/**
 * template <class ForwardIterator1, class ForwardIterator2>
 * ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2);
 * 
 * @brief 在[first1, last1)范围内查找[first2, last2)这个子序列第一次出现的位置，并返回指向该子序列的第一个元素的迭代器。
 */
void search_test() {
  std::vector<int> foo1 = {10,20,30,40,50,60,70,80,90};
  std::vector<int> foo2 = {30,40,50};
  std::vector<int>::iterator it = std::search(foo1.begin(), foo1.end(), foo2.begin(), foo2.end());
  if (it != foo1.end()) {
    std::cout << "Subsequence found at position: " << (it - foo1.begin()) << std::endl;
    std::cout << "Subsequence starts with: " << *it << std::endl;
  } else {
    std::cout << "Subsequence not found" << std::endl;
  }
}

int main() {
  std::cout << "==================== all_of ====================" << std::endl;
  all_of();
  std::cout << "==================== any_of ====================" << std::endl;
  any_of();
  std::cout << "==================== none_of ====================" << std::endl;
  none_of();
  std::cout << "==================== for_each ====================" << std::endl;
  for_each();
  std::cout << "==================== find_test ====================" << std::endl;
  find_test();
  std::cout << "==================== find_if_test ====================" << std::endl;
  find_if_test();
  std::cout << "==================== find_end_test ====================" << std::endl;
  find_end_test();
  std::cout << "==================== find_first_of_test ====================" << std::endl;
  find_first_of_test();
  std::cout << "==================== adjacent_find_text ====================" << std::endl;
  adjacent_find_text();
  std::cout << "==================== mismatch_test ====================" << std::endl;
  mismatch_test();
  std::cout << "==================== count_test ====================" << std::endl;
  count_test();
  std::cout << "==================== is_permutation_test ====================" << std::endl;
  is_permutation_test();
  std::cout << "==================== search_test ====================" << std::endl;
  search_test();
  return 0;
}