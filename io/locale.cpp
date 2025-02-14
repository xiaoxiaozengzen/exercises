#include <iostream>
#include <locale>
#include <type_traits>
#include <string>

class MyFacet : public std::locale::facet {
public:
    MyFacet(std::size_t refs) : std::locale::facet(refs) {}
    ~MyFacet() {}
    static std::locale::id id;
};

void MemType() {
    if(std::is_same<std::locale::category, int>::value) {
        std::cout << "std::locale::category is int" << std::endl;
    } else {
        std::cout << "std::locale::category is not int" << std::endl;
    }
    if(std::is_same<std::locale::id, int>::value) {
        std::cout << "std::locale::id is int" << std::endl;
    } else {
        std::cout << "std::locale::id is not int" << std::endl;
    }
    if(std::is_same<std::locale::facet, int>::value) {
        std::cout << "std::locale::facet is int" << std::endl;
    } else {
        std::cout << "std::locale::facet is not int" << std::endl;
    }
}

void Confun() {
    std::locale loc = std::locale();
    std::locale loc2(loc);
    std::locale loc3("en_US.UTF8");
    std::locale loc4 = std::locale(loc3, "", std::locale::ctype);

    // std::locale::facet *f = new MyFacet(0);
    // std::locale loc5(loc4, &f);

    std::cout << "loc: constructor" << std::endl;
}

void MemFun() {
    std::locale loc = std::locale::classic(); // 等价于 std::locale loc("C");

    std::locale loc2("");
    loc2 = loc2.combine<std::num_put<char>>(std::locale::classic());

    std::locale loc3("C");
    loc3.global(std::locale(""));
    std::locale loc4("C");
    std::cout << "loc3 == loc4: " << ((loc3 == loc4)?"True":"False") << std::endl;

    std::locale loc5("");
    std::string name = loc5.name();
    std::cout << "loc5.name(): " << name << std::endl;

    std::cout << "MemFun" << std::endl;
}

int main() {
    std::cout << "======================MemType======================" << std::endl;
    MemType();
    std::cout << "======================Confun======================" << std::endl;
    Confun();
    std::cout << "======================MemFun======================" << std::endl;
    MemFun();
}