#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>
#include <unordered_set>

/**
 * 迭代器需要支持的操作：
 * 1.基本属性：
 *   - 支持拷贝构造和赋值操作
 *   - 支持自增操作：++a和a++，返回值为迭代器自身
 * 2.输入/输出迭代器：
 *   - 支持解引用操作： 
 *     - 输入迭代器：返回右值，不能修改容器中的元素
 *     - 输出迭代器：返回左值，可以修改容器中的元素
 *   - 支持比较操作：a == b和a != b
 * 3.前向迭代器：
 *   - 拥有输入/输出迭代器的所有特性
 * 4.双向迭代器：
 *   - 支持自减操作：--a和a--
 * 5.随机访问迭代器：
 *   - 支持加法和减法操作：a + n和a - n
 *   - 支持比较操作：a < b, a <= b, a > b, a >= b
 *   - 支持复合操作符号：a += n, a -= n
 *   - 支持下标操作：a[n]和a[-n]
 */

// template <class Category,              // iterator::iterator_category
//           class T,                     // iterator::value_type
//           class Distance = ptrdiff_t,  // iterator::difference_type
//           class Pointer = T*,          // iterator::pointer
//           class Reference = T&         // iterator::reference>
// class iterator;

/**
 * 注意：
 * 1.空迭代器不能被解引用，否则会报异常
 * 2.迭代器不一定支持所有的指针操作，需要根据迭代器的类型来判断。
 */

class MyIterator : public std::iterator<std::input_iterator_tag, int> {
  int* p;

 public:
  MyIterator(int* x) : p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator=(const MyIterator& mit) {
    p = mit.p;
    return *this;
  }
  MyIterator& operator++() {
    ++p;
    return *this;
  }
  MyIterator operator++(int) {
    MyIterator tmp(*this);
    operator++();
    return tmp;
  }
  bool operator==(const MyIterator& rhs) const { return p == rhs.p; }
  bool operator!=(const MyIterator& rhs) const { return p != rhs.p; }
  int& operator*() { return *p; }
};

void BasicIter() {
  int numbers[] = {1, 2, 3, 4, 5};
  MyIterator begin(numbers);
  MyIterator another_begin(begin);
  MyIterator end(numbers + 5);
  for (MyIterator it = another_begin; it != end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

/**
 * @brief: Input Iterators
 * 
 * @note 可以被解引用为右值
 */
void Input() {
  std::vector<int> nu;
  std::vector<int>::iterator it_nu = nu.begin();

  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = v.begin();
  std::cout << "begin == end? " << (it == v.end()) << std::endl;
  std::cout << "begin: " << *it << std::endl;
}

/**
 * @brief: Output Iterators
 * 
 * @note 可以被解引用为左值
 * 
 * @note 迭代器的解引用操作符返回一个左值引用，因此可以修改容器中的元素。
 */
void Output() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = v.begin();
  *it = 6;
  for (const auto& i : v) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  // 先使用it，再将it进行加1操作
  *it++ = 7;
  for (const auto& i : v) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << "it: " << *it << std::endl;

#if 0
  std::vector<int>::iterator it2;
  std::cout << "it2: " << *it2 << std::endl;
#endif
}

void Forward() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it;
  it = v.begin();
  std::cout << "it: " << *it << std::endl;

  std::vector<int>::iterator it2 = ++it;
  std::cout << "it2: " << *it2 << std::endl;

  it = it2;
  std::cout << "it: " << *it << std::endl;

  it++;
  std::cout << "it: " << *it << ", it2: " << *it2 << std::endl;
}

void Bidirectional() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = v.end();

  it--;
  std::cout << "it: " << *it << std::endl;
}

void Random() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = v.begin();

  std::vector<int>::iterator it2 = it + 2;
  std::cout << "it2: " << *it2 << std::endl;

  if (it < it2) {
    std::cout << "it < it2" << std::endl;
  } else {
    std::cout << "it >= it2" << std::endl;
  }

  it2 += 1;
  std::cout << "it2: " << *it2 << std::endl;

  std::cout << "it: " << it[2] << std::endl;
  std::cout << "it2: " << it2[-1] << std::endl;
}

