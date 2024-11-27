#include <map>
#include <iostream>
#include <functional>
#include <utility>
#include <memory>

// template<
//     class Key,                                              // map::key_type
//     class T,                                                // map::mapped_type
//     class Compare = std::less<Key>,                         // map::key_compare
//     class Alloc = std::allocator<std::pair<const Key,T>>    // map::allocator_type           
// > class map;

/**
 * note: Maps are typically implemented as binary search trees.
 */

class A {
public:
    A() {
        std::cout << "construct" << std::endl;
    }
    explicit A(int a):a(a) {
        std::cout << "another construct" << std::endl;
    }
    ~A() {
        std::cout << "deconstruct" << std::endl;
    }

    A(const A& other) {
        std::cout << "copy construct" << std::endl;
        this->a = other.a;
    }

    A& operator=(const A& other) {
        std::cout << "copy assign construct" << std::endl;
        this->a = other.a;
        return *this;
    }

    A(A&& other) {
        std::cout << "move construct" << std::endl;
        this->a = other.a;
    }

    A& operator=(A&& other) {
        std::cout << "move assign construct" << std::endl;
        this->a = other.a;
        return *this;
    }

    bool operator<(const A &a) const {
      std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
      return this->a < a.a;
    }

    friend std::ostream& operator<<(std::ostream &output, const A &a) { 
        output << a.a;
        return output;            
    }

    bool operator==(const A &a) const {
      std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
      return this->a == a.a;
    }

public:
    int a = 0;
};

void BasicSetMemberTypes() {
    std::map<double, int> map1;
    if(std::is_same<std::map<double, int>::key_type, double>::value) {
        std::cout << "map::key_type is double" << std::endl;
    }
    if(std::is_same<std::map<double, int>::mapped_type, int>::value) {
        std::cout << "map::mapped_type is int" << std::endl;
    }
    if(std::is_same<std::map<double, int>::value_type, std::pair<double, int>>::value) {
        std::cout << "map::value_type is std::pair<double, int>" << std::endl;
    }
}

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
    BasicSetMemberTypes();
}