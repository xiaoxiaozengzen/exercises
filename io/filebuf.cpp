/**
 * Stream buffer to read from and write to files.
 */

#include <iostream>
#include <fstream>
#include <type_traits>

void MemType(){
    if(std::is_same<std::filebuf::char_type, char>::value){
        std::cout << "filebuf::char_type is char" << std::endl;
    }
    if(std::is_same<std::filebuf::traits_type, std::char_traits<char>>::value){
        std::cout << "filebuf::traits_type is std::char_traits<char>" << std::endl;
    }
    if(std::is_same<std::filebuf::int_type, int>::value){
        std::cout << "filebuf::int_type is int" << std::endl;
    }
    // template <class stateT> class fpos;
    // fpos可以简单认为是一个int，因为它需要从int构造，并且可以支持加减streamoff

    // typedef fpos<mbstate_t> streampos;
    if(std::is_same<std::filebuf::pos_type, std::streampos>::value){
        std::cout << "filebuf::pos_type is streampos" << std::endl;
    }
    // typedef internal_type streamoff;
    if(std::is_same<std::filebuf::off_type, std::streamoff>::value){
        std::cout << "filebuf::off_type is streamoff" << std::endl;
    }
}

void ConFun() {
  std::filebuf fb = std::filebuf();
  // std::filebuf fb2(std::filebuf()); delete
  std::filebuf fb2(std::move(fb));
}

void MemFun() {
  std::filebuf fb;
  std::filebuf fbb;

  std::string file1 = "/mnt/workspace/cgz_workspace/Exercise/exercises/io/test.txt";
  std::string file2 = "/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt";

  std::filebuf *fb1 = fb.open(file1, std::ios::in);
  if(fb1 == nullptr){
    std::cout << "open file1 failed" << std::endl;
  } else {
    std::cout << "open file1 success" << std::endl;
  }
  std::filebuf *fb2 = fbb.open(file2, std::ios::in);
  if(fb2 == nullptr){
    std::cout << "open file2 failed, because it is not existed" << std::endl;
  } else {
    std::cout << "open file2 success" << std::endl;
  }
  std::filebuf *fb3 = fb.open(file1, std::ios::out | std::ios::app);
  if(fb3 == nullptr){
    std::cout << "open file1 failed, because it has been opened" << std::endl;
  } else {
    std::cout << "open file1 success" << std::endl;
  }

  bool is_open = fb.is_open();
  if(is_open){
    std::cout << "file1 is open" << std::endl;
  } else {
    std::cout << "file1 is not open" << std::endl;
  }

  bool is_open2 = fbb.is_open();
  if(is_open2){
    std::cout << "file2 is open" << std::endl;
  } else {
    std::cout << "file2 is not open" << std::endl;
  }

  std::filebuf *fb4 = fb.close();
  if(fb4 == nullptr){
    std::cout << "close file failed" << std::endl;
  } else {
    std::cout << "close file success" << std::endl;
  }
}

/**
 * filebuf继承了streambuf，所以可以使用streambuf的所有public方法。
 * streambuf得构造函数是protected的，所以streambuf不能直接构造
 */
void PubMemFunInhertStreambuff() {
  // std::streambuf buf; // 编译报错is protected within this context
}

int main() {
  std::cout << "======================MemType======================" << std::endl;
  MemType();
  std::cout << "======================ConFun======================" << std::endl;
  ConFun();
  std::cout << "======================MemFun======================" << std::endl;
  MemFun();
  std::cout << "======================PubMemFunInhertStreambuff======================" << std::endl;
  PubMemFunInhertStreambuff();
}
