#include <ios>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>

/**
 * 输入输出库，使用stream的方式，在字符序列(例如文件、字符串)上进行输入输出操作
 */


/**
 * @brief ios_base类是所有I/O流类的基类，提供大部分与流状态和格式化相关的功能，无关具体的字符类型。
 * 
 * @note 该类不处理具体的输入输出操作，而是提供了一组通用的接口和成员变量，
 * @note 以便派生类可以继承和扩展这些功能。
 * @note 构造函数是protected的，不能直接创建对象
 */
void ios_base_example() {
#if 0
    // ios_base的构造函数是protected的，不能直接创建对象
    protected: ios_base();
    ios_base (const ios_base&) = delete;
#endif

    /**
     * 成员函数
     * 1. formatting
     *   - flags
     *   - setf
     *   - unsetf
     *   - precision
     *   - width
     * 2. locale
     *   - imbue
     *   - getloc
     * 3.others
     *   - void register_callback (event_callback fn, int index);
     *      * 注册一个fn函数，改函数会在stream event发生的时候自动调用，并且使用之前传入的index
     *   - sync_with_stdio
     */

     /**
      * 成员类型：
      * 1. event： 
      *   - enum class event {
      *         copyfmt_event,
      *         erase_event,
      *         imbue_event
      *     }
      * 2. event_callback: 
      *   - typedef void (*event_callback) (event ev, ios_base& obj, int index);
      * 3. fmtflags:
      *   - 一个bitmap类型来表示流的格式化标志
      *     - adjustfield：调整域的标志位掩码
      *       * left：左对齐
      *       * right：右对齐
      *       * internal：符号位在最左边，数字右对齐
      *     - 等其他流格式
      * 4. iostate: 一个bitmap类型来表示当前流的状态
      *   - eofbit：已经到达流的末尾
      *   - failbit：上一次的input操作失败
      *   - badbit：由于之前的输入或者输出流操作失败导致位于流的错误状态
      *   - goodbit：流的状态正常
      * 5. openmode: 一个bitmap类型来表示流的打开模式
      *   - app：追加模式
      *   - ate：打开流时，定位到流的末尾
      *   - binary：二进制模式
      *   - in：输入模式
      *   - out：输出模式
      *   - trunc：截断模式
      * 6. seekdir: 一个枚举类型来表示流的定位方式
      *   - beg：从流的开头开始定位
      *   - cur：从流的当前位置开始定位
      *   - end：从流的末尾开始定位
      * 
      * 成员类：
      * 1. init: class init；
      *    - 内部类，一般给标准库的实现人员使用。
      *    - 保证std::cin, std::cout, std::cerr, std::clog在main函数开始前被正确初始化
      * 2. failure： class failure;
      *   - 该类继承自system_error，用于表示I/O流操作中的错误
      *   - 该类含有code()成员函数，返回一个std::error_code对象，表示具体的错误类型
      *   - 该类含有what()成员函数，返回一个C风格的字符串，描述错误信息
      */
}

/**
 * template <class charT, class traits = char_traits<charT> >  
 * class basic_ios;
 * 
 * @brief 该类继承了ios_base。该类跟ios_base一起实现了无关输出/输出类型的流的操作。
 * 
 * @note 区别是：ios_base实现了无关字符类型的流的操作，而basic_ios则实现了与具体字符类型相关的流的操作。
 * @note 其中 using ios = basic_ios<char>;
 */
