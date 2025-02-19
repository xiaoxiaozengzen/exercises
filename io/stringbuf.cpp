/**
 * Stream buffer to read from and write to string objects.
 */

#include <iostream>
#include <sstream>

// typedef basic_stringbuf<char> stringbuf;

void MemType() {
  std::cout << "reference ifstream" << std::endl;
}

void Confun() {
  // explicit stringbuf (ios_base::openmode which = ios_base::in | ios_base::out);
  std::stringbuf sb1;
  std::stringbuf sb2(std::move(sb1));
  // std::stringbuf sb3(std::stringbuf()); // delete

  // explicit stringbuf (const string& str,                    ios_base::openmode which = ios_base::in | ios_base::out)
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
  std::cout << "====================MemType====================" << std::endl;
  MemType();
  std::cout << "====================Confun====================" << std::endl;
  Confun();
  std::cout << "====================MemFun====================" << std::endl;
  MemFun();
}