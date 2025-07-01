#include <iostream>
#include <string>
#include <string_view>
#include <cstddef>
#include <cctype>
#include <cstring>
#include <type_traits>

/**
 * template <class charT> 
 * struct char_traits;
 * 
 * @brief char_traits 是一个模板结构体，用于定义字符类型的特性。
 * 
 * template <> 
 * struct char_traits<char>;
 * 
 * template <> 
 * struct char_traits<wchar_t>;
 * 
 * template <> 
 * struct char_traits<char16_t>;
 * 
 * template <> 
 * struct char_traits<char32_t>;
 */

#if 0
// 有四个特化版本：
// - char 专门用于char类型，一个char占一个字节
// - wchar_t 专门用于wchar_t类型，大小，符号和占位和另一种的整形类型一致
// - char16_t 专门用于char16_t类型，大小为16位
// - char32_t 专门用于char32_t类型，大小为32位
template <class charT> 
struct char_traits;
#endif

void MemType() {
  if(std::is_same<std::char_traits<char>::char_type, char>::value) {
    std::cout << "char_traits<char>::char_type is char" << std::endl;
  }
  if(std::is_same<std::char_traits<char>::int_type, int>::value) {
    std::cout << "char_traits<char>::int_type is int" << std::endl;
  }
  if(std::is_same<std::char_traits<char>::off_type, std::streamoff>::value) {
    std::cout << "char_traits<char>::off_type is std::streamoff" << std::endl;
  }
  if(std::is_same<std::char_traits<char>::pos_type, std::streampos>::value) {
    std::cout << "char_traits<char>::pos_type is std::streampos" << std::endl;
  }
}

void MemFun() {
  std::char_traits<char> char_traits;

  bool eq = std::char_traits<char>::eq('a', 'a');
  std::cout << "eq: " << eq << std::endl;

  bool lt = std::char_traits<char>::lt('a', 'b');
  std::cout << "lt: " << lt << std::endl;

  /**
   * @brief 返回以\0结尾的字符串的长度，不包括\0。
   * @note 作用类似strlen()函数。
   */
  char c[] = "Hello";
  std::size_t len = std::char_traits<char>::length(c);
  std::cout << "len: " << len << std::endl;

  /**
   * static void assign (char_type& r, const char_type& c) noexcept;
   * @brief 将字符 c 赋值给 r。类似 r = c;
   */
  char r = 'a';
  std::char_traits<char>::assign(r, 'b');
  std::cout << "assign: " << std::string("")+r << std::endl;

  /**
   * static char_type* assign (char_type* p, site_t n, char_type c);
   * @brief 将字符 c 赋值给 p 指向的前 n 个字符。
   */
  char p[10] = "aaaaaaa";
  std::char_traits<char>::assign(p, 5, 'x');
  std::cout << "assign p: " << p << std::endl;

  /**
   * static int compare (const char_type* p, const char_type* q, size_t n);
   * @brief 比较 p 和 q 指向的前 n 个字符。
   * @return 如果 p < q 返回负数，如果 p > q 返回正数，如果 p == q 返回 0。
   * @note 作用类似strncmp()函数。
   */
  const char* p1 = "abc";
  const char* p2 = "abd";
  int cmp = std::char_traits<char>::compare(p1, p2, 3);
  if(cmp < 0) {
    std::cout << "p1 < p2" << std::endl;
  } else if(cmp > 0) {
    std::cout << "p1 > p2" << std::endl;
  } else {
    std::cout << "p1 == p2" << std::endl;
  }

  /**
   * static const char_type* find (const char_type* p, size_t n, const char_type& c);
   * @brief 在 p 指向的前 n 个字符中查找字符 c。
   * @return 如果找到返回指向 c 的指针，否则返回 nullptr。
   */
  const char* p3 = "Hello, world!";
  const char* found = std::char_traits<char>::find(p3, 13, 'w');
  if(found) {
    std::cout << "Found 'w' at position: " << (found - p3) << std::endl;
  } else {
    std::cout << "'w' not found" << std::endl;
  }

  /**
   * static char_type* move (char_type* dest, const char_type* src, size_t n);
   * @brief 将 src 指向的前 n 个字符移动到 dest 指向的位置。即使overlap
   * @note 作用类似memmove()函数，支持重叠内存区域的移动。
   */
  char src[] = "Hello, world!";
  char dest[20];
  std::char_traits<char>::move(dest, src, 7);
  dest[13] = '\0'; // 确保字符串以 null 结尾
  std::cout << "Moved src: " << src << std::endl;
  std::cout << "Moved dest: " << dest << ", len:" << strlen(dest) << std::endl;

  /**
   * static char_type* copy (char_type* dest, const char_type* src, size_t n);
   * @brief 将 src 指向的前 n 个字符拷贝到 dest 指向的位置。即使overlap
   * @note 作用类似memcpy()函数，不支持重叠内存区域的拷贝。
   */
  char src_copy[] = "1234,5678";
  char dest_copy[20];
  std::char_traits<char>::copy(dest_copy, src_copy, 7);
  dest_copy[13] = '\0'; // 确保字符串以 null 结尾
  std::cout << "Copied src: " << src_copy << std::endl;
  std::cout << "Copied dest: " << dest_copy << ", len:" << strlen(dest_copy) << std::endl;

  int eol = std::char_traits<char>::eof();
  std::cout << "eol: " << eol << std::endl;

  char c1 = 'a';
  int not_eof = std::char_traits<char>::not_eof(c1);
  std::cout << "not_eof: " << not_eof << std::endl;
  int eof = std::char_traits<char>::not_eof(eol);
  std::cout << "eof: " << eof << std::endl;

  char ret = std::char_traits<char>::to_char_type(67);
  std::cout << "to_char_type: " << std::string("")+ret << std::endl;

  int int_ret = std::char_traits<char>::to_int_type('d');
  std::cout << "to_int_type: " << int_ret << std::endl;

  bool euqal_ret = std::char_traits<char>::eq_int_type(12, 12);
  std::cout << "eq_int_type: " << euqal_ret << std::endl;

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

struct MyCharTraits : public std::char_traits<char> {
  static bool eq(char c1, char c2) {
    return std::tolower(c1)==std::tolower(c2);
  }
};

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
  std::cout << "====================== MemType ======================" << std::endl;
  MemType();
  std::cout << "====================== MemFun ======================" << std::endl;
  MemFun();
  std::cout << "====================== MyCharTraits ======================" << std::endl;
  MyTest();
  std::cout << "====================== TypeTest ======================" << std::endl;
  TypeTest();
  return 0;
}