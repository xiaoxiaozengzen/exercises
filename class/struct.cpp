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

struct DataStatic {
  int a;
  double b;
  static int c;  // 静态成员变量不占用类的内存空间
};

void struct_construct() {
  Data d1{};          // OK，值初始化，a=0, b=0.0
  Data d2{1, 2.0};    // OK，直接初始化，a=1, b=2.0
  Data d3;         // OK，默认初始化，a和b未定义
  std::cout << "sizeof(Data) = " << sizeof(Data) << std::endl;
  std::cout << "sizeof(DataStatic) = " << sizeof(DataStatic) << std::endl;
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

/**
 * 结构体内存字节对齐方式：
 * 1.重排字段：把大字段放前面，小字段放后面，减少内存填充字节
 * 2.显示填充字段：在成员中加入char padding[?]，手动填充字节
 * 3.attribute
 *   __attribute__((packed))：GCC和Clang支持，告诉编译器按1字节对齐，不进行填充
 *   __attribute__((aligned(n)))：GCC和Clang支持，告诉编译器按n字节对齐，进行填充
 * 4.#pragma pack(n)：MSVC、GCC和Clang支持，告诉编译器按n字节对齐，进行填充
 *   一般用#pragma pack(push)保存当前对齐方式，#pragma pack(pop)恢复之前对齐方式
 * 5.alignas(n)：C++11标准，告诉编译器按n字节对齐，进行填充
 *
 * @note
 * padding于pack的区别：
 * - packed：改变成员布局，取消成员间的填充字节
 * - padding：不改变成员布局，调整整个结构体的大小为指定对齐方式的整数倍，在结构体末尾添加填充字节
 */
#pragma pack(push)
#pragma pack(1)
template<typename T>
struct Point3D {
  T x;
  T y;
  T z;
};
#pragma pack(pop)

template<typename T>
struct Point3D_derive : public Point3D<T> {
  T a;
};

template<typename T>
struct Point3D_derive_1 : public Point3D_derive<T> {
  float b;
};

template<typename T>
struct __attribute__((packed)) Point3D_attr {
  T x;
  T y;
  T z;
};

template<typename T>
struct __attribute__((aligned(8))) Point3D_attr_aligned {
  T x;
  T y;
  T z;
};

template<typename T>
struct __attribute__((packed, aligned(16))) Point3D_attr_both {
  T x;
  T y;
  T z;
};

template<typename T>
struct alignas(8) Point3D_alignas {
  T x;
  T y;
  T z;
};

void pack_test() {
  std::cout << "sizeof(Point3D<char>) = " << sizeof(Point3D<char>) << std::endl;
  std::cout << "sizeof(Point3D<int>) = " << sizeof(Point3D<int>) << std::endl;
  std::cout << "sizeof(Point3D<double>) = " << sizeof(Point3D<double>) << std::endl;
  std::cout << "sizeof(Point3D_attr<char>) = " << sizeof(Point3D_attr<char>) << std::endl;
  std::cout << "sizeof(Point3D_attr<int>) = " << sizeof(Point3D_attr<int>) << std::endl;
  std::cout << "sizeof(Point3D_attr<double>) = " << sizeof(Point3D_attr<double>) << std::endl;
  std::cout << "sizeof(Point3D_attr_aligned<char>) = " << sizeof(Point3D_attr_aligned<char>) << std::endl;
  std::cout << "sizeof(Point3D_attr_aligned<int>) = " << sizeof(Point3D_attr_aligned<int>) << std::endl;
  std::cout << "sizeof(Point3D_attr_aligned<double>) = " << sizeof(Point3D_attr_aligned<double>) << std::endl;
  std::cout << "sizeof(Point3D_attr_both<char>) = " << sizeof(Point3D_attr_both<char>) << std::endl;
  std::cout << "sizeof(Point3D_attr_both<int>) = " << sizeof(Point3D_attr_both<int>) << std::endl;
  std::cout << "sizeof(Point3D_attr_both<double>) = " << sizeof(Point3D_attr_both<double>) << std::endl;
  std::cout << "sizeof(Point3D_alignas<char>) = " << sizeof(Point3D_alignas<char>) << std::endl;
  std::cout << "sizeof(Point3D_alignas<int>) = " << sizeof(Point3D_alignas<int>) << std::endl;
  std::cout << "sizeof(Point3D_alignas<double>) = " << sizeof(Point3D_alignas<double>) << std::endl;
  std::cout << "sizeof(Point3D_derive<char>) = " << sizeof(Point3D_derive<char>) << std::endl;
  std::cout << "sizeof(Point3D_derive<int>) = " << sizeof(Point3D_derive<int>) << std::endl;
  std::cout << "sizeof(Point3D_derive<double>) = " << sizeof(Point3D_derive<double>) << std::endl;
  std::cout << "sizeof(Point3D_derive_1<char>) = " << sizeof(Point3D_derive_1<char>) << std::endl;
  std::cout << "sizeof(Point3D_derive_1<int>) = " << sizeof(Point3D_derive_1<int>) << std::endl;
  std::cout << "sizeof(Point3D_derive_1<double>) = " << sizeof(Point3D_derive_1<double>) << std::endl;
}

int main() {
  std::cout << "======================Init======================" << std::endl;
  Init();
  std::cout << "==================struct_construct==================" << std::endl;
  struct_construct();
  std::cout << "======================pack_test======================" << std::endl;
  pack_test();

  return 0;
}