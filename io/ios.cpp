#include <ios>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>

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

void ios_base_example() {
#if 0
    // ios_base的构造函数是protected的，不能直接创建对象
    protected: ios_base();ios_base (const ios_base&) = delete;
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
      * 2. failure： class failure;
      */
}

/**
 * template <class charT, class traits = char_traits<charT> >  
 * class basic_ios;
 * 
 * @brief 该类继承了ios_base。该类实现了和流类型无关的流操作。
 * @note ios_base实现了和字符类型无关的流操作，
 * @note 其中 using ios = basic_ios<char>;
 */
void basic_ios_example() {
    // 1. member types
    if(std::is_same<std::basic_ios<char>::char_type, char>::value) {
        std::cout << "std::basic_ios<char>::char_type is char" << std::endl;
    } else {
        std::cout << "std::basic_ios<char>::char_type is not char" << std::endl;
    }

    // 2, constructor
    /**
     * explicit basic_ios (basic_streambuf<char_type,traits_type>* sb);
     */

    // 3. member functions
    /**
     * 1. state flag fun
     *   - good
     *   - eof
     *   - fail
     *   - bad
     *   - rdstate
     *   - setstate
     *   - clear
     * 2. formatting fun
     *   - fill
     *   - copyfmt
     * 3. others
     *   - exception
     *   - imbue
     *   - tie
     *   - rdbuf
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

int main() {
    std::cout << "======================tie_test=========================" << std::endl;
    tie_test();
    std::cout << "======================sync_test=========================" << std::endl;
    sync_test();
    std::cout << "======================ios_base_example=========================" << std::endl;
    ios_base_example();
    std::cout << "======================basic_ios_example=========================" << std::endl;
    basic_ios_example();

    return 0;
}