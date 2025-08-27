#include <iostream>
#include <sstream>

/**
 * @brief basic_stringbuf继承自basic_streambuf，并且实现了在basic_string上进行输入输出操作的功能。
 * 
 * @note 该类提供了在内存中读写字符串的能力，类似于文件流(file stream)。
 */
void Confun() {
  // explicit stringbuf (ios_base::openmode which = ios_base::in | ios_base::out);
  std::stringbuf sb1;
  std::stringbuf sb2(std::move(sb1));
  // std::stringbuf sb3(std::stringbuf()); // delete

  // explicit stringbuf (const string& str, ios_base::openmode which = ios_base::in | ios_base::out)
  std::string str = "hello world";
  std::stringbuf sb4(str);
}

void MemFun() {
  std::stringbuf sb1;
  std::string ret = sb1.str();
  std::cout << "sb1.str() = " << ret << std::endl;

  std::string str = "hello world";
  std::stringbuf sb2(str);
  ret = sb2.str();
  std::cout << "sb2.str() = " << ret << std::endl;
  sb2.str("nihao");
  ret = sb2.str();
  std::cout << "sb2.str() = " << ret << std::endl;
}

int main() {
  std::cout << "====================Confun====================" << std::endl;
  Confun();
  std::cout << "====================MemFun====================" << std::endl;
  MemFun();
}