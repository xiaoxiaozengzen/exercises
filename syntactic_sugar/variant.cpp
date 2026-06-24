#include <valarray>
#include <variant>
#include <string>
#include <iostream>
#include <vector>

/**
 * 类型安全的联合体
 * template <class...Types>
 * class variant;
 */

struct NoCon {
    NoCon(int a):a(a) {}
    
    int a = 0;
};

struct NoCon2 {
    NoCon2(int a):a(a) {}
    
    int a = 0;
};

struct MulCon {
    int a;
    int b;
    int c;

    MulCon(int a, int b, int c):a(a),b(b),c(c) {}
};

struct NoCopy {
    int a;
    NoCopy(int a):a(a){}
    NoCopy(const NoCopy& other) = delete;
    NoCopy& operator=(const NoCopy& other) = delete;
    NoCopy(NoCopy&& other) = delete;
    NoCopy& operator=(NoCopy&& other) = delete;
};

void ConFun() {
    // 1.默认构造函数，会使用第一个类型做值初始化
    // 需要第一个参数类型有默认构造函数
    std::variant<int, std::string> var0;
#if 0
    // 编译报错
    std::variant<NoCon, int> var0_0;
#endif

    // 2.拷贝构造和移动构造需要所有类型都满足拷贝和移动

    // 3.转换构造，编译器选择一个最佳匹配的类型，然后构造它
    std::variant<std::string, double, int> var1_0 = 10;
    std::variant<std::string, double, int> var1_1 = "str";
    std::variant<std::string, double, int> var1_2 = 11.0;
    // 3.1 注意隐式转换
    std::variant<double, int> var1_3 = 1.0f;
    // 3.2.有重复的类型，需要使用in_place按照下表指出
#if 0
    // error: conversion from ‘int’ to non-scalar type ‘std::variant<int, int>’ requested
    std::variant<int, int> var1_4 = 10;
#endif

    // 4.按照类型构造
    std::variant<std::string, double, int> var2_0{std::in_place_type<std::string>, "str"};
    // 4.1. 直接构造，少一个拷贝
    std::variant<MulCon, int> var2_1{std::in_place_type<MulCon>, 1, 2, 3};
    
    // 5. in_place_index
    // 5.1. 适合有重复类型的情况
    std::variant<int, int> var1_5{std::in_place_index<0>, 10};
    
}

void MemFun() {
    std::variant<std::string, double, int> var1{std::in_place_type<std::string>, 10, 42};
    std::variant<std::string, double, int> var2{std::in_place_type<double>, 10.9};
    std::variant<std::string, std::string> var3{std::in_place_index<1>, "STR", 1};

    // 1.Observers
    std::cout << "===== Observers =====\n";
    std::size_t index = var1.index();
    std::cout << "index: " << var1.index() << ", " << var2.index() << ", " << var3.index() << std::endl;
    if(var1.valueless_by_exception()) {
        std::cout << "valueless_by_exception\n";
    }
    bool result = var1.valueless_by_exception();
    std::cout << "valueless_by_exception: " << (result?"true":"false") << std::endl;

    // 2. Modifiers
    // 2.1. emplace
    std::cout << "===== emplace =====\n";
    double ret = var1.emplace<double>(10.9);
    std::cout << "emplace: " << ret << ", index: " << var1.index() << std::endl;
    std::string ret2 = var1.emplace<std::string>("STR");
    std::cout << "emplace: " << ret2 << ", index: " << var1.index() << std::endl;
    ret2 = var1.emplace<std::string>("ABCDEF", 2);
    std::cout << "emplace: " << ret2 << ", index: " << var1.index() << std::endl;
    int ret3 = var1.emplace<2>(10);
    std::cout << "emplace: " << ret3 << ", index: " << var1.index() << std::endl;
    std::variant_alternative_t<1, decltype(var1)> ret4 = var1.emplace<1>(11);
    std::cout << "emplace: " << ret4 << ", index: " << var1.index() << std::endl;
}

