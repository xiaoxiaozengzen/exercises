// template< class T >
// class optional;

// 该类型表示可能含有值，类似薛定谔的猫
// T必须是可以析构的，并且不能是array和reference

#include <iostream>
#include <optional>
#include <type_traits>

void MemType() {
  if(std::is_same<std::optional<int>::value_type, int>::value) {
    std::cout << "optional<int>::value_type is int" << std::endl;
  }
}

void ConFun() {
    std::optional<int> o1; // empty
    std::optional<int> o11(std::nullopt); // empty
    std::optional<int> o2 = 1; // init from rvalue
    std::optional<int> o3 = o2; // copy-constructor
 
    // calls std::string( initializer_list<CharT> ) constructor
    // struct in_place_t { explicit in_place_t() = default; };
    // inline constexpr in_place_t in_place{};
    std::optional<std::string> o4(std::in_place, {'a', 'b', 'c'});
 
    // calls std::string( size_type count, CharT ch ) constructor
    std::optional<std::string> o5(std::in_place, 3, 'A');
 
    // Move-constructed from std::string using deduction guide to pick the type
 
    std::optional o6(std::string{"deduction"});
 
    std::cout << *o2 << ' ' << *o3 << ' ' << *o4 << ' ' << *o5  << ' ' << *o6 << '\n';
}

void MemFun() {
    // operator*() and operator->() 
    std::optional<int> o1 = 1;
    int i = *o1;
    std::cout << "o1 = " << i << std::endl;
    int *p = o1.operator->();
    std::cout << "o1-> = " << *p << std::endl;
    std::optional<std::string> o2 = "abc";
    std::cout << "size = " << o2->size() << std::endl;

    // operator bool()
    std::optional<int> o3;
    if(o3) {
        std::cout << "o3 has value" << std::endl;
    } else {
        std::cout << "o3 is empty" << std::endl;
    }
    if(o1) {
        std::cout << "o1 has value" << std::endl;
    } else {
        std::cout << "o1 is empty" << std::endl;
    }

    // has_value()
    if(o3.has_value()) {
        std::cout << "o3 has value" << std::endl;
    } else {
        std::cout << "o3 is empty" << std::endl;
    }
    if(o1.has_value()) {
        std::cout << "o1 has value" << std::endl;
    } else {
        std::cout << "o1 is empty" << std::endl;
    }

    // value()
    std::optional<int> o4 = 4;
    int value = o4.value();
    std::cout << "o4 value = " << value << std::endl;
    try {
        std::optional<int> o5;
        int value = o5.value();
    } catch(const std::bad_optional_access& e) {
        std::cout << "o5 is empty" << std::endl;
    }

    // value_or()
    std::optional<int> o6;
    int value1 = o6.value_or(6);
    std::cout << "o6 value = " << value1 << std::endl;

    // swap()
    std::optional<int> o7 = 7;
    std::optional<int> o8 = 8;
    o7.swap(o8);
    std::cout << "o7 = " << *o7 << ", o8 = " << *o8 << std::endl;

    // reset()
    o7.reset();
    if(o7) {
        std::cout << "o7 has value" << std::endl;
    } else {
        std::cout << "o7 is empty" << std::endl;
    }

    // emplace()
    o7.emplace(7);
    std::cout << "o7 = " << *o7 << std::endl;
}

void NonMemFun() {
    std::optional<int> o1 = std::make_optional<int>(1);
    std::cout << "o1 = " << *o1 << std::endl;

    std::optional<int> o2;
    if(o2 == std::nullopt) {
        std::cout << "o2 is empty" << std::endl;
    } else {
        std::cout << "o2 has value" << std::endl;
    }
}

int main() {
    std::cout << "======================MemType======================" << std::endl;
    MemType();
    std::cout << "======================ConFun======================" << std::endl;
    ConFun();
    std::cout << "======================MemFun======================" << std::endl;
    MemFun();
    std::cout << "======================NonMemFun======================" << std::endl;
    NonMemFun();
    return 0;
}
