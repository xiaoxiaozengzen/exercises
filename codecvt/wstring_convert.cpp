#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
#include <cstring>
#include <cstdint>
#include <iomanip>

#if 0
// 用于在wide string和multibyte string之间转换
template < 
    class Codecvt,
    class Elem = wchar_t, // 需要跟codvect的intern_type一致
    class Wide_alloc = std::allocator<Elem>,
    class Byte_alloc = std::allocator<char> 
> class wstring_convert;
#endif

void ConFun() {
  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert(new std::codecvt_utf8<char16_t>);

  std::string utf8_string = "Hello!";
  std::u16string utf16_string = u"world!";
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert2(utf8_string, utf16_string);
}

void MemFun() {
  const std::string utf8_string = "123456!";
  const std::u16string utf16_string = u"world!";

  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
  std::u16string utf16_string2 = convert.from_bytes(utf8_string);
  std::cout << "utf16_string2 size: " << utf16_string2.size() << std::endl;
  char buf[15];
  memcpy(buf, reinterpret_cast<void*>(const_cast<char16_t*>(utf16_string2.data())), utf16_string2.size() * sizeof(char16_t));
  buf[utf16_string2.size() * sizeof(char16_t)] = '\0';

  for(int i = 0; i < 15; i++) {
    std::cout << "buf[" << i << "]: " << static_cast<std::uint32_t>(buf[i]) << std::endl;
  }

  std::string utf8_string2 = convert.to_bytes(utf16_string);
  std::cout << "utf8_string2 size: " << utf8_string2.size() << std::endl;
  std::cout << "utf8_string2: " << utf8_string2 << std::endl;

  std::uint32_t value = 0x12345678;
  std::uint8_t p[4];
  memcpy(p, &value, 4);
  for(int i = 0; i < 4; i++) {
    std::cout << "p[" << i << "]: " << std::hex << static_cast<std::uint32_t>(p[i]) << std::endl;
  }

  std::size_t converted = convert.converted();
  std::cout << "converted: " << converted << std::endl;
  std::mbstate_t state = std::mbstate_t();
}

void chinese() {
  std::string utf8_string = "你好";
  std::u16string utf16_string = u"你好";
  std::cout << "utf8_string size: " << utf8_string.size() << ", bytes: " << utf8_string.size() * sizeof(char) << std::endl;
  std::cout << "utf16_string size: " << utf16_string.size() << ", bytes: " << utf16_string.size() * sizeof(char16_t) << std::endl;

  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;

  std::u16string utf16_string2 = convert.from_bytes(utf8_string);
  std::string utf8_string2 = convert.to_bytes(utf16_string);
  std::cout << "utf8_string2: " << utf8_string2 << std::endl;
  std::cout << "utf8_string2 size: " << utf8_string2.size() << std::endl;
  std::cout << "utf16_string2 size: " << utf16_string2.size() << std::endl;
}

int main() {
  std::cout << "====================ConFun====================" << std::endl;
  ConFun();
  std::cout << "====================MemFun====================" << std::endl;
  MemFun();
  std::cout << "====================chinese====================" << std::endl;
  chinese();
  return 0;
}