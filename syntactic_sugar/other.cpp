#include <iostream>

struct Werid {
    Werid& operator=(int) {return *this;}
    operator bool() { return false; }
};

void if_declare() {
    auto fun = [](int in)->int {
        return in;
    };

    /**
     * @brief condition with declaration
     * @note 1.声明了一个新的变量，并初始化它
     *       2.条件判断会判断变量本身
     *       3.变量的作用域只限于条件判断
     */
    if(auto a = fun(10)) {
        std::cout << "true: auto a = fun(10) is " << (a?"true":"false") << std::endl;
    } else {
        std::cout << "false: auto a = fun(10) is " << (a?"true":"false") << std::endl;
    }

    if(auto a = fun(0)) {
        std::cout << "true: auto a = fun(0) is " << (a?"true":"false") << std::endl;
    } else {
        std::cout << "false: auto a = fun(0) is " << (a?"true":"false") << std::endl;
    }

    if(auto a = false) {
        std::cout << "true: auto a = false is " << (a?"true":"false") << std::endl;
    } else {
        std::cout << "false: auto a = false is " << (a?"true":"false") << std::endl;
    }

    /**
     * @brief 对于一个赋值表达式:
     * @note 1.赋值会先执行，即变量会被赋值 2.然后赋值表达式的结果就等价于赋值后的变量
     */
    Werid a;
    if(a = 10) {
        std::cout << "true: a = false is " << (a?"true":"false") << std::endl;
    } else {
        std::cout << "false: a = false is " << (a?"true":"false") << std::endl;
    }
}

int main() {
    std::cout << "================ if_declare ================" << std::endl;
    if_declare();

    return 0;
}