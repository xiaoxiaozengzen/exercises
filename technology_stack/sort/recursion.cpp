#include <iostream>

/**
 * 递归特点：
 * - 自身调用：原问题可以分解为子问题，子问题和原问题的求解方法是一致的，即都是调用自身的同一个函数。
 * - 终止条件：递归必须有一个明确的终止条件，否则会导致无限递归，最终引发栈溢出。
 *
 * 递归解题思路：
 * 1. 定义函数功能
 * 2. 确定终止条件
 * 3. 递推函数的等价关系式：递归的本义是原问题可以分解为子问题，子问题和原问题的求解方法是一致的，即都是调用自身的同一个函数。
 */

int Sum(int n) {
    if(n == 1) {
        return 1;
    } else {
        return n + Sum(n - 1);
    }

}

int main(int argc, char** argv) {
    std::cout << "Hello, Recursion!" << std::endl;

    int ret = Sum(5);
    std::cout << "Sum(5) = " << ret << std::endl;

    return 0;
}