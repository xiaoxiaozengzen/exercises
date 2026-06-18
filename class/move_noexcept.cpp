#include <iostream>
#include <vector>

/**
 * 类的移动构造和移动赋值操作符可以被标记为noexcept，以指示它们不会抛出异常。
 * 这对于性能优化非常重要，因为它允许标准库在需要移动对象时使用更高效的移动操作，而不是退回到复制操作。
 * 对于STL(特别是vector)来说，如果移动构造函数或移动赋值操作符被标记为noexcept，STL会优先使用它们来移动元素，而不是复制元素。
 * 如果移动操作可能抛出异常，STL会退回到复制操作，这可能会导致性能下降，特别是在处理大量元素时。
 * 因此，在设计类时，如果移动构造函数和移动赋值操作符不会抛出异常，应该将它们标记为noexcept，以便STL能够优化性能。
 */

class A {
public:
    A(int a) : a(a) {
        std::cout << "A Constructor" << std::endl;
    }

    ~A() {
        std::cout << "A Destructor" << std::endl;
    }

    A(const A& other) : a(other.a) {
        std::cout << "A Copy Constructor" << std::endl;
    }

    A& operator=(const A& other) {
        std::cout << "A Copy Assignment Operator" << std::endl;
        if (this != &other) {
            a = other.a;
        }
        return *this;
    }

    A(A&& other) noexcept : a(other.a) {
        std::cout << "A Move Constructor" << std::endl;
        other.a = 0;
    }

    A& operator=(A&& other) noexcept {
        std::cout << "A Move Assignment Operator" << std::endl;
        if (this != &other) {
            a = other.a;
            other.a = 0;
        }
        return *this;
    }

private:
    int a = 0;
};

class B {
public:
    B(int b):b(b) {
        std::cout << "B Constructor" << std::endl;
    }

    ~B() {
        std::cout << "B Destructor" << std::endl;
    }

    B(const B& other) : b(other.b) {
        std::cout << "B Copy Constructor" << std::endl;
    }

    B& operator=(const B& other) {
        std::cout << "B Copy Assignment Operator" << std::endl;
        if (this != &other) {
            b = other.b;
        }
        return *this;
    }

    B(B&& other) : b(other.b) {
        std::cout << "B Move Constructor" << std::endl;
        other.b = 0;
    }

    B& operator=(B&& other) {
        std::cout << "B Move Assignment Operator" << std::endl;
        if (this != &other) {
            b = other.b;
            other.b = 0;
        }
        return *this;
    }

private:
    int b = 0;
};

void with_noexcept() {
    std::vector<A> vec(4, 0);
    std::cout << "+++++1" << std::endl;

    vec.emplace_back(5);
    vec.emplace_back(6);
    std::cout << "+++++2" << std::endl;

}

void with_no_noexcept() {
    std::vector<B> vec(4, 0);
    std::cout << "+++++1" << std::endl;

    vec.emplace_back(5);
    vec.emplace_back(6);
    std::cout << "+++++2" << std::endl;
}

int main() {
    std::cout << "---------------------- with_noexcept ----------------------" << std::endl;
    with_noexcept();
    std::cout << "---------------------- with_no_noexcept ----------------------" << std::endl;
    with_no_noexcept();

    return 0;
}