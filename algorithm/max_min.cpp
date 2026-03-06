#include <iostream>
#include <vector>
#include <algorithm>

/**
 * template <class T> 
 * const T& max (const T& a, const T& b);
 *
 * template <class T, class Compare>  
 * const T& max (const T& a, const T& b, Compare comp);
 *
 * template <class T> 
 * T max (initializer_list<T> il);
 *
 * template <class T, class Compare> 
 * T max (initializer_list<T> il, Compare comp);
 *
 * @note 对于1）2）返回 a和b中较大的一个，如果相等则返回a
 * @note 对于3）4）返回il中最大的一个元素，如果有多个相等的最大元素，则返回第一个
 * @note 默认使用operator<进行比较，也可以自定义比较函数
 */
void max_example() {
    int a = 10;
    int b = 20;
    std::cout << "max(a, b) = " << std::max(a, b) << std::endl;

    auto my_less = [](const double& x, const double& y) { return static_cast<int>(x) < static_cast<int>(y); };
    double c = 10.5;
    double d = 10.6;
    std::cout << "max(c, d) = " << std::max(c, d) << std::endl;
    std::cout << "max(c, d, my_less) = " << std::max(c, d, my_less) << std::endl;

    // 不一样的类型
    double e = 10.5;
    int f = 10;
#if 0
    // 编译报错，因为std::max要求两个参数必须是同一类型
    std::cout << "max(e, f) = " << std::max(e, f) << std::endl;
    std::cout << "max(f, e) = " << std::max(f, e) << std::endl;
#endif
    
}

int main() {
    std::cout << "=============== max_example ===============" << std::endl;
    max_example();

    return 0;
}