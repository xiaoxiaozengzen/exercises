#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <array>

/**
 * std::string跟std::string_view的区别：
 * 1. 是否拥有数据：
 *    std::string是一个拥有字符串数据的类，
 *    std::string_view只是一个指向字符串数据的视图。
 * 2. 内存管理：
 *    std::string需要管理内存，可能会进行动态分配和释放，
 *    std::string_view不需要管理内存，只是一个轻量级的对象。
 */

#if 0
template<
    class CharT,
    class Traits = std::char_traits<CharT>
> class basic_string_view;
#endif

void MemType() {
  if(std::is_same<std::string_view::value_type, char>::value) {
    std::cout << "std::string_view::value_type is char" << std::endl;
  } else {
    std::cout << "std::string_view::value_type is not char" << std::endl;
  }
}

void ConFun() {
  std::string_view str_v1;
  std::string_view str_v2("Hello");
  std::string_view str_v3("Hello", 3);
  std::cout << "str_v1: " << str_v1 << std::endl;
  std::cout << "str_v2: " << str_v2 << std::endl;
  std::cout << "str_v3: " << str_v3 << std::endl;
}

void MemFun() {
  char arr[] = "Hello1234567890";
  std::string_view str_v(arr);
  std::cout << "str_v: " << str_v << std::endl;

  // 改变str_v的偏移位置，不影响arr
  str_v.remove_prefix(2);
  std::cout << "str_v: " << str_v << std::endl;
  std::cout << "arr: " << arr << std::endl;
}

/**
 * SSO（Small String Optimization）小字符串优化(std::string实现的一个重要特性)：
 *  1. 当字符串长度小于等于15时，优化使用栈空间存储字符串数据，避免动态分配内存，提高性能。
 *  2. 当字符串长度大于15时，使用堆空间存储字符串数据，动态分配内存。
 *
 * 为什么要有SSO：
 *  1.高频次小对象的创建和销毁会导致频繁的内存分配和释放，增加系统开销。
 *  2.缓存命中率低，频繁的内存分配和释放会导致内存碎片化，降低性能。
 *  3.内存碎片化会导致内存使用效率降低，增加内存占用。
 */
void Test() {
  std::cout << "-------------------- Test1 --------------------" << std::endl;
  const char* cs = "1234567";
  std::string s(cs);
  std::string_view sv(cs);

  // cs address: 0x55f2c002702d
  std::cout << "cs address: " << (void*)cs << std::endl;
  // s address: 当长度小于16时，在栈上存储字符串数据，地址和cs不同；当长度大于15时，在堆上存储字符串数据，地址和cs不同。
  std::cout << "s address: " << (void*)s.data() << std::endl;
  // sv address: 0x55f2c002702d,和cs地址相同，因为sv只是一个指向字符串数据的视图，不拥有数据。
  std::cout << "sv address: " << (void*)sv.data() << std::endl;

  char* first = static_cast<char*>(s.data());
  std::cout << "first: " << *first << std::endl;
  char* second = first + 1;
  std::cout << "second: " << *second << std::endl;

  std::cout << "-------------------- Test2 --------------------" << std::endl;
  char arr[] = "Hello111111111111111111111111111111";
  std::string s1(arr);
  std::string_view sv1(arr);
  std::cout << "arr[0]: " << arr[0]
            << ", s1[0]: " << s1[0]
            << ", sv1[0]: " << sv1[0]
            << std::endl;
  // 修改arr[0]，s1[0]不变，sv1[0]改变，因为s1拥有数据，sv1只是一个视图。
  arr[0] = 'h';
  std::cout << "arr[0]: " << arr[0]
            << ", s1[0]: " << s1[0]
            << ", sv1[0]: " << sv1[0]
            << std::endl;

  std::cout << "-------------------- Test3 --------------------" << std::endl;
#if 0
  // 会报错，因为sv1[0]返回的是const char&，不能修改。
  sv1[0] = 'i';
  std::cout << "arr[0]: " << arr[0]
            << ", s1[0]: " << s1[0]
            << ", sv1[0]: " << sv1[0]
            << std::endl;
#endif
}

int main() {
  std::cout << "====================== MemType ======================" << std::endl;
  MemType();
  std::cout << "====================== ConFun ======================" << std::endl;
  ConFun();
  std::cout << "====================== MemFun ======================" << std::endl;
  MemFun();
  std::cout << "====================== Test ======================" << std::endl;
  Test();
  return 0;
}