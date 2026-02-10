#include <filesystem>
#include <iostream>

/**
 * @brief 一个字符串路径，表示一个文件系统中的路径，可以不存在
 * @details 这个路径可以是：
 * - 文件的绝对位置：/home/user/file.txt
 * - 路径的绝对位置：/home/user
 * - 零个或者多个一下组合：
 *   - . 当前路径
 *   - .. 上级路径
 *   - 其他路径，其中多个连续的///会被当成一个/，
 */
void path_example() {
    // 1. 构造函数
    std::filesystem::path p1;
    std::filesystem::path p2("/mnt/workspace/cgz_workspace/Exercise/exercises/syntactic_sugar/input/test.txt");
    // 对于posix，native_format和generic_format是一样的
    std::filesystem::path p3("/mnt/workspace/cgz_workspace/Exercise/exercises/syntactic_sugar/input/test.txt", std::filesystem::path::format::generic_format);
    std::filesystem::path p4(p2);

    // 2. 成员函数

}

void fun_example() {
    /********************** 1. create_directory **********************/
    bool ret = std::filesystem::create_directory("/tmp/test");
    if(!ret) {
        std::cout << "create_directory failed" << std::endl;
    } else {
        std::cout << "create_directory success" << std::endl;
    }

    std::error_code ec;
    ret = std::filesystem::create_directory("/tmp/test", ec);
    if(!ret) {
        std::cout << "create_directory failed: " << ec.message() << std::endl;
    } else {
        std::cout << "create_directory success" << std::endl;
    }

    // 不能递归创建目录，否则抛出异常并终止程序，生成core文件
    try {
        ret = std::filesystem::create_directory("/tmp/test/test1/test2");
        if(!ret) {
            std::cout << "create_directory failed" << std::endl;
        } else {
            std::cout << "create_directory success" << std::endl;
        }
    } catch(const std::filesystem::filesystem_error& e) {
        std::cout << "create_directory failed: " << e.what() << std::endl;
    }

    // 不能递归创建目录，否则返回false，并设置错误码 
    ret = std::filesystem::create_directory("/tmp/test/test1/test2", ec);
    if(!ret) {
        std::cout << "create_directory failed: " << ec.message() << std::endl;
    } else {
        std::cout << "create_directory success" << std::endl;
    }
}

int main() {
    std::cout << "=================== path_example ==================" << std::endl;
    path_example();
    std::cout << "=================== fun_example ==================" << std::endl;
    fun_example();

    return 0;
}