/**
 * 在utf编码中进行转换
 */

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <type_traits>

#if 0
enum codecvt_mode {
  consume_header = 4,
  generate_header = 2,
  little_endian = 1
};
#endif

#if 0
// 在两种不同的字符编码之间进行转换：一般intern_type是wchar_t，extern_type是多字节的序列
// 其构造函数是protected的，不能直接实例化，只能通过派生类实例化
template <
    class internT,
    class externT,
    class stateT
> class codecvt;
#endif

#if 0
template <
    class Elem, // intern_type
    unsigned long MaxCode = 0x10ffffUL, // max_code
    codecvt_mode Mode = (codecvt_mode)0 
> 
class codecvt_utf8 : public codecvt <Elem, char, mbstate_t>
#endif

#if 0
template < 
    class Elem,
    unsigned long MaxCode = 0x10ffffUL,
    codecvt_mode Mode = (codecvt_mode)0 
>  class codecvt_utf16 : public codecvt <Elem, char, mbstate_t>
#endif

#if 0
// Convert to/from wide string
template < 
    class Codecvt,
    class Elem = wchar_t, // 需要跟Codecvt的intern_type一致
    class Wide_alloc = std::allocator<Elem>,
    class Byte_alloc = std::allocator<char> 
> class wstring_convert;
#endif

void MemType() {
  std::codecvt_utf8<wchar_t> cvt;
  if(std::is_same<std::codecvt_utf8<wchar_t>::intern_type, wchar_t>::value) {
    std::cout << "codecvt_utf8<wchar_t>::intern_type is wchar_t" << std::endl;
  } else {
    std::cout << "codecvt_utf8<wchar_t>::intern_type is not wchar_t" << std::endl;
  }
  if(std::is_same<std::codecvt_utf8<wchar_t>::extern_type, char>::value) {
    std::cout << "codecvt_utf8<wchar_t>::extern_type is char" << std::endl;
  } else {
    std::cout << "codecvt_utf8<wchar_t>::extern_type is not char" << std::endl;
  }
  if(std::is_same<std::codecvt_utf8<wchar_t>::state_type, mbstate_t>::value) {
    std::cout << "codecvt_utf8<wchar_t>::state_type is mbstate_t" << std::endl;
  } else {
    std::cout << "codecvt_utf8<wchar_t>::state_type is not mbstate_t" << std::endl;
  }
  if(std::is_same<std::codecvt_utf8<wchar_t>::result, std::codecvt_base::result>::value) {
    std::cout << "codecvt_utf8<wchar_t>::result is std::codecvt_base::result" << std::endl;
  } else {
    std::cout << "codecvt_utf8<wchar_t>::result is not std::codecvt_base::result" << std::endl;
  }
}

void MemFun_in() {
  std::codecvt_utf8<wchar_t> cvt;

#if 0
// 用于从extern_type转换到intern_type，典型的multibyte-to-wide character转换
result in (
    state_type& state,
    const extern_type* from,
    const extern_type* from_end,
    const extern_type*& from_next,
    intern_type* to,
    intern_type* to_limit,
    intern_type*& to_next
) const;
#endif

  const char mystr[] = "Hello, world!";
  wchar_t pwstr[sizeof(mystr)];
  std::mbstate_t state = std::mbstate_t();
  const char* pc;
  wchar_t* pwc;
  std::codecvt_base::result r = cvt.in(
      state,
      mystr,
      mystr + sizeof(mystr),
      pc,
      pwstr,
      pwstr + sizeof(pwstr),
      pwc
  );
  if(r == std::codecvt_base::ok) {
    std::wcout << pwstr << std::endl;
  } else {
    std::cout << "Failed to convert!" << std::endl;
  }
}

void MemFun_out() {
  std::codecvt_utf8<wchar_t> cvt;

#if 0
// 用于从intern_type转换到extern_type，典型的wide character-to-multibyte转换
result out (
    state_type& state,
    const intern_type* from,
    const intern_type* from_end,
    const intern_type*& from_next,
    extern_type* to,
    extern_type* to_limit,
    extern_type*& to_next
) const;
#endif
  std::wstring mywstr = L"Hello, world!";
  std::wstring::size_type len = mywstr.size();
  std::cout << "wstring size: " << len << std::endl;
  char* pstr = new char[len+1];
  std::mbstate_t state = std::mbstate_t();
  const wchar_t* pwc;
  char* pc;
  std::codecvt_base::result r = cvt.out(
      state,
      mywstr.c_str(),
      mywstr.c_str() + len,
      pwc,
      pstr,
      pstr + len,
      pc
  );
  if(r == std::codecvt_base::ok) {
    std::cout << pstr << std::endl;
  } else {
    std::cout << "Failed to convert!" << std::endl;
  }
  delete[] pstr;
}

void MemFun_out_u16() {
  std::codecvt_utf8<char16_t> cvt;

  std::u16string mywstr = u"Hello, world!";
  std::u16string::size_type len = mywstr.size();
  std::cout << "u16string size: " << len << std::endl;
  char* pstr = new char[len+1];
  std::mbstate_t state = std::mbstate_t();
  const char16_t* pwc;
  char* pc;
  std::codecvt_base::result r = cvt.out(
      state,
      mywstr.c_str(),
      mywstr.c_str() + len,
      pwc,
      pstr,
      pstr + len,
      pc
  );
  if(r == std::codecvt_base::ok) {
    std::cout << pstr << std::endl;
  } else {
    std::cout << "Failed to convert!" << std::endl;
  }
  delete[] pstr;
}

void MemFun() {
  std::codecvt_utf8<wchar_t> cvt;

  // true 如果intern_type和extern_type会发生无法转换的情况
  int ret = cvt.always_noconv();
  std::cout << "always_noconv: " << ret << std::endl;

  ret = cvt.encoding();
  std::cout << "encoding: " << ret << std::endl;

  // Returns the maximum number of internal characters needed for an external character.
  ret = cvt.max_length();
  std::cout << "max_length: " << ret << std::endl;

#if 0
int length (
    state_type& state,
    const extern_type* from,
    const extern_type* from_end,
    size_t max
) const; 
#endif
  std::mbstate_t state = std::mbstate_t();
  const char mystr[] = "Hello, world!";
  int len = cvt.length(state, mystr, mystr + sizeof(mystr), sizeof(mystr));
  std::cout << "length: " << len << std::endl;
}

int main() {
  std::cout << "====================== MemType ======================" << std::endl;
  MemType();
  std::cout << "====================== MemFun_in ======================" << std::endl;
  MemFun_in();
  std::cout << "====================== MemFun_out ======================" << std::endl;
  MemFun_out();
  std::cout << "====================== MemFun_out_u16 ======================" << std::endl;
  MemFun_out_u16();
  std::cout << "====================== MemFun ======================" << std::endl;
  MemFun();
  return 0;
}