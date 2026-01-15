#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream>
#include <fstream>

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
 * 
 * @note 注意：
 *   1.并不是所有的迭代器都支持所有的操作，需要根据迭代器的类型来判断。
 *   2.迭代器的类型可以通过std::iterator_traits来获取
 *   3.空迭代器不能被解引用，否则会报异常
 */

/**
 * template <class Category,              // iterator::iterator_category
 *           class T,                     // iterator::value_type
 *           class Distance = ptrdiff_t,  // iterator::difference_type
 *           class Pointer = T*,          // iterator::pointer
 *           class Reference = T&         // iterator::reference>
 * class iterator;
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

  // 迭代器的默认构造函数
  // 不能和bool/nullptr进行比较
  std::vector<int>::iterator it_default;
  std::vector<int>::iterator it_default2 = std::vector<int>::iterator();
  std::vector<int>::iterator it_default3{};

  it_default = v.begin();
  std::cout << "it_default after assignment: " << *it_default << std::endl;
  it_default2 = v.begin();
  std::cout << "it_default2 after assignment: " << *it_default2 << std::endl;
  it_default3 = v.begin();
  std::cout << "it_default3 after assignment: " << *it_default3 << std::endl;

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

void MyBackIterator() {
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

  std::vector<int> v2 = {10, 11, 12};
  my_back_insert_iterator<std::vector<int>> my_back_it2(v2);
  my_back_it2 = 13;  // 将13插入到v2的
  for(const auto& i : v2) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

/**
 * template <class charT, class traits = char_traits<charT> >
 * class istreambuf_iterator;
 * 
 * @note 一种输入迭代器，用于从stream buffer中读取字符。它读取的是流缓冲区中的字符，而不是流中的字符。
 * @note 只能用于输入流，不能用于输出流。
 * @note 不能用于标准输入流cin，因为cin的缓冲区是不可读的。
 * @note 该迭代器有一种end-of-range迭代器，等价于访问到stream的末尾
 */
void istreambuf_iterator_test() {
  // 1. construct
  std::istreambuf_iterator<char> eos;                    // default construct，等价于end-of-range iterator
  std::istreambuf_iterator<char> it1 (std::cin.rdbuf()); // 基于basic_streambuf或者basic_istream构造
  std::string str = "Hello, World!";
  std::stringbuf sbuf(str);
  std::istreambuf_iterator<char> it2 (&sbuf);            // 基于basic_streambuf或者basic_istream构造
  std::string file = "/mnt/workspace/cgz_workspace/Exercise/exercises/container/iterator_text.txt";
  std::ifstream fin(file);
  if (!fin) {
    std::cerr << "Cannot open the input file: " << file << std::endl;
    return;
  }
  std::istreambuf_iterator<char> it3 (fin.rdbuf());       // 基于ifstream的streambuf构造
  // 基于ifstream构造也行，等价于：istreambuf_iterator(istream_type& s) throw(): sbuf_(s.rdbuf()) { }
  // std::istreambuf_iterator<char> it4 (fin);              
  std::vector<char> vec3(it3, eos);
  std::cout << "vec3: ";
  for(const auto& c : vec3) {
    std::cout << c;
  }
  std::cout << std::endl;

  // 2. member functions
  std::string mystring;
  std::cout << "Please, enter your name: ";
  while (it1 != eos && *it1 != '\n'){
    std::cout << "current: " <<*it1 << std::endl;
    mystring+=*it1;
    it1++;
  }
  
  std::cout << "Your name is " << mystring << ".\n";
  while(it2 != eos){
    std::cout << "it2: " << *it2 << std::endl;
    ++it2;
  }
}

/**
 * template <class T,
 *           class charT=char,
 *           class traits=char_traits<charT>,
 *           class Distance = ptrdiff_t>
 * class istream_iterator;
 * 
 * @brief 一种输入迭代器，用于从输入流(例如std::cin)中读取数据。它读取的是流中的数据，而不是流缓冲区中的数据。
 * @note 只能用于输入流，不能用于输出流。
 * @note T是读取的数据类型，charT是字符类型(跟basic_stream的第一个模板参数类型一致)
 */
void istream_iterator_test() {
  // 1. member types
  if(std::is_same<std::istream_iterator<int>::value_type, int>::value) {
    std::cout << "value_type is int" << std::endl;
  }
  if(std::is_same<std::istream_iterator<int>::char_type, char>::value) {
    std::cout << "char_type is char" << std::endl;
  }
  if(std::is_same<std::istream_iterator<int>::pointer, const int*>::value) {
    std::cout << "pointer is int*" << std::endl;
  }
  if(std::is_same<std::istream_iterator<int>::reference, const int&>::value) {
    std::cout << "reference is int&" << std::endl;
  }

  // 2. construct
  std::istream_iterator<int> eos;                    // default construct，等价于end-of-stream iterator
  std::istream_iterator<int> it (std::cin);         // 基于basic_istream对象构造

  // 3. member functions
  // 3.1 reference operator*() const;
  // 3.2 istream_iterator& operator++(); // 前置自增
  // 3.3 istream_iterator operator++(int); // 后置自增
  // 3.4 pointer operator->() const;
  double value1, value2;
  std::cout << "Please, insert two values: ";
  std::istream_iterator<double> eos1;
  std::istream_iterator<double> it1 (std::cin);
  if (it1 != eos1) {
    value1=*it1;
  }
  ++it1;
  if (it1 != eos1) {
    value2=*it1;
  }
  std::cout << value1 << "*" << value2 << "=" << (value1*value2) << '\n';

  std::string file = "/mnt/workspace/cgz_workspace/Exercise/exercises/container/iterator_text.txt";
  std::ifstream fin(file);
  if (!fin) {
    std::cerr << "Cannot open the input file: " << file << std::endl;
    return;
  }
  std::istream_iterator<char> eos2;          // default construct，等价于end-of-stream iterator
  std::istream_iterator<char> it2 (fin);     // 基于basic_istream对象构造
  if(it2 != eos2) {
    std::cout << *it2 << std::endl;
  }
  
  std::istream_iterator<std::string> eos3;
  std::istream_iterator<std::string> it3 (fin);
  if(it3 != eos3) {
    std::cout << *it3 << std::endl;
  }
  std::cout << "it3.size(): " << it3->size() << std::endl;
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
  std::cout << "--------------------------------MyBackIterator--------------------------------" << std::endl;
  MyBackIterator();
  std::cout << "--------------------------------istreambuf_iterator_test--------------------------------" << std::endl;
  istreambuf_iterator_test();
  std::cout << "--------------------------------istream_iterator_test--------------------------------" << std::endl;
  istream_iterator_test();

  return 0;
}