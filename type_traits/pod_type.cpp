#include <iostream>
#include <type_traits>

using namespace std;

/**
 * POD (Plain Old Data) :
 * 1.历史背景：
 *    - 系统底层基本都是用C写的，数据类型基本上是int、float、struct等。随便一堆二进制数据，都可以直接映射到具体的类型上
 *    - C++引入了类和对象的概念，增加了复杂性。为了兼容C的数据，C++引入了POD类型。
 * 2.术语描述
 *    - 对于POD type，可以直接用memcpy、memset等C风格的函数进行操作
 *    - 对于POD Class，需要其满足两个条件：
 *       1) Trivial：类的构造函数、析构函数和拷贝/移动构造函数都是编译器自动生成的，且没有虚函数和虚基类
 *       2) Standard-layout：线性的数据结构，类(或者struct、union)：
 *          - 没有虚函数和虚基类
 *          - 对于所有的非静态成员，拥有同样的访问控制权限
 *          - 如果有基类：所有非静态成员必须在一个基类中，不可以分散；或者所有基类都没有非静态成员
 *          - 基类也需要是standard-layout
 *          - 第一个非静态成员类型必须是自己的，即不能是任何一个基类的类型
 *          
 */

struct B {
 protected:
  virtual void Foo() {}
};

/**
 * Neither trivial nor standard-layout
 */
struct A : B {
  int a;
  int b;
  void Foo() override {}  // Virtual function
};

/**
 * Trivial but not standard-layout
 */
struct C {
  int a;

 private:
  int b;  // Different access control
};

/**
 * Standard-layout but not trivial
 */
struct D {
  int a;
  int b;
  D() {}  // User-defined constructor
};

/**
 * POD type: trivial and standard-layout
 */
struct POD {
  int a;
  int b;
};

int main() {
  cout << boolalpha;
  cout << "A is pod is " << is_pod<A>() << endl;                  // false
  cout << "A is trivial is " << is_trivial<A>() << endl;                  // false
  cout << "A is standard-layout is " << is_standard_layout<A>() << endl;  // false

  cout << "B is pod is " << is_pod<B>() << endl;                  // false
  cout << "B is trivial is " << is_trivial<B>() << endl;                  // false
  cout << "B is standard-layout is " << is_standard_layout<B>() << endl;  // false

  cout << "C is pod is " << is_pod<C>() << endl;                  // false
  cout << "C is trivial is " << is_trivial<C>() << endl;                  // true
  cout << "C is standard-layout is " << is_standard_layout<C>() << endl;  // false

  cout << "D is pod is " << is_pod<D>() << endl;                  // false
  cout << "D is trivial is " << is_trivial<D>() << endl;                  // false
  cout << "D is standard-layout is " << is_standard_layout<D>() << endl;  // true

  cout << "POD is pod is " << is_pod<POD>() << endl;                  // true
  cout << "POD is trivial is " << is_trivial<POD>() << endl;                  // true
  cout << "POD is standard-layout is " << is_standard_layout<POD>() << endl;  // true

  return 0;
}