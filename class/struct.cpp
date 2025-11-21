#include <iostream>
#include <string>

struct Point {
  std::string name;
    int x;
    int y;
    int z;
};

typedef struct {
    int x;
    int y;
    int z;
} Point2;

void Init() {
  // 0.不赋值，成员的值未定义
  Point p0;

  // 1.定义时赋值
  Point p1 = {"p1", 1, 2, 3};

  // 2.定义后逐个赋值
  Point p2;
  p2.name = "p2";
  p2.x = 3;
  p2.y = 4;
  p2.z = 5;

  // 3.定义时乱序赋值，C风格
  // 如果不按照声明顺序，编译报错error: designator order for field ‘Point::x’ does not match declaration order in ‘Point’
  Point p3 = {.name = "p3", .x = 5, .y = 6, .z = 7};

  // 4.定义时乱序赋值, C++风格
  Point p4 = {
    name: "p4",
    x: 8,
    y: 9,
    z: 10
  };

  // 5.这是C++的值初始化，他会将结构体的所有成员初始化为0，基本类型都为其对应的默认值
  Point p5 = {};

  // 6.这是c风格的初始化，他会将第一个元素初始化，其他元素隐式初始化为0
  Point p6 = {"p6"};

  std::cout << "p0: " << p0.name << ", " << p0.x << ", " << p0.y << ", " << p0.z << std::endl;
  std::cout << "p1: " << p1.name << ", " << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
  std::cout << "p2: " << p2.name << ", " << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
  std::cout << "p3: " << p3.name << ", " << p3.x << ", " << p3.y << ", " << p3.z << std::endl;
  std::cout << "p4: " << p4.name << ", " << p4.x << ", " << p4.y << ", " << p4.z << std::endl;
  std::cout << "p5: " << p5.name << ", " << p5.x << ", " << p5.y << ", " << p5.z << std::endl;
  std::cout << "p6: " << p6.name << ", " << p6.x << ", " << p6.y << ", " << p6.z << std::endl;
}

struct Data {
  int a;
  double b;
  // Data(int a_, double b_) : a(a_), b(b_) {}
};

void struct_construct() {
  Data d1{};          // OK，值初始化，a=0, b=0.0
  Data d2{1, 2.0};    // OK，直接初始化，a=1, b=2.0
  Data d3;         // OK，默认初始化，a和b未定义
#if 0
  /**
   * 编译报错：error: no matching function for call to ‘Data::Data()’
   *
   * 并且会提示(编译器尝试找默认提供的构造函数)：
   * note: candidate: ‘Data::Data()’
   * note:   candidate expects 0 arguments, 2 provided
   * note: candidate: ‘constexpr Data::Data(const Data&)’
   * note:   candidate expects 1 argument, 2 provided
   * note: candidate: ‘constexpr Data::Data(Data&&)’
   * note:   candidate expects 1 argument, 2 provided
   */
  Data d4(1, 2.0);    // ERROR，没有定义构造函数

  std::vector<Data> vec(5);
  vec.emplace_back(1, 2.0);  // ERROR，没有定义构造函数
#endif
}

int main() {
  std::cout << "======================Init======================" << std::endl;
  Init();
  std::cout << "==================struct_construct==================" << std::endl;
  struct_construct();

  return 0;
}