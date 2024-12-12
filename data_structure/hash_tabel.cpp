#include <iostream>
#include <functional>

int main() {
    std::hash<std::string> hash_fn;
    std::cout << hash_fn("Hello, World!") << std::endl;
    return 0;
}