#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <array>

// std::string_view记录了对应的字符串指针和偏移位置，无需管理内存，
// 相对std::string拥有一份字符串拷贝，如字符串查找和拷贝，效率更高。

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

void Test() {
  std::cout << "====================== Test1 ======================" << std::endl;
  const char* str = "Hello111111111111111111111111111111";
  std::string s(str);
  std::string_view sv(str);

  // str address: 0x55f2c002702d
  std::cout << "str address: " << (void*)str << std::endl;
  // s address: 当长度小于16时，开辟新的内存，否则指向str
  std::cout << "s address: " << (void*)s.data() << std::endl;
  // sv address: 0x55f2c002702d
  std::cout << "sv address: " << (void*)sv.data() << std::endl;

  char* single = static_cast<char*>(s.data());
  std::cout << "single: " << *single << std::endl;

  std::cout << "====================== Test2 ======================" << std::endl;
  char arr[] = "Hello111111111111111111111111111111";
  std::string s1(arr);
  std::string_view sv1(arr);
  std::cout << "arr address: " << (void*)arr
            << ", s1 address: " << (void*)s1.data()
            << ", sv1 address: " << (void*)sv1.data()
            << std::endl;
  // 发现s1的地址和arr的地址不一样，说明s1开辟了新的内存。难道是因为arr不是const char*?
  // 但是sv1的地址和arr的地址一样，说明sv1没有开辟新的内存。
  
  std::cout << "====================== Test3 ======================" << std::endl;
  std::cout << "arr[0]: " << arr[0]
            << ", s1[0]: " << s1[0]
            << ", sv1[0]: " << sv1[0]
            << std::endl;
  arr[0] = 'h';
  std::cout << "arr[0]: " << arr[0]
            << ", s1[0]: " << s1[0]
            << ", sv1[0]: " << sv1[0]
            << std::endl;
  // 发现arr的第一个元素改变了，s1的第一个元素没有变，但是sv1的第一个元素变了。
  // 看起来string_view适用于原字符串不变的情况，如果原字符串改变了，string_view也会改变。

  std::cout << "====================== Test4 ======================" << std::endl;
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