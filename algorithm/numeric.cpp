#include <iostream>
#include <vector>
#include <numeric>

class MyData {
public:
    MyData(int data):data(data) {

    }
    ~MyData() = default;

    friend int operator+(const int& left, const MyData& right) {
        return left + right.data;
    }

    friend int operator+(const MyData& right, const int& left) {
        return left + right.data;
    }

    friend int operator-(const MyData& left, const MyData& right) {
        return right.data - left.data + 1;
    }

    operator int() const {
        return data;
    }

private:
    int data = 0;
};

/**
 * template <class InputIterator, class T>   
 * T accumulate (InputIterator first, InputIterator last, T init);
 *
 * template <class InputIterator, class T, class BinaryOperation>   
 * T accumulate (InputIterator first, InputIterator last, T init, BinaryOperation binary_op);
 * 
 * @note 返回[first, last)范围内元素累加在初始值init的值
 * @note binary_op张的应该类似这样 T fun(T, InputIterator)
 */
void accumulate_example() {
    std::vector<MyData> arr(10, 2);
    int init = 5;
    int ret = std::accumulate(arr.begin(), arr.end(), init);
    std::cout << "ret = " << ret << std::endl;

    int ret2 = std::accumulate(arr.begin(), arr.end(), init, [](int left, MyData right) {
        return left + right + 10;
    });
    std::cout << "ret2 = " << ret2 << std::endl;
}

/**
 * template <class InputIterator, class OutputIterator>   
 * OutputIterator adjacent_difference (InputIterator first, InputIterator last, OutputIterator result);
 *
 * template <class InputIterator, class OutputIterator, class BinaryOperation>   
 * OutputIterator adjacent_difference ( InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op );
 *
 * @note 从result开始，将[frist, end)范围内的元素赋值过去，类似 y0 = x0;y1 = x1 - x0
 * @note  BinaryOperation可以堪称一个函数，参数是[frist, end)的两个元素，返回值是其diff
 */
void adjacent_difference_example() {
    std::vector<int> arr1(10, 7);
    std::vector<int> arr2(10, 10);
    std::vector<int>::iterator ite1 = std::adjacent_difference(arr1.begin(), arr1.end(), arr2.begin());
    if(ite1 == arr2.end()) {
        std::cout << "ite is arr2 end" << std::endl;
    } else {
        std::cout << "ite1 " << *ite1 << std::endl;
    }
    std::cout << "arr2: ";
    for(auto val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    MyData a(10);
    MyData b(5);
    int ret = a - b;

    std::vector<MyData> arr3(10, 2);
    std::vector<int>::iterator ite2 = std::adjacent_difference(arr3.begin(), arr3.end(), arr2.begin(), [](MyData left, MyData right){
        int ret = (right - left);
        return ret;
    });
    std::cout << "arr2: ";
    for(auto val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "========================== accumulate_example ==========================" << std::endl;
    accumulate_example();
    std::cout << "========================== adjacent_difference_example ==========================" << std::endl;
    adjacent_difference_example();

    return 0;
}