void Traits() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = v.begin();

  if (std::is_same<std::vector<int>::iterator::value_type, int>::value) {
    std::cout << "std::vector<int>::iterator::value_type is int" << std::endl;
  }

  if (std::is_same<std::iterator_traits<std::vector<int>::iterator>::value_type, int>::value) {
    std::cout << "value_type is int" << std::endl;
  }
  if (std::is_same<std::iterator_traits<std::vector<int>::iterator>::iterator_category,
                   std::random_access_iterator_tag>::value) {
    std::cout << "iterator_category is random_access_iterator_tag" << std::endl;
  }
  if (std::is_same<std::iterator_traits<std::vector<int>::iterator>::difference_type,
                   std::ptrdiff_t>::value) {
    std::cout << "difference_type is ptrdiff_t" << std::endl;
  }
  if (std::is_same<std::iterator_traits<std::vector<int>::iterator>::pointer, int*>::value) {
    std::cout << "pointer is int*" << std::endl;
  }
  if (std::is_same<std::iterator_traits<std::vector<int>::iterator>::reference, int&>::value) {
    std::cout << "reference is int&" << std::endl;
  }
}

void iterator_operations() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  int arr[] = {1, 2, 3, 4, 5};
  int(&arrd)[5] = arr;
  std::vector<int>::iterator it = v.begin();

  std::advance(it, 2);
  std::cout << "it: " << *it << std::endl;

  std::vector<int>::iterator::difference_type diff = std::distance(v.begin(), it);
  std::cout << "diff: " << diff << std::endl;
  diff = std::distance(it, v.begin());
  std::cout << "diff: " << diff << std::endl;

  std::cout << "begin: " << *(std::begin(v)) << std::endl;
  std::cout << "begin: " << *std::begin<std::vector<int>>(v) << std::endl;
  std::cout << "begin: " << *(std::begin<int>(arrd)) << std::endl;

  std::cout << "previous: " << *std::prev(v.end()) << std::endl;
  std::cout << "previous 2: " << *std::prev(v.end(), 2) << std::endl;

  std::cout << "next: " << *std::next(v.begin()) << std::endl;
  std::cout << "next 2: " << *std::next(v.begin(), 2) << std::endl;
}
/**
 * @brief: Pre-Iterator
 * 
 * @note 自定义实现一个后插迭代器，类似于std::back_insert_iterator。
 */
template <class Container>
class my_back_insert_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void> {
 protected:
  Container* container;

 public:
  typedef Container container_type;
  explicit my_back_insert_iterator(Container& x) : container(&x) {}
  my_back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
    container->push_back(value);
    return *this;
  }
  my_back_insert_iterator<Container>& operator=(typename Container::value_type&& value) {
    container->push_back(std::move(value));
    return *this;
  }
  my_back_insert_iterator<Container>& operator*() { return *this; }
  my_back_insert_iterator<Container>& operator++() { return *this; }
  my_back_insert_iterator<Container> operator++(int) { return *this; }
};

void PreIterator() {
  std::vector<int> v = {1, 2, 3, 4, 5};

  /**
   * template <class Container>
   * class back_insert_iterator;
   * 
   * @note 一种特殊的output迭代器，它将元素插入到容器的末尾。container必须支持push_back()方法。
   */
  std::back_insert_iterator<std::vector<int>> back_it(v);
  back_it = 6;  // 将6插入到v的末尾
  back_it = 7;  // 将7插入到v的末尾

  std::back_insert_iterator<std::vector<int>> my_back_it = std::back_inserter(v);
  my_back_it = 8;  // 将8插入到v的末尾
  my_back_it = 9;  // 将9插入到v的末尾

  for(const auto& i : v) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::cout << "--------------------------------BasicIter--------------------------------" << std::endl;
  BasicIter();
  std::cout << "--------------------------------Input--------------------------------" << std::endl;
  Input();
  std::cout << "--------------------------------Output--------------------------------" << std::endl;
  Output();
  std::cout << "--------------------------------Forward--------------------------------" << std::endl;
  Forward();
  std::cout << "--------------------------------Bidirectional--------------------------------" << std::endl;
  Bidirectional();
  std::cout << "--------------------------------Random--------------------------------" << std::endl;
  Random();
  std::cout << "--------------------------------Traits--------------------------------" << std::endl;
  Traits();
  std::cout << "--------------------------------iterator_operations--------------------------------" << std::endl;
  iterator_operations();
  std::cout << "--------------------------------PreIterator--------------------------------" << std::endl;
  PreIterator();
  return 0;
}