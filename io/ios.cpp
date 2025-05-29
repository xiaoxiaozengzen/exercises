#include <ios>
#include <iostream>
#include <thread>
#include <chrono>

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

    printf("before tie null");

    // 清除std::cin的tie()，由于std::cout.flush不会再被std::cin任何IO操作自动调用，则printf("789")不会被打印，因为printf跟std::cout公用一个缓冲区
    std::cin.tie(0);

    // ?这句话还是能打印出来，很诧异
    printf("after tie null");

    std::string str;
    std::cin >> str;
    std::cout << get_current_time() << "str = " << str << std::endl;
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
    std::cout << "======================tie_test=========================" << std::endl;
    tie_test();
    std::cout << "======================sync_test=========================" << std::endl;
    sync_test();
    std::cout << "======================end=========================" << std::endl;

    return 0;
}