void basic_ios_example() {
    // 1. 除了继承自ios_base的成员类型外，basic_ios还定义了以下成员类型
    if(std::is_same<std::basic_ios<char>::char_type, char>::value) {
        std::cout << "std::basic_ios<char>::char_type is char" << std::endl;
    } else {
        std::cout << "std::basic_ios<char>::char_type is not char" << std::endl;
    }

    // 2, constructor
    /**
     * public: explicit basic_ios (basic_streambuf<char_type,traits_type>* sb);
     * 
     * protected: basic_ios();
     * 
     * basic_ios (const basic_ios&) = delete;basic_ios& operator= (const basic_ios&) = delete;
     */

    // 3. 除了继承自ios_base的成员函数外，basic_ios还定义了以下成员函数
    /**
     * 1. state flag fun
     *   - good
     *   - eof
     *   - fail
     *   - bad
     *   - rdstate
     *   - setstate
     *   - clear
     *   - operator bool
     *   - operator!
     * 2. formatting fun
     *   - fill
     *   - copyfmt
     * 3. others
     *   - exception
     *   - imbue
     *   - tie
     *   - rdbuf
     *     - basic_streambuf<char_type,traits_type>* rdbuf() const; // 获取当前关联的streambuf对象
     *     - basic_streambuf<char_type,traits_type>* rdbuf(basic_streambuf<char_type,traits_type>* sb); // 设置关联的streambuf对象
     *   - narrow
     *   - widen
     */

    std::string str = "hello world";
    std::stringbuf sb(str);
    std::basic_ios<char> ios(&sb);

    bool is_good = ios.good();
    if(is_good) {
        std::cout << "ios is good" << std::endl;
    } else {
        std::cout << "ios is not good" << std::endl;
    }
    bool is_eof = ios.eof();
    if(is_eof) {
        std::cout << "ios is eof" << std::endl;
    } else {
        std::cout << "ios is not eof" << std::endl;
    }
    std::ios_base::iostate state = ios.rdstate();
    if(state == std::ios_base::goodbit) {
        std::cout << "ios rdstate is goodbit" << std::endl;
    } else if(state == std::ios_base::eofbit) {
        std::cout << "ios rdstate is eofbit" << std::endl;
    } else if(state == std::ios_base::failbit) {
        std::cout << "ios rdstate is failbit" << std::endl;
    } else if(state == std::ios_base::badbit) {
        std::cout << "ios rdstate is badbit" << std::endl;
    } else {
        std::cout << "ios rdstate is unknown" << std::endl;
    }

    int size = ios.width();
    std::cout << "ios width is " << size << std::endl;
}

/**
 * template <class charT, class traits = char_traits<charT> >
 * class basic_istream;
 * 
 * @brief 该类继承自basic_ios，提供了输入流的功能：从字符序列(例如文件、字符串)中读取数据，并解析数据。
 */
void basic_istream_test() {
  // 1.除了继承自basic_ios的成员类型外，basic_istream还定义了以下成员类型

  // 2. constructor
  /**
   * explicit basic_istream (basic_streambuf<char_type,traits_type>* sb);
   */

  // 3. 除了继承自basic_ios的成员函数外，basic_istream还定义了以下成员函数
  /**
   * 1.Formatting functions
   *   - operator>> // 重载输入运算符
   * 2. Unformatted input functions
   *   - gcount // 返回上一次未格式化输入操作中读取的字符数
   *   - get // 从流中读取字符
   *   - getline // 从流中读取一行字符，区别于read是read接口不管'\n'，而getline会以'\n'为结束符提前结束读取
   *   - ignore // 忽略指定数量的字符。或者直到遇到指定的分隔符为止
   *   - peek // 查看下一个字符，但不从流中提取它
   *   - read // 从流中读取指定数量的字符，并存储到指定的缓冲区中
   *   - readsome // 从流中读取可用的字符，并存储到指定的缓冲区中
   *   - putback // 将一个字符放回流
   *   - putback // 将一个字符放回流
   *   - unget // 将最后一个提取的字符放回流
   * 3. positioning
   *   - tellg // 返回当前读位置相对于流开头的偏移量
   *   - seekg // 设置读位置相对于流开头的偏移量
   * 4. synchronization
   *   - sync // 同步流的缓冲区与其底层设备
   */
  std::string str = "1234567\nHello, World!\n";
  std::stringbuf sbuf(str);
  std::basic_istream<char> istream(&sbuf);
  std::cout << "+++++++ 1 +++++++" << std::endl;
  char ret1 = istream.get(); // 读取一个字符
  std::cout << "gcount: " << istream.gcount() << ", ret1: " << ret1 << std::endl;
  char ret2 = istream.peek(); // 查看下一个字符
  std::cout << "gcount: " << istream.gcount() << ", ret2: " << ret2 << std::endl;
  char buf[10];
  istream.getline(buf, 10); // 读取一行字符，遇到'\n'结束
  std::cout << "gcount: " << istream.gcount() << ", buf: " << buf << std::endl;
  istream.ignore(2); // 忽略2个字符
  std::cout << "gcount: " << istream.gcount() << std::endl;
  istream.read(buf, 4); // 读取4个字符
  buf[4] = '\0';
  std::cout << "gcount: " << istream.gcount() << ", buf: " << buf << std::endl;

}

