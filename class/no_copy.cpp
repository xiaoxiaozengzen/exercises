#include <iostream>
#include <utility>

class BaseCopyable {
public:
    BaseCopyable() {
        std::cout << "BaseCopyable constructed" << std::endl;
    }

    BaseCopyable(const BaseCopyable&) {
        std::cout << "BaseCopyable copy constructor" << std::endl;
    }
    BaseCopyable& operator=(const BaseCopyable&) {
        std::cout << "BaseCopyable copy assignment" << std::endl;
        return *this;
    }

    BaseCopyable(BaseCopyable&&) noexcept {
        std::cout << "BaseCopyable move constructor" << std::endl;
    }
    BaseCopyable& operator=(BaseCopyable&&) noexcept {
        std::cout << "BaseCopyable move assignment" << std::endl;
        return *this;
    }

    ~BaseCopyable() {
        std::cout << "BaseCopyable destructed" << std::endl;
    }
};

class BaseNonCopyable {
public:
    BaseNonCopyable() {
        std::cout << "BaseNonCopyable constructed" << std::endl;
    }

    BaseNonCopyable(const BaseNonCopyable&) = delete;
    BaseNonCopyable& operator=(const BaseNonCopyable&) = delete;

    BaseNonCopyable(BaseNonCopyable&&) = delete;
    BaseNonCopyable& operator=(BaseNonCopyable&&) = delete;

    ~BaseNonCopyable() {
        std::cout << "BaseNonCopyable destructed" << std::endl;
    }
};

class DerivedCopyable : public BaseCopyable {
public:
    DerivedCopyable() = default;

    DerivedCopyable(const DerivedCopyable& other) : BaseCopyable(other) {
        std::cout << "DerivedCopyable copy constructor" << std::endl;
        value = other.value;
    }

    DerivedCopyable(DerivedCopyable&& other) noexcept : BaseCopyable(std::move(other)) {
        std::cout << "DerivedCopyable move constructor" << std::endl;
        value = other.value;
    }

    DerivedCopyable& operator=(const DerivedCopyable& other) {
        if (this != &other) {
            BaseCopyable::operator=(other);
            value = other.value;
        }
        std::cout << "DerivedCopyable copy assignment" << std::endl;
        return *this;
    }

    int value = 0;
};

class DerivedNonCopyable : public BaseNonCopyable {
public:
    int value = 0;
};

class DerivedNonCopyable2 : public BaseNonCopyable {
public:
    DerivedNonCopyable2() : BaseNonCopyable() {
        std::cout << "DerivedNonCopyable2 constructed" << std::endl;
    }

    ~DerivedNonCopyable2() {
        std::cout << "DerivedNonCopyable2 deconstructed" << std::endl;
    }

    DerivedNonCopyable2(const DerivedNonCopyable2& other) {
        std::cout << "DerivedNonCopyable2 copy constructed" << std::endl;
        value = other.value;
    }

    DerivedNonCopyable2& operator=(const DerivedNonCopyable2& other) {
        std::cout << "DerivedNonCopyable2 copy assignment" << std::endl;
        this->value = other.value;
        return *this;
    }

public:
    int value = 0;
};

/**
 * 关于子类的拷贝/移动：
 * 1.默认拷贝/移动
 *  - 如果父类允许拷贝/移动，子类也默认可以拷贝/移动。
 *  - 会先对父类部分进行处理(拷贝/移动)，再处理子类自己的成员
 * 2.父类禁止拷贝/移动
 *  - 如果父类把复制或移动函数删掉了，那么子类默认的拷贝/移动也会被禁止。
 * 3.子类自己显式写了拷贝/移动构造
 *  - 子类自己决定怎么做
 * 4.需要注意切片(slice)问题
 *
 * 核心原则：
 *  - 父类负责“自己的那一层”
 *  - 子类负责“自己的那一层”
 *  - 拷贝/移动时，先处理父类，再处理子类
 */
void copyalbe_test() {
    std::cout << "--- copy/move enabled base ---" << std::endl;
    std::cout << "+++++" << std::endl;
    DerivedCopyable a;
    a.value = 10;
    std::cout << "+++++" << std::endl;
    DerivedCopyable b = a;      // copy
    std::cout << "+++++" << std::endl;
    DerivedCopyable c = std::move(a);  // move
    std::cout << "+++++" << std::endl;

    std::cout << "b.value = " << b.value << std::endl;
    std::cout << "c.value = " << c.value << std::endl;

    std::cout << "--- non-copyable/non-movable base ---" << std::endl;
    DerivedNonCopyable d;
    d.value = 20;

#if 0
    // 下面这两行都会编译失败：
    //  use of deleted function ‘DerivedNonCopyable::DerivedNonCopyable(const DerivedNonCopyable&)’
    DerivedNonCopyable e = d;
    // use of deleted function ‘DerivedNonCopyable::DerivedNonCopyable(DerivedNonCopyable&&)’
    DerivedNonCopyable f = std::move(d);
#endif

    std::cout << "--- non-copyable/non-movable base with custom ---" << std::endl;
    DerivedNonCopyable2 e;
    std::cout << "+++++" << std::endl;
    DerivedNonCopyable2 e1 = e;
    std::cout << "+++++" << std::endl;
    e1 = e;
    std::cout << "+++++" << std::endl;
    std::cout << "DerivedNonCopyable object created successfully" << std::endl;
}

int main() {
    std::cout << "================== copyalbe_test ==================" << std::endl;
    copyalbe_test();

    return 0;
}