#include <iostream>
#include <sstream>

void Confun() {
    std::stringstream ss1;
    // std::stringstream ss2(ss1); // deleted function
    std::stringstream ss3(std::move(ss1));
    std::stringstream ss4("Hello");
}

void MemFun() {
    std::stringstream ss1("Hello");
    std::string ret = ss1.str();
    std::cout << "ss1.str() = " << ret << std::endl;
    ss1.str("World");
    ret = ss1.str();
    std::cout << "ss1.str() = " << ret << std::endl;
    std::stringstream ss2;
    ss2.swap(ss1);
    std::cout << "ss1.str() = " << ss1.str() << std::endl;
    std::cout << "ss2.str() = " << ss2.str() << std::endl;

    std::stringstream ss3;
    ss3 << ss2.rdbuf();
    std::string ret1 = ss3.str();
    std::cout << "ss3 << ss2.rdbuf() = " << ret1 << std::endl;
    std::stringstream ss4("Hello");
    ss4 >> ss3.rdbuf();
    ret1 = ss3.str();
    std::cout << "ss4 >> ss3.rdbuf() = " << ret1 << std::endl;
}

void Inherti_istream() {
    std::stringstream ss1("Hello");
    std::string ret;
    ss1 >> ret;
    std::cout << "ss1 >> ret = " << ret << std::endl;
    std::stringstream ss2("123");
    int num;
    ss2 >> num;
    std::cout << "ss2 >> num = " << num << std::endl;
    std::stringstream ss3("3.14");
    double dnum;
    ss3 >> dnum;
    std::cout << "ss3 >> dnum = " << dnum << std::endl;
    std::stringstream ss4("1");
    bool b;
    ss4 >> b;
    std::cout << "ss4 >> b = " << b << std::endl;
    std::stringstream ss5("123 456");
    int num1;
    int num2;
    ss5 >> num1;
    std::cout << "ss5 >> num1 = " << num1 << std::endl;
    ss5 >> num2;
    std::cout << "ss5 >> num2 = " << num2 << std::endl;
    std::stringstream ss7("Hello");
    ss7 >> ss2.rdbuf();
    ret = ss2.str();
    std::cout << "ss7 >> ss2.rdbuf() = " << ret << std::endl;
}

void Inherit_ostream() {
    std::stringstream ss1;
    ss1 << "Hello";
    std::string ret = ss1.str();
    std::cout << "ss1 << \"Hello\" = " << ret << std::endl;
    std::stringstream ss2;
    ss2 << 123;
    ret = ss2.str();
    std::cout << "ss2 << 123 = " << ret << std::endl;
    std::stringstream ss3;
    ss3 << 3.14;
    ret = ss3.str();
    std::cout << "ss3 << 3.14 = " << ret << std::endl;
    std::stringstream ss4;
    ss4 << true;
    ret = ss4.str();
    std::cout << "ss4 << true = " << ret << std::endl;
    std::stringstream ss5;
    ss5 << 123 << " " << 456;
    ret = ss5.str();
    std::cout << "ss5 << 123 << \" \" << 456 = " << ret << std::endl;
    std::stringstream ss6;
    ss6 << ss1.rdbuf();
    ret = ss6.str();
    std::cout << "ss6 << ss1.rdbuf() = " << ret << std::endl;
}

void inherit_ios() {
    std::stringstream ss1("Hello");
    bool good = ss1.good();
    std::cout << "ss1.good() = " << good << std::endl;
}

int main() {
    std::cout << "=========Confun=========" << std::endl;
    Confun();
    std::cout << "=========Memfun=========" << std::endl;
    MemFun();
    std::cout << "=========Inherti_istream=========" << std::endl;
    Inherti_istream();
    std::cout << "=========Inherit_ostream=========" << std::endl;
    Inherit_ostream();
    std::cout << "=========inherit_ios=========" << std::endl;
    inherit_ios();
    return 0;
}