/**
 * template <class charT, class traits = char_traits<charT> >  
 * class basic_streambuf;
 * 
 * @note 改模板类是所有流缓冲区的基类。
 * 
 * @note stream buffer用于管理stream的读写操作
 */
void basic_streambuf_test() {
#if 0
  // 无法直接构造basic_streambuf，因为它的构造函数是protected的
  protected:basic_streambuf();
#endif
  
  // 1. member types
  if(std::is_same<std::basic_streambuf<char>::char_type, char>::value) {
    std::cout << "std::streambuf::char_type is char" << std::endl;
  }
  if(std::is_same<std::basic_streambuf<char>::traits_type, std::char_traits<char>>::value) {
    std::cout << "std::streambuf::traits_type is std::char_traits<char>" << std::endl;
  }
  if(std::is_same<std::basic_streambuf<char>::int_type, int>::value) {
    std::cout << "std::streambuf::int_type is int" << std::endl;
  }
  if(std::is_same<std::basic_streambuf<char>::pos_type, std::streampos>::value) {
    std::cout << "std::streambuf::pos_type is streampos" << std::endl;
  }
  if(std::is_same<std::basic_streambuf<char>::off_type, std::streamoff>::value) {
    std::cout << "std::streambuf::off_type is streamoff" << std::endl;
  }

  // 2. constructor
#if 0
  // 无法直接构造basic_streambuf，因为它的构造函数是protected的
  protected:basic_streambuf();
  basic_streambuf (const basic_streambuf&) = delete;
#endif

  // 3. member functions
  /**
   * 1. locale
   *    - pubimbue
   *    - getloc
   * 2. buffer management
   *    - pubsetbuf
   *    - pubseekoff
   *    - pubseekpos
   *    - pubsync
   * 3. input
   *    - in_avail
   *    - sgetc
   *    - snextc
   *    - sbumpc
   *    - sgetn
   *    - sputbackc
   *    - sungetc
   * 4. output
   *    - sputc
   *    - sputn
   * 5. protected virtual functions
   */
}

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    int sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    std::uint32_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % 1000000000;
    return std::to_string(sec) + "." + std::to_string(ns) + ": ";
}

/**
 * @brief 默认情况下，std::cin和std::cerr是和std::cout绑定的。
 * 
 * @note 在默认情况下， cin和cout 之间存在⼀种绑定关系。
 * 这种绑定意味着，每当从cin 读取数据时，任何之前通过cout 输出的内容都会被强制刷新到屏幕上。
 * 这个机 制保证了输出内容能够⽴即显⽰给⽤⼾，这对于交互式程序⾮常有⽤。
 * 但是，这种绑定也 可能导致性能问题，特别是在需要频繁读取⼤量数据的情况下。
 * 这是因为每次从 cin 读 取数据都会触发⼀次输出缓冲区的刷新，即使实际上没有进⾏输出操作，也会浪费时间。
 */
