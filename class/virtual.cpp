#include <stdio.h>

#include <iostream>

class A {
public:
    void fun1() {
        std::cout << "A::fun1" << std::endl;
    }

    virtual void fun2() {
        std::cout << "virtual A::fun2" << std::endl;
    }

    virtual void fun3() {
        std::cout << "virtual A::fun3" << std::endl;
    }

    virtual void fun4(int d) {
        std::cout << "virtual A::fun4: " << d << std::endl;
    }
public:
    int a;
    char b;
};

class AA {
public:
    void fun1() {
        std::cout << "AA::fun1" << std::endl;
    }
public:
    int a;
    char b;
};

typedef void(*Fun1)();
typedef void(*Fun2)(int);

void fun() {
    std::cout << "fun" << std::endl;
}

void ptr_array() {
    int a[10] = {1, 2, 3, 4, 5, 6 ,7 ,8 ,9, 0};
    printf("a :%p\n", a);
    printf("a[0]: %p, %d  %d\n", &a[0], a[0], *(int*)&a);
}

void virtual_tabel() {
    std::cout << "sizeof A:" <<sizeof(A) << std::endl;
    std::cout << "sizeof AA:" <<sizeof(AA) << std::endl;

    // 函数指针使用
    Fun1 f = fun;
    f();
    printf("f1 address: %p\n", f);
    printf("fun address: %p\n", fun);

    A a;
    A a1;
    printf("a: &vptr=%p, * vptr=%p\n", (long long*)&a, *(long long*)&a);
    printf("a1: &vptr=%p, * vptr=%p\n", (long long*)&a1, *(long long*)&a1);

    auto * vptr = (long long*)&a;
    auto * vtabel = (long long*)*vptr;
    printf("vptr=%p, vtabel=%p\n", vptr, vtabel);
    printf("*vtabel=%p\n", *vtabel);
    printf("*vtabel2=%p\n", *(vtabel + 1));
    Fun1 fu1 = (Fun1)*vtabel;
    fu1();
    Fun1 fu2 = (Fun1)*(vtabel + 1);
    fu2();
    Fun2 fu3 = (Fun2)*(vtabel + 2);
    fu3(10);

    printf("fun1() %p\n", *(long long*)*(long long*)&a);
    printf("fun1() %p\n", (void*)&A::fun2);
    Fun1 f1 = (Fun1)(void*)&A::fun2;
    f1();
    f1 = (Fun1)*(long long*)*(long long*)&a;
    f1();
}

class Base {
public:
    Base() {
        std::cout << "Base construct" << std::endl;
    }

    // 不为虚函数，则多态的时候只调用父类的析构，造成内存泄漏
    virtual ~Base() {
        std::cout << "Base deconstruct" << std::endl;
    }

    void first() {
        std::cout << "Base::first" << std::endl;
    }

    virtual void second() {
        std::cout << "Base::second" << std::endl;
    }

    virtual void third() {
        std::cout << "Base::third: " << this->a << std::endl;
    }

    // 协变，即基类的虚函数返回基类对象的指针或者引用，派生类虚函数返回派生类对象的指针或者引用
    virtual Base& re() {
        return *this;
    }
public:
    int a = 10;
    int b = 11;
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived construct" << std::endl;
    }

    ~Derived() {
        std::cout << "Derived deconstruct" << std::endl;
    }
    int first() {
        std::cout << "Derived::first" << std::endl;
    }

    virtual void second() {
        std::cout << "Derived::second" << std::endl;
    }

    void third() {
        std::cout << "Derived::third:" << this->a << std::endl;
    }

    Derived& re() {
        return *this;
    }
public:
    int a = 12;
    int c = 13;
};

class DerivedOther {
public:
    virtual int first() {
        std::cout << "DerivedOther::first" << std::endl;
    }
};

/**
多重集成的情况下，包含两个虚函数表了
 */
class DerivedEnd : public Derived, public DerivedOther{
public:
    virtual int first() {
        std::cout << "DerivedEnd::first" << std::endl;
    }
};

/**
多态的两个条件：1.虚函数重写 2.必须通过基类的指针或者引用调用虚函数。
 */
void duotai_example() {
    Base * b = new Derived;
    b->first();
    b->second();
    b->third();

    // 多态中：成员变量编译和运行的时候都以父类为准
    std::cout << "b->a: " << b->a << std::endl;
    std::cout << "b->b: " << b->b << std::endl;
    delete b;

    std::cout << "sizeof(Base): " << sizeof(Base) 
    << ", sizeof(Derived): " << sizeof(Derived)
    << ", sizeof(DerivedOther): " << sizeof(DerivedOther)
    << ", sizeof(DerivedEnd): " << sizeof(DerivedEnd)
    << std::endl;
}

int main() {
    std::cout << "=================ptr_array===============" << std::endl;
    ptr_array();
    std::cout << "=================virtual_tabel()===============" << std::endl;
    virtual_tabel();
    std::cout << "=================duotai_example()===============" << std::endl;
    duotai_example();
}