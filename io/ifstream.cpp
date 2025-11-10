#include <iostream>
#include <fstream>
#include <type_traits>

void MemType() {
    if(std::is_same<std::ifstream::char_type, char>::value) {
        std::cout << "std::ifstream::char_type is char" << std::endl;
    }
    if(std::is_same<std::ifstream::traits_type, std::char_traits<char>>::value) {
        std::cout << "std::ofstream::traits_type is std::char_trait<char>" << std::endl;
    }
    if(std::is_same<std::ifstream::int_type, int>::value) {
        std::cout << "std::ifstream::int_type is int" << std::endl;
    }
    if(std::is_same<std::ifstream::pos_type, std::streampos>::value) {
        std::cout << "std::ifstream::pos_type is streampos" << std::endl;
    }
    if(std::is_same<std::ifstream::off_type, std::streamoff>::value) {
        std::cout << "std::ifstream::off_type is streamoff" << std::endl;
    }

    // Inherit from istream and io_base
    if(std::is_same<std::ifstream::event, std::ios_base::event>::value) {
        std::cout << "std::ifstream::event is std::ios_base::event" << std::endl;
    }
    if(std::is_same<std::ifstream::failure, std::ios_base::failure>::value) {
        std::cout << "std::ifstream::failure is std::ios_base::failure" << std::endl;
    }
    if(std::is_same<std::ifstream::fmtflags, std::ios_base::fmtflags>::value) {
        std::cout << "std::ifstream::fmtflags is std::ios_base::fmtflags" << std::endl;
    }
    if(std::is_same<std::ifstream::iostate, std::ios_base::iostate>::value) {
        std::cout << "std::ifstream::iostate is std::ios_base::iostate" << std::endl;
    }
}

void Confun() {
    std::ifstream ifs = std::ifstream();
    std::ifstream ifs2 = std::ifstream("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);
    std::ifstream ifs3(std::move(ifs2));
}

void MemFun() {
    std::ifstream ifs = std::ifstream("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);
    bool ret = ifs.is_open();
    std::cout << "is_open: " << ret << std::endl;

    std::filebuf* pbuf = ifs.rdbuf();

    ifs.open("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test3.txt", std::ios::in);
    ret = ifs.is_open();
    std::cout << "is_open: " << ret << std::endl;

    std::ifstream ifs2 = std::ifstream("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);
    ifs.swap(ifs2);

    ifs.close();
}

void Inherit_istream() {
    std::ifstream ifs = std::ifstream("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);
    std::streamsize size;
    size = ifs.tellg();
    std::cout << "tellg: " << size << std::endl;

    std::string str;
    // 按行读取
    ifs >> str;
    std::cout << "str: " << str << std::endl;
    // 返回上一次 unformatted input operations 读取的字符数
    // unformatted input operations有：get，getline，ignore，peek，read，readsome，putback，unget
    size = ifs.gcount();
    std::cout << "gcount: " << size << std::endl;
    ifs >> str;
    std::cout << "str: " << str << std::endl;
    size = ifs.gcount();
    std::cout << "gcount: " << size << std::endl;

    int ret = ifs.get();
    std::cout << "get: " << ret << ", char:" << static_cast<char>(ret) << std::endl;
    ret = ifs.get();
    std::cout << "get: " << ret << ", char:" << static_cast<char>(ret) << std::endl;
    size = ifs.gcount();
    std::cout << "gcount: " << size << std::endl;
    char ret2;
    ifs.get(ret2);
    std::cout << "get: " << ret2 << std::endl;
    size = ifs.gcount();
    std::cout << "gcount: " << size << std::endl;
    char buf[10];
    ifs.get(buf, 10);
    std::cout << "get: " << buf << std::endl;
    size = ifs.gcount();
    std::cout << "gcount: " << size << std::endl;

    ifs.getline(buf, 10);
    std::cout << "getline: " << buf << std::endl;

    ifs.ignore(1);

    ret = ifs.peek();
    std::cout << "peek: " << ret << std::endl;

    ifs.read(buf, 6);
    std::cout << "read: " << buf << std::endl;

    ret = ifs.readsome(buf, 6);
    std::cout << "readsome: " << ret << std::endl;

    ifs.putback('1');
    ifs >> str;
    std::cout << "putback: " << str << std::endl;

    ifs.unget();
    ifs >> str;
    std::cout << "unget: " << str << std::endl;

    std::streampos pos = ifs.tellg();
    std::cout << "tellg: " << pos << std::endl;

    ifs.seekg(0);
    pos = ifs.tellg();
    std::cout << "tellg: " << pos << std::endl;
    ifs.seekg(10, std::ios::beg);
    ret = ifs.get();
    std::cout << "get: " << ret << std::endl;

    ret = ifs.sync();
    if(ret == 0) {
        std::cout << "sync success" << std::endl;
    } else {
        std::cout << "sync failed" << std::endl;
    }
}

void Inherit_ios() {
  std::ifstream ifs("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);

  bool ret = ifs.good();
  if(ret) {
    std::cout << "good" << std::endl;
  } else {
    std::cout << "bad" << std::endl;
  }
  ret = ifs.eof();
  if(ret) {
    std::cout << "eof" << std::endl;
  } else {
    std::cout << "not eof" << std::endl;
  }
  ret = ifs.fail();
  if(ret) {
    std::cout << "fail" << std::endl;
  } else {
    std::cout << "not fail" << std::endl;
  }
  ret = ifs.bad();
  if(ret) {
    std::cout << "bad" << std::endl;
  } else {
    std::cout << "not bad" << std::endl;
  }

  std::ios::iostate state = ifs.rdstate();
  ifs.setstate(std::ios::badbit);
  ifs.clear();

  char c = ifs.fill();
  std::cout << "fill: " << int(c) << std::endl;
  c = ifs.fill('1');
  std::cout << "fill: " << int(c) << std::endl;
}

void Inherit_iosbase() {
  std::ifstream ifs("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test2.txt", std::ios::in);

  std::ios_base::fmtflags flags = ifs.flags();
  if(flags & std::ios_base::dec) {
    std::cout << "dec" << std::endl;
  }
  if(flags & std::ios_base::oct) {
    std::cout << "oct" << std::endl;
  } else {
    std::cout << "not oct" << std::endl;
  }
  std::ios_base::fmtflags before = ifs.setf(std::ios_base::oct);
  ifs.unsetf(std::ios_base::oct);

  std::streamsize precision = ifs.precision();
  std::cout << "precision: " << precision << std::endl;

  std::streamsize width = ifs.width();
  std::cout << "width: " << width << std::endl;

}

int main() {
    std::cout << "==========================MemType==========================" << std::endl;
    MemType();
    std::cout << "==========================Confun==========================" << std::endl;
    Confun(); 
    std::cout << "==========================MemFun==========================" << std::endl;
    MemFun(); 
    std::cout << "==========================Inherit_istream==========================" << std::endl;
    Inherit_istream();
    std::cout << "==========================Inherit_ios==========================" << std::endl;
    Inherit_ios();
    std::cout << "==========================Inherit_iosbase==========================" << std::endl;
    Inherit_iosbase();
}