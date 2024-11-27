#include <iostream>
#include <utility>
#include <type_traits>
#include <tuple>

// template<
//     class T1,
//     class T2
// > struct pair;

void BasicSetMemberTypes() {
    std::pair<int, double> p1;
    if(std::is_same<std::pair<int, double>::first_type, int>::value) {
        std::cout << "pair::first_type is int" << std::endl;
    }
    if(std::is_same<std::pair<int, double>::second_type, double>::value) {
        std::cout << "pair::second_type is double" << std::endl;
    }
}

void Construct() {
    std::pair<int, double> p1;
    std::cout << "p1.first: " << p1.first << ", p1.second: " << p1.second << std::endl;
    std::pair<int, double> p2(1, 2.0);
    std::cout << "p2.first: " << p2.first << ", p2.second: " << p2.second << std::endl;
    std::pair<int, double> p3(p2);

    // template<class... Args1, class... Args2>
    // pair(piecewise_construct_t pwc, tuple<Args1...> first_args, tuple<Args2...> second_args);
    std::pair<int, double> p4(
        std::piecewise_construct,
        std::tuple<int>(1),
        std::tuple<double>(2.0)
    );
}

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
    BasicSetMemberTypes();
    std::cout << "--------------------------------Construct--------------------------------" << std::endl;
    Construct();
}