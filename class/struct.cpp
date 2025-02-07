#include <iostream>

struct Point {
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
  // 1.定义时赋值
  Point p1 = {1, 2, 3};

  // 2.定义后逐个赋值
  Point p2;
  p2.x = 3;
  p2.y = 4;
  p2.z = 5;

  // 3.定义时乱序赋值，C风格
  // 如果不按照声明顺序，编译报错error: designator order for field ‘Point::x’ does not match declaration order in ‘Point’
  Point p3 = {.x = 5, .y = 6, .z = 7};

  // 4.定义时乱序赋值, C++风格
  Point p4 = {
    x: 8,
    y: 9,
    z: 10
  };

  std::cout << "p1: " << p1.x << ", " << p1.y << ", " << p1.z << std::endl;
  std::cout << "p2: " << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
  std::cout << "p3: " << p3.x << ", " << p3.y << ", " << p3.z << std::endl;
  std::cout << "p4: " << p4.x << ", " << p4.y << ", " << p4.z << std::endl;
}

int main() {
  std::cout << "======================Init======================" << std::endl;
  Init();
}