#include <iostream>
#include <forward_list>

// template<
//     class T,
//     class Alloc = std::allocator<T>
// > class forward_list;

class A {
public:
    A() {
        std::cout << "construct" << std::endl;
    }

    explicit A(std::string a):a(a) {
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
    std::string a = "";
};

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
}