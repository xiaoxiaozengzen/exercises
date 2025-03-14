/**
 * char_traits提供了一些操作字符的函数，以及体现字符的属性
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstddef>
#include <cctype>
#include <cstring>

#if 0
// 有四个特化版本：
// - char 专门用于char类型，一个char占一个字节
// - wchar_t 专门用于wchar_t类型，大小，符号和占位和另一种的整形类型一致
// - char16_t 专门用于char16_t类型，大小为16位
// - char32_t 专门用于char32_t类型，大小为32位
template <class charT> 
struct char_traits;
#endif

struct MyCharTraits : public std::char_traits<char> {
  static bool eq(char c1, char c2) {
    return std::tolower(c1)==std::tolower(c2);
  }
};

void MemFun() {
  std::char_traits<char> char_traits;

  bool eq = std::char_traits<char>::eq('a', 'a');
  std::cout << "eq: " << eq << std::endl;

  bool lt = std::char_traits<char>::lt('a', 'b');
  std::cout << "lt: " << lt << std::endl;

  char c[] = "Hello";
  std::size_t len = std::char_traits<char>::length(c);
  std::cout << "len: " << len << std::endl;

  int eol = std::char_traits<char>::eof();
  std::cout << "eol: " << eol << std::endl;

  std::char_traits<char16_t> char16_traits;
  bool eq16 = std::char_traits<char16_t>::eq(u'a', u'a');
  std::cout << "eq16: " << eq16 << std::endl;

  std::char_traits<char32_t> char32_traits;
  bool eq32 = std::char_traits<char32_t>::eq(U'a', U'a');
  std::cout << "eq32: " << eq32 << std::endl;

  std::char_traits<wchar_t> wchar_traits;
  bool eqw = std::char_traits<wchar_t>::eq(L'a', L'a');
  std::cout << "eqw: " << eqw << std::endl;
}

void MyTest() {
  std::basic_string<char, MyCharTraits> str1 = "Hello";
  std::basic_string<char, MyCharTraits> str2 = "hello";
  if(str1 == str2) {
    std::cout << "str1 == str2" << std::endl;
  } else {
    std::cout << "str1 != str2" << std::endl;
  }
}

void TypeTest() {
  char a = 'a';
  char16_t b = u'b';
  char32_t c = U'c';
  wchar_t d = L'd';
  std::cout << "sizeof(char): " << sizeof(a) << std::endl;
  std::cout << "sizeof(char16_t): " << sizeof(b) << std::endl;
  std::cout << "sizeof(char32_t): " << sizeof(c) << std::endl;
  std::cout << "sizeof(wchar_t): " << sizeof(d) << std::endl;

  std::string str = "Hello";
  std::u16string str16 = u"Hello";
  std::u32string str32 = U"Hello";
  std::wstring strw = L"Hello";

  std::cout << "str size: " << str.size() << std::endl;
  std::cout << "str16 size: " << str16.size() << std::endl;
  std::cout << "str32 size: " << str32.size() << std::endl;
  std::cout << "strw size: " << strw.size() << std::endl;

  // std::cout << "str16: " << str16 << std::endl; // error: no match for ‘operator<<’ (operand types are ‘std::ostream {aka std::basic_ostream<char>}’ and ‘std::u16string {aka std::basic_string<char16_t>}’)
}

int main() {
  std::cout << "====================== char_traits ======================" << std::endl;
  MemFun();
  std::cout << "====================== MyCharTraits ======================" << std::endl;
  MyTest();
  std::cout << "====================== TypeTest ======================" << std::endl;
  TypeTest();
  return 0;
}