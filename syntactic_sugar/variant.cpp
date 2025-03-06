// template< class... Types >
// class variant;

#include <variant>
#include <string>
#include <iostream>
#include <vector>


void ConFun() {
    // value-initializes first alternative
    std::variant<int, std::string> var0;
 
    // initializes first alternative with std::string{"STR"};
    std::variant<std::string, int> var1{"STR"};
 
    // initializes second alternative with int == 42;
    std::variant<std::string, int> var2{42};

    // // ill-formed: no std::string constructor taking an int
    // std::variant<std::string, std::string> var3{"STR"};

    // initializes first alternative with 10个char== 'a';
    std::variant<std::string, double, int> var4{std::in_place_type<std::string>, 10, 42};
    // initializes second alternative with 10.9;
    std::variant<std::string, double, int> var5{std::in_place_type<double>, 10.9};

    // initializes second alternative with std::string{"STR"} and 1;
    std::variant<std::string, std::string> var6{std::in_place_index<1>, "STR", 1};
    
}

void MemFun() {
    std::variant<std::string, double, int> var1{std::in_place_type<std::string>, 10, 42};
    std::variant<std::string, double, int> var2{std::in_place_type<double>, 10.9};
    std::variant<std::string, std::string> var3{std::in_place_index<1>, "STR", 1};

    // 1.Observers
    std::size_t index = var1.index();
    std::cout << "index: " << var1.index() << ", " << var2.index() << ", " << var3.index() << std::endl;
    if(var1.valueless_by_exception()) {
        std::cout << "valueless_by_exception\n";
    }

    // 2. Modifiers
    double ret = var1.emplace<double>(10.9);
    std::cout << "emplace: " << ret << std::endl;
    std::string ret2 = var1.emplace<std::string>("STR");
    std::cout << "emplace: " << ret2 << std::endl;
    ret2 = var1.emplace<std::string>("ABCDEF", 2);
    std::cout << "emplace: " << ret2 << std::endl;
    int ret3 = var1.emplace<2>(10);
    std::cout << "emplace: " << ret3 << std::endl;
    std::variant_alternative_t<1, decltype(var1)> ret4 = var1.emplace<1>(11);
    std::cout << "emplace: " << ret4 << std::endl;
}

void NonMemFun() {
    std::variant<std::string, double, int> var1{std::in_place_type<std::string>, 10, 'a'};
    std::variant<std::string, double, int> var2;
    
    // holds_alternative
    bool ret = std::holds_alternative<std::string>(var1);
    if(ret) {
        std::cout << "holds_alternative: " << ret << std::endl;
    }
    ret = std::holds_alternative<std::string>(var2);
    if(ret) {
        std::cout << "var2 holds_alternative: " << ret << std::endl;
    } else {
        std::cout << "var2 holds_alternative: " << ret << std::endl;
    }
    std::size_t index = var2.index();
    std::cout << "index: " << index << std::endl;
    ret = var2.valueless_by_exception();
    if(ret) {
        std::cout << "valueless_by_exception\n";
    }

    // get
    // std::variant_alternative_t<1, decltype(var1)> ret2 = std::get<1>(var1); // terminate called after throwing an instance of 'std::bad_variant_access'
    std::variant_alternative_t<0, decltype(var1)> ret2 = std::get<0>(var1);
    std::cout << "get: " << ret2 << std::endl;
    std::string ret3 = std::get<std::string>(var1);
    std::cout << "get: " << ret3 << std::endl;

    // visit
    var2.emplace<int>(42);
    auto visitor = [](auto&& arg) {
        std::cout << "arg " << arg << std::endl;
    };
    auto visitor2 = [](auto&& arg1, auto&& arg2) {
        std::cout << "arg1 " << arg1 << ", arg2 " << arg2 << std::endl;
    };
    int ret4;
    auto visitor3 = [&](auto a) {
        if constexpr (std::is_same_v<int, decltype(a)>) {
            ret4 = a;
        } else {
            ret4 = 0;
        }
    };
    std::visit(visitor, var1);
    std::visit(visitor, var2);
    std::visit(visitor2, var1, var2);
    std::visit(visitor3, var2);
    std::cout << "visit: " << ret4 << std::endl;
}

int main() {
    std::cout << "===== Constructor =====\n";
    ConFun();
    std::cout << "===== Member Function =====\n";
    MemFun();
    std::cout << "===== Non-Member Function =====\n";
    NonMemFun();
    return 0;
}