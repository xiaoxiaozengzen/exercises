#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

#include <algorithm>

/**
 * copy跟memcpy的区别：
 * copy适用于：
 *  1. 处理自定义类型，copy在进行拷贝时会调用对象的拷贝构造函数和拷贝赋值运算符。
 *  2. 类或者结构体中包含指针时，如果实现了深拷贝构造函数，copy会调用深拷贝构造函数
 * 
 * memcpy适用于：
 *  1. 处理内置类型（如int、char等）或POD类型（Plain Old Data），memcpy直接按字节拷贝数据，不会调用构造函数或赋值运算符。
 *  2. 处理简单的内存拷贝操作，memcpy通常比copy更高效，因为它直接操作内存，不涉及对象的构造和析构
 */

/**
 * template <class InputIterator, class OutputIterator>
 * OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result);
 * 
 * @brief Copies the elements in the range [first,last) into the range beginning at result.
 * @return 返回一个迭代器，result中拷贝的最后一个元素的下一个位置。
 */
void copy_test() {
    int arr[] = {1, 2, 3, 4, 5};
    int arr_copy[10] = {0};
    int* result = std::copy(arr, arr + 5, arr_copy);
    std::cout << "Result address: " << result << std::endl;
    std::cout << "Result value: " << *result << std::endl;
    std::cout << "arr[4]: " << &arr[4] << std::endl;
    std::cout << "arr_copy[5]: " << &arr_copy[5] << std::endl;
    std::cout << "Copied array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr_copy[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * template <class InputIterator, class Size, class OutputIterator>
 * OutputIterator copy_n (InputIterator first, Size n, OutputIterator result);
 * 
 * @brief Copies the first n elements from the range beginning at first into the range beginning at result.
 * @return 返回一个迭代器，result中拷贝的最后一个元素的下一个位置。
 */
void copy_n_test() {
    int arr[] = {1, 2, 3, 4, 5};
    int arr_copy[10] = {0};
    int* result = std::copy_n(arr, 5, arr_copy);
    std::cout << "Result address: " << result << std::endl;
    std::cout << "Result value: " << *result << std::endl;
    std::cout << "arr[4]: " << &arr[4] << std::endl;
    std::cout << "arr_copy[5]: " << &arr_copy[5] << std::endl;
}

/**
 * template <class InputIterator, class OutputIterator, class UnaryPredicate>
 * OutputIterator copy_if (InputIterator first, InputIterator last, OutputIterator result, UnaryPredicate pred);
 * 
 * @brief Copies the elements in the range [first,last) for which pred returns true to the range beginning at result.
 */
void copy_if_test() {
  std::vector<int> foo = {25,15,-5,5,-15};
  std::vector<int> bar (foo.size());

  // copy only positive numbers:
  auto it = std::copy_if (foo.begin(), foo.end(), bar.begin(), [](int i){return !(i<0);} );
  std::cout << "diff: " << std::distance(bar.begin(), it) << std::endl;
  std::cout << "it: " << *it << std::endl;

  std::cout << "bar contains:";
  for (int& x: bar) std::cout << ' ' << x;
  std::cout << '\n';
}

/**
 * template <class BidirectionalIterator1, class BidirectionalIterator2>
 * BidirectionalIterator2 copy_backward (BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);
 * 
 * @brief Copies the elements in the range [first,last) starting from the end into the range terminating at result.
 * @return returns an iterator to the first element in the destination range.
 */
void copy_backward_test() {
    int arr[] = {1, 2, 3, 4, 5};
    int arr_copy[10] = {0};

    // 该函数最开始会copying *(last-1) into *(result-1),
    int* result = std::copy_backward(arr, arr + 5, arr_copy + 10);
    std::cout << "Result address: " << result << std::endl;
    std::cout << "Result value: " << *result << std::endl;
    std::cout << "arr_copy[5]: " << arr_copy[9 - 5] << std::endl;
    std::cout << "arr_copy[5] address: " << &arr_copy[9 + 1 - 5] << std::endl;

    std::cout << "arr_copy contains:";
    for (int i = 0; i < 10; ++i) {
        std::cout << ' ' << arr_copy[i];
    }
    std::cout << std::endl;
}

/**
 * template <class InputIterator, class OutputIterator>
 * OutputIterator move (InputIterator first, InputIterator last, OutputIterator result);
 * 
 * @brief Moves the elements in the range [first,last) into the range beginning at result.
 * @return 返回一个迭代器，result中移动的最后一个元素的下一个位置。
 */
void move_test() {
  std::vector<std::string> foo = {"air","water","fire","earth"};
  std::vector<std::string> bar (4);

  // moving ranges:
  std::cout << "Moving ranges...\n";
  std::vector<std::string>::iterator ret = std::move ( foo.begin(), foo.begin()+2, bar.begin() );
  std::cout << "diff: " << std::distance(bar.begin(), ret) << std::endl;
  std::cout << "ret -1: " << *(ret - 1) << std::endl;

  // old array
  std::cout << "foo size: " << foo.size() << std::endl;
  std::cout << "foo contains:";
  for (const auto& x: foo) std::cout << ' ' << x;
  std::cout << '\n';
}

/**
 * template <class T> 
 * void swap (T& a, T& b)  noexcept (is_nothrow_move_constructible<T>::value && is_nothrow_move_assignable<T>::value);
 * 
 * template <class T, size_t N> 
 * void swap(T (&a)[N], T (&b)[N])  noexcept (noexcept(swap(*a,*b)));
 */
void swap_test() {
    int a = 10;
    int b = 20;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    std::swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    std::cout << "Before swap: arr1 = {";
    for (int i : arr1) std::cout << i << " ";
    std::cout << "}, arr2 = {";
    for (int i : arr2) std::cout << i << " ";
    std::cout << "}" << std::endl;
    std::swap(arr1, arr2);
    std::cout << "After swap: arr1 = {";
    for (int i : arr1) std::cout << i << " ";
    std::cout << "}, arr2 = {";
    for (int i : arr2) std::cout << i << " ";
    std::cout << "}" << std::endl;
}

/**
 * template <class InputIterator, class OutputIterator, class UnaryOperation>
 * OutputIterator transform (InputIterator first1, InputIterator last1, OutputIterator result, UnaryOperation op);
 * @brief 对[first1, last1)中的每个元素应用一元操作op，并从result开始存储结果。
 * 
 * template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>  
 * OutputIterator transform (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryOperation binary_op);
 * @brief 遍历[first1, last1)]作为binary_op的第一个参数，切相对的从first2开始的元素作为第二个参数，并将结果存储在result中。
 * 
 * @return 紧跟着写入result的最后一个元素的下一个位置。
 */
void transform_test() {
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> dst(src.size());

    // 使用一元操作
    std::transform(src.begin(), src.end(), dst.begin(), [](int x) { return x * x; });
    std::cout << "Transformed (squared): ";
    for (int v : dst) std::cout << v << " ";
    std::cout << std::endl;

    // 使用二元操作
    std::vector<int> src2 = {10, 20, 30, 40, 50};
    std::vector<int> dst2(src.size());
    std::transform(src.begin(), src.end(), src2.begin(), dst2.begin(), [](int x, int y) { return x + y; });
    std::cout << "Transformed (added): ";
    for (int v : dst2) std::cout << v << " ";
    std::cout << std::endl;
}

/**
 * template <class ForwardIterator, class T>  
 * void replace (ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value);
 * @brief 替换[first, last)范围内的所有跟old_value相等的元素为new_value。
 */
void replace_test() {
    std::vector<int> vec = {1, 2, 3, 2, 4, 2, 5};
    std::cout << "Original vector: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << std::endl;

    // 替换所有的2为99
    std::replace(vec.begin(), vec.end(), 2, 99);
    
    std::cout << "After replace: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "====================== copy_test ======================" << std::endl;
    copy_test();
    std::cout << "====================== copy_n_test ======================" << std::endl;
    copy_n_test();
    std::cout << "====================== copy_if_test ======================" << std::endl;
    copy_if_test();
    std::cout << "====================== copy_backward_test ======================" << std::endl;
    copy_backward_test();
    std::cout << "====================== move_test ======================" << std::endl;
    move_test();
    std::cout << "====================== swap_test ======================" << std::endl;
    swap_test();
    std::cout << "====================== transform_test ======================" << std::endl;
    transform_test();
    std::cout << "====================== replace_test ======================" << std::endl;
    replace_test();

    return 0;
}