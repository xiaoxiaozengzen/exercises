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

  std::cout << "*poiterVar1: " << *poiterVar1 << std::endl;
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

  int arr1[4] = {1, 2, 3, 4};
  int(*p)[4] = &arr1;
  std::cout << "arr1: " << arr1 << std::endl;
  std::cout << "arr1[0]: " << *arr1 << std::endl;
  std::cout << "arr1[1]: " << *(arr1 + 1) << std::endl;
  std::cout << "*(*p): " << *(*p) << std::endl;
  std::cout << "*((*p)+1): " << *((*p) + 1) << std::endl;
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
}