void NonMemFun() {
    std::variant<std::string, double, int> var1{std::in_place_type<std::string>, 10, 'a'};
    std::variant<std::string, double, int> var2;

    // 1. visit
    std::cout << "===== visit =====\n";
    std::visit([](auto&& arg) {
        std::cout << "arg: " << arg << std::endl;
    }, var1);
    var2.emplace<int>(10);
    std::visit([](auto&& arg, auto&& arg2) {
        std::cout << "arg: " << arg << ", arg2: " << arg2 << std::endl;
    }, var1, var2);
    
    // 2. holds_alternative
    std::cout << "===== holds_alternative =====\n";
    bool ret = std::holds_alternative<std::string>(var1);
    if(ret) {
        std::cout << "holds_alternative string: " << ret << std::endl;
    } else {
        std::cout << "holds_alternative string: " << ret << std::endl;
    }
    ret = std::holds_alternative<double>(var1);
    if(ret) {
        std::cout << "holds_alternative double: " << ret << std::endl;
    } else {
        std::cout << "holds_alternative double: " << ret << std::endl;
    }

    // 3. get
    std::cout << "===== get =====\n";
    std::variant_alternative_t<0, decltype(var1)> ret2 = std::get<0>(var1);
    std::cout << "get: " << ret2 << std::endl;
#if 0
    // std::bad_variant_access
    int ret3_1 = std::get<2>(var1);
    std::cout << "get: " << ret3_1 << std::endl;
#endif
    std::string ret3 = std::get<std::string>(var1);
    std::cout << "get: " << ret3 << std::endl;

    // 4. get_if
    std::cout << "===== get_if =====\n";
    std::variant_alternative_t<0, decltype(var1)>* ret4 = std::get_if<0>(&var1);
    if(ret4) {
        std::cout << "get_if: " << *ret4 << ", index: " << var1.index() << std::endl;
    } else {
        std::cout << "get_if: nullptr, index: " << var1.index() << std::endl;
    }
    std::variant_alternative_t<1, decltype(var1)>* ret5 = std::get_if<1>(&var1);
    if(ret5) {
        std::cout << "get_if: " << *ret5 << ", index: " << var1.index() << std::endl;
    } else {
        std::cout << "get_if: nullptr, index: " << var1.index() << std::endl;
    }
}

void helper_calss() {
    // 1. monostate，用于类型没有默认构造函数的情况
    std::cout << "===== monostate =====\n";
    std::variant<std::monostate, NoCon, int> var1;
    std::cout << "index: " << var1.index() << std::endl;
    var1.emplace<NoCon>(10);
    std::variant_alternative_t<1, decltype(var1)> ret1 = std::get<1>(var1);
    std::cout << "get: " << ret1.a << ", index: " << var1.index() << std::endl;
    std::variant<std::monostate, NoCon, std::monostate, NoCon2, int> var2;
    var2.emplace<NoCon2>(20);
    std::variant_alternative_t<3, decltype(var2)> ret2 = std::get<3>(var2);
    std::cout << "get: " << ret2.a << ", index: " << var2.index() << std::endl;

    // 2. variant_size，获取variant中类型的个数
    std::cout << "===== variant_size =====\n";
    std::cout << "variant_size: " << std::variant_size<decltype(var1)>::value << std::endl;
    std::cout << "variant_size: " << std::variant_size_v<decltype(var2)> << std::endl;

    // 3. variant_alternative，获取variant中指定索引的类型
    std::cout << "===== variant_alternative =====\n";
    if(std::is_same<int, std::variant_alternative<1, decltype(var1)>::type>::value) {
        std::cout << "variant_alternative: int" << std::endl;
    } else {
        std::cout << "variant_alternative: not int" << std::endl;
    }
    if(std::is_same<NoCon2, std::variant_alternative_t<3, decltype(var2)>>::value) {
        std::cout << "variant_alternative: NoCon2" << std::endl;
    } else {
        std::cout << "variant_alternative: not NoCon2" << std::endl;
    }
}

int main() {
    std::cout << "===== Constructor =====\n";
    ConFun();
    std::cout << "===== Member Function =====\n";
    MemFun();
    std::cout << "===== Non-Member Function =====\n";
    NonMemFun();
    std::cout << "===== Helper Class =====\n";
    helper_calss();

    return 0;
}