void tie_test() {
    // 查看std::cin的tie()是否指向std::cout
    std::ostream* os = nullptr;
    os = std::cin.tie();
    if(os == &std::cout) {
        std::cout << "os == &std::cout" << std::endl;
    } else {
        std::cout << "os != &std::cout" << std::endl;
    }

    // 输入输出的buffer不是同一个
    std::streambuf* cout_rdbuf = std::cout.rdbuf();
    std::streambuf* cin_rdbuf = std::cin.rdbuf();
    if(cout_rdbuf == nullptr) {
        std::cout << "std::cout.rdbuf() == nullptr" << std::endl;
    } else {
        std::cout << "std::cout.rdbuf() != nullptr" << std::endl;
    }
    if(cin_rdbuf == nullptr) {
        std::cout << "std::cin.rdbuf() == nullptr" << std::endl;
    } else {
        std::cout << "std::cin.rdbuf() != nullptr" << std::endl;
    }
    printf("std::cout.rdbuf() = %p\n", cout_rdbuf);  // 0x7f1e420d8ea0
    printf("std::cin.rdbuf() = %p\n", cin_rdbuf);  // 0x7f1e420d8e40

    printf("%sbefore tie null\n", get_current_time().c_str());

    // 清除std::cin的tie()，由于std::cout.flush不会再被std::cin任何IO操作自动调用，则输出不会被打印
    std::cin.tie(0);
    os = std::cin.tie();
    if(os == nullptr) {
        std::cout << "os == nullptr" << std::endl;
    } else {
        std::cout << "os != nullptr" << std::endl;
    }

    // ?这句话还是能打印出来，很诧异
    std::cout << get_current_time() << "after tie null";

    std::string str;
    std::cin >> str;
    std::cout << get_current_time() << "std::cin = " << str << std::endl;
    std::cin.tie(&std::cout);  // 重新绑定std::cin和std::cout
}

/**
 * @brief std::ios_base::sync_with_stdio()函数用于控制C++标准输入输出流和C标准输入输出流之间的同步。
 * 
 * @note 在C++中，标准输⼊输出流如 cin 和 中，标准输⼊输出函数如 cout 是由C++的标准库提供的;⽽在C语⾔ scanf 和 printf 是由C标准库提供的。
 * 由于C++是从C 发展⽽来的语⾔，C++标准库的输⼊输出流系统需要与C标准库的输⼊输出系统兼容，以 确保在同⼀程序中能够混合使⽤C和C++的输⼊输出函数。
 * 为了实现这种兼容性，C++ 标准库默认会将 cin 、 cout 等C++流对象与stdin 、 stdout 等C标准库的流对象同步在⼀起。
 * 这种同步操作意味着每次使⽤cin 或 cout 时，都会⾃动刷新C标准库的缓冲区，以确保C++和C的I/O是⼀致的;
 */
void sync_test() {
    bool sync = std::ios_base::sync_with_stdio();
    if(sync) {
        std::cout << "std::ios_base::sync_with_stdio() == true" << std::endl;
    } else {
        std::cout << "std::ios_base::sync_with_stdio() == false" << std::endl;
    }
    std::cout << get_current_time() << "before: sync 1" << std::endl;
    printf("%sbefore: sync 2 ", get_current_time().c_str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << get_current_time() << "before: sync 3" << std::endl;

    // 关闭C++标准库和C标准库的同步
    // 这将使得C++的标准输入输出流和C的标准输入输出流不再同步。
    // 关闭同步后，C++的标准输入输出流将不再自动刷新C的标准输入输出流。
    // 这意味着在使用C++的标准输入输出流时，C的标准输入输出流可能不会立即刷新。
    // 这可以提高性能，特别是在需要频繁进行输入输出操作的情况下。
    // 但是需要注意，这可能会导致C++和C的输入输出流之间的数据不一致。
    std::ios_base::sync_with_stdio(false);

    sync = std::ios_base::sync_with_stdio();
    if(sync) {
        std::cout << "std::ios_base::sync_with_stdio() == true" << std::endl;
    } else {
        std::cout << "std::ios_base::sync_with_stdio() == false" << std::endl;
    }

    std::cout << get_current_time() << "after: sync 4 " << std::endl;
    printf("%safter: sync 5", get_current_time().c_str());

    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("%safter: sync 6\n", get_current_time().c_str());
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::ios_base::sync_with_stdio(true);  // 恢复同步
}

int main() {
    std::cout << "======================ios_base_example=========================" << std::endl;
    ios_base_example();
    std::cout << "======================basic_ios_example=========================" << std::endl;
    basic_ios_example();
    std::cout << "======================basic_streambuf_test=========================" << std::endl;
    basic_streambuf_test();
    std::cout << "======================basic_istream_test=========================" << std::endl;
    basic_istream_test();
    std::cout << "======================tie_test=========================" << std::endl;
    tie_test();
    std::cout << "======================sync_test=========================" << std::endl;
    sync_test();

    return 0;
}