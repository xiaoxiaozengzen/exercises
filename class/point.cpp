#include <stdio.h>

#include <iostream>
#include <string>

void one_point() {
  int a = 10;
  int *b = &a;

  printf("&a: %p\n", &a);
  printf("*b: %d\n", *b);
  printf("b: %p\n", b);
  printf("&b: %p\n", &b);
}

/**
 * @brief 二级指针
 *
 * @note 星号的作用有两个:
 * 一是在指针定义的时候表明该变量是指针变量以及是几级指针（有几个星号就表示几级）
 * 二是能够通过指针变量所指向的内存地址（或者说上图中Value的值）来获取对应内存的内容。
 */
void second_point() {
  // name: str
  // value: hello
  // address: 0x7fffffffdc00
  std::string str = "hello";

  // name str1
  // value: world
  // address: 0x7fffffffdc20
  std::string str1 = "world";

  // name: poiterVar1
  // value: 0x7fffffffdc00
  // address: 0x7fffffffdbf0
  std::string *poiterVar1 = &str;

  // name: poiterVar2
  // value: 0x7fffffffdbf0
  // address: 0x7fffffffdbf8
  std::string **poiterVar2 = &poiterVar1;

  std::cout << "str: " << str
            << ", &str: " << &str
            << std::endl;
  std::cout << "str1: " << str1
            << ", &str1: " << &str1
            << std::endl;
  std::cout << "poiterVar1: " << poiterVar1
            << ", &poiterVar1: " << &poiterVar1
            << ", *poiterVar1: " << *poiterVar1
            << std::endl;
  std::cout << "poiterVar2: " << poiterVar2
            << ", &poiterVar2: " << &poiterVar2
            << ", *poiterVar2: " << *poiterVar2
            << ", **poiterVar2: " << **poiterVar2
            << std::endl;
  *poiterVar2 = &str1;
  std::cout << "*poiterVar1: " << *poiterVar1 << std::endl;
  std::cout << "**poiterVar2: " << **poiterVar2 << std::endl;
}

void const_point() {
  int a = 10;
  int b = 20;
  int *p1 = &a;
  // 常量指针
  const int *p2 = &a;
  // 指针常量
  int *const p3 = &a;
  const int *const p4 = &a;

  p1 = &b;
  printf("*p1 %d\n", *p1);

  p2 = &b;
  printf("*p2 %d\n", *p2);
  // error: assignment of read-only location ‘* p2’
  // *p2 = 30;

  // error: assignment of read-only variable ‘p3’
  // p3 = &b;
  printf("*p3 %d\n", *p3);

  printf("*p4 %d\n", *p4);
}

/**
 * @brief 数组指针
 *
 * @note
 * 指针数组：指针数组可以说成是”指针的数组”，首先这个变量是一个数组，
 * 其次，”指针”修饰这个数组，意思是说这个数组的所有元素都是指针类型，在32位系统中，指针占四个字节
 *
 * 数组指针：数组指针可以说成是”数组的指针”，首先这个变量是一个指针，
 * 其次，”数组”修饰这个指针，意思是说这个指针存放着一个数组的首地址，或者说这个指针指向一个数组的首地址。
 *
 */
void arr_point() {
  char *arr[4] = {"hello", "world", "shannxi", "xian"};
  std::cout << "sizeof(arr): " << sizeof(arr) << std::endl;
  std::cout << "arr: " << arr << std::endl;
  std::cout << "&arr: " << &arr << std::endl;
  std::cout << "*arr: " << *arr << std::endl;
  char* first = nullptr;
  first = arr[0];
  std::cout << "first: " << first << std::endl;
  std::cout << "arr[0]: " << arr[0] << std::endl;

  std::cout << "-------------------------" << std::endl;

  int arr1[4] = {10, 11, 12, 13};
  std::cout << "sizeof(arr1): " << sizeof(arr1) << std::endl;
  std::cout << "arr1: " << arr1 << std::endl;
  std::cout << "&arr1: " << &arr1 << std::endl;
  std::cout << "&arr1[0]: " << &arr1[0] << std::endl;
  std::cout << "arr1[0]: " << arr1[0] << std::endl;
  std::cout << "*arr1: " << *arr1 << std::endl;
  std::cout << "*(arr1 + 1): " << *(arr1 + 1) << std::endl;

  std::cout << "-------------------------" << std::endl;
  
  /**
   * @brief 一个数组指针
   */
  int(*p)[4] = &arr1;
  std::cout << "sizeof(p): " << sizeof(p) << std::endl;
  std::cout << "p: " << p << std::endl;
  std::cout << "&p: " << &p << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "*(*p): " << *(*p) << std::endl;
  std::cout << "*((*p)+1): " << *((*p) + 1) << std::endl;

  std::cout << "-------------------------" << std::endl;

  /**
   * @brief 双指针
   */
  char** pp = arr;
  std::cout << "sizeof(pp): " << sizeof(pp) << std::endl;
  std::cout << "pp: " << pp << std::endl;
  std::cout << "&pp: " << &pp << std::endl;
  std::cout << "*pp: " << *pp << std::endl;
  std::cout << "*(pp + 1): " << *(pp + 1) << std::endl;
  std::cout << "*pp + 1: " << *pp + 1 << std::endl;
  std::cout << "*(*pp): " << *(*pp) << std::endl;
  std::cout << "*((*pp)+1): " << *((*pp) + 1) << std::endl;
}

void point_reference() {
  int * p = new int(10);
  int * p_null = nullptr;

  std::cout << "before: p: " << *p << std::endl;
  auto lambda = [](int * value) {
    *value = 20;
    std::cout << "lambda: value: " << *value << std::endl;
  };
  lambda(p);
  std::cout << "after: p: " << *p << std::endl;

  /**
   * 函数参数是按值传递，因此是传入指针p的一份拷贝。
   * lambda2函数中，修改了指针变量value的值，使其指向了一个新的内存地址，但这并不会影响到外部的指针p，因为p和value是两个独立的变量。
   */
  auto lamdba2 = [](int* value) {
    int * temp = new int(100);
    value = temp;
    std::cout << "lambda2: value: " << *value << std::endl;
  };
  lamdba2(p);
  std::cout << "after lambda2: p: " << *p << std::endl;

  /**
   * 函数参数是按引用传递，因此传入的是指针p的引用，修改value的值会直接影响到外部的指针p，使其指向一个新的内存地址。
   */
  auto lanbda3 = [](int*& value) {
    int * temp = new int(100);
    value = temp;
    std::cout << "lambda3: value: " << *value << std::endl;
  };
  lanbda3(p);
  std::cout << "after lambda3: p: " << *p << std::endl;
}

int main() {
  std::cout << "=================one_point=================" << std::endl;
  one_point();
  std::cout << "=================second_point=================" << std::endl;
  second_point();
  std::cout << "=================const_point=================" << std::endl;
  const_point();
  std::cout << "=================arr_point=================" << std::endl;
  arr_point();
  std::cout << "=================point_reference=================" << std::endl;
  point_reference();

  return 0;
}