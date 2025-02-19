#include <ios>
#include <iostream>

int main() {
    // 查看std::cin的tie()是否指向std::cout
    std::ostream* os = nullptr;
    os = std::cin.tie();
    if(os == &std::cout) {
        std::cout << "os == &std::cout" << std::endl;
    } else {
        std::cout << "os != &std::cout" << std::endl;
    }

    // c和c++的输入输出流是否同步
    // 对于标准输出的加锁时机不同：printf在对标准输出作任何处理前先加锁；std::out在实际向标准输出打印时才加锁
    // 两者的缓存机制不同：printf无缓冲区，而std::cout有缓冲区
    bool sync = std::ios_base::sync_with_stdio();
    if(sync) {
        std::cout << "std::ios_base::sync_with_stdio() == true" << std::endl;
    } else {
        std::cout << "std::ios_base::sync_with_stdio() == false" << std::endl;
    }

    std::ios_base::sync_with_stdio(false);

    sync = std::ios_base::sync_with_stdio();
    if(sync) {
        std::cout << "std::ios_base::sync_with_stdio() == true" << std::endl;
    } else {
        std::cout << "std::ios_base::sync_with_stdio() == false" << std::endl;
    }

    std::cout << "123" << "456" << std::endl;
    printf("789");

    // 清除std::cin的tie()，由于std::cout.flush不会再被std::cin任何IO操作自动调用，则printf("789")不会被打印，因为printf跟std::cout公用一个缓冲区
    std::cin.tie(nullptr);
    std::string str;

    std::cin >> str;
    std::cout << "str = " << str << std::endl;
    return 0;

}