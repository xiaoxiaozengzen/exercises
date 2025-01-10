#include <iostream>

// mutable的作用有两点：
//  （1）保持常量对象中大部分数据成员仍然是“只读”的情况下，实现对个别数据成员的修改；
//  （2）使类的const函数可以修改对象的mutable数据成员。

int main() {
  int a = 10;

  // 可以修改a的值
  // lambda是闭包类，其operator()()函数默认是const的，如果要修改值，需要加上mutable关键字
  auto lam1 = [a]() mutable {
    std::cout << a << std::endl;
    a++;
  };

  lam1();

  std::cout << a << std::endl;
}