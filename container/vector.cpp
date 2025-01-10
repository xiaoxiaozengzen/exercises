#include <iostream>
#include <vector>

// template<
//       class T,
//       class Alloc = allocator<T>
// > class vector; // generic template

class A {
 public:
  A() { std::cout << "construct" << std::endl; }

  A(int a) : a(a) { std::cout << "construct with a" << std::endl; }

  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A& other) {
    this->a = other.a;
    std::cout << "copy construct" << std::endl;
  }

  A& operator=(const A& other) {
    this->a = other.a;
    std::cout << "copy assignment" << std::endl;
    return *this;
  }

  A(A&& other) {
    this->a = other.a;
    std::cout << "move construct" << std::endl;
  }

  A& operator=(A&& other) {
    this->a = other.a;
    std::cout << "move assignment" << std::endl;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const A& a) {
    os << a.a;
    return os;
  }

 private:
  int a = 0;
};

void MemberType() {
  std::vector<int> arr = {1, 2, 3, 4, 5};

  if (std::is_same<std::vector<int>::value_type, int>::value) {
    std::cout << "value_type is int" << std::endl;
  }
  if (std::is_same<std::vector<int>::allocator_type, std::allocator<int>>::value) {
    std::cout << "allocator_type is std::allocator<int>" << std::endl;
  }
  if (std::is_same<std::vector<int>::size_type, std::size_t>::value) {
    std::cout << "size_type is std::size_t" << std::endl;
  }
  if (std::is_same<std::vector<int>::difference_type, std::ptrdiff_t>::value) {
    std::cout << "difference_type is std::ptrdiff_t" << std::endl;
  }
  if (std::is_same<std::vector<int>::reference, int&>::value) {
    std::cout << "reference is int&" << std::endl;
  }
  if (std::is_same<std::vector<int>::const_reference, const int&>::value) {
    std::cout << "const_reference is const int&" << std::endl;
  }
  if (std::is_same<std::vector<int>::pointer, int*>::value) {
    std::cout << "pointer is int*" << std::endl;
  }
  if (std::is_same<std::vector<int>::const_pointer, const int*>::value) {
    std::cout << "const_pointer is const int*" << std::endl;
  }
  if (std::is_same<std::vector<int>::iterator, std::vector<int>::pointer>::value) {
    std::cout << "iterator is std::vector<int>::pointer" << std::endl;
  } else {
    std::cout << "iterator is not std::vector<int>::pointer" << std::endl;
  }
  if (std::is_same<std::vector<int>::const_iterator, std::vector<int>::const_pointer>::value) {
    std::cout << "const_iterator is std::vector<int>::const_pointer" << std::endl;
  } else {
    std::cout << "const_iterator is not std::vector<int>::const_pointer" << std::endl;
  }
  if (std::is_same<std::vector<int>::reverse_iterator,
                   std::reverse_iterator<std::vector<int>::iterator>>::value) {
    std::cout << "reverse_iterator is std::reverse_iterator<std::vector<int>::iterator>"
              << std::endl;
  } else {
    std::cout << "reverse_iterator is not std::reverse_iterator<std::vector<int>::iterator>"
              << std::endl;
  }
  if (std::is_same<std::vector<int>::const_reverse_iterator,
                   std::reverse_iterator<std::vector<int>::const_iterator>>::value) {
    std::cout << "const_reverse_iterator is std::reverse_iterator<std::vector<int>::const_iterator>"
              << std::endl;
  } else {
    std::cout
        << "const_reverse_iterator is not std::reverse_iterator<std::vector<int>::const_iterator>"
        << std::endl;
  }
}

void ConstructFun() {
  std::vector<int> arr1;
  std::vector<int> arr2(5);
  std::vector<int> arr3(5, 1);
  std::vector<int> arr4 = {1, 2, 3, 4, 5};
  std::vector<int> arr5(arr4.begin(), arr4.end());
  std::vector<int> arr6(arr5);

  int arr[] = {1, 2, 3, 4, 5};
  std::vector<int> arr7(std::begin(arr), std::end(arr));
}

void MemberFun() {
  // 1. iterators
  std::vector<int> arr = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it = arr.begin();
  std::cout << "begin: " << *it << std::endl;
  std::vector<int>::iterator it2 = arr.end();
  std::cout << "end: " << *(it2 - 1) << std::endl;
  std::vector<int>::reverse_iterator it3 = arr.rbegin();
  std::cout << "rbegin: " << *it3 << std::endl;
  std::vector<int>::reverse_iterator it4 = arr.rend();
  std::cout << "rend: " << *(it4 - 1) << std::endl;
  std::vector<int>::const_iterator it5 = arr.cbegin();
  std::cout << "cbegin: " << *it5 << std::endl;
  std::vector<int>::const_iterator it6 = arr.cend();
  std::cout << "cend: " << *(it6 - 1) << std::endl;
  std::vector<int>::const_reverse_iterator it7 = arr.crbegin();
  std::cout << "crbegin: " << *it7 << std::endl;
  std::vector<int>::const_reverse_iterator it8 = arr.crend();
  std::cout << "crend: " << *(it8 - 1) << std::endl;

  // 2. capacity
  std::cout << "size: " << arr.size() << std::endl;
  std::cout << "max_size: " << arr.max_size() << std::endl;
  std::cout << "capacity: " << arr.capacity() << std::endl;
  std::cout << "empty: " << arr.empty() << std::endl;
  arr.reserve(10);
  std::cout << "capacity: " << arr.capacity() << std::endl;
  arr.shrink_to_fit();  // This may cause a reallocation, but has no effect on the vector size and
                        // cannot alter its elements.
  std::cout << "capacity: " << arr.capacity() << std::endl;

  // 3. element access
  std::cout << "arr[0]: " << arr[0] << std::endl;
  std::cout << "arr.at(0): " << arr.at(0) << std::endl;
  try {
    std::cout << "arr.at(10): " << arr.at(10) << std::endl;
  } catch (const std::out_of_range& e) {
    std::cout << "out_of_range" << std::endl;
  }
  std::vector<int>::reference ref = arr.front();
  ref = 10;
  std::cout << "front: " << arr.front() << std::endl;
  std::cout << "back: " << arr.back() << std::endl;

  std::vector<int>::value_type* data = arr.data();
  std::cout << "data: " << *data << std::endl;
  std::cout << "data+1: " << *(data + 1) << std::endl;

  // 4. modifiers
  int arr2[] = {6, 7, 8, 9, 10};
  arr.assign(std::begin(arr2), std::end(arr2));
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  arr.assign(10, 12);
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  arr.assign({1, 2, 3, 4, 5});
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  std::cout << "capacity: " << arr.capacity() << std::endl;
  std::cout << "empty: " << arr.empty() << std::endl;

  arr.push_back(6);
  arr.pop_back();

  std::vector<int>::iterator it9 = arr.insert(arr.begin(), 0);
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  std::cout << "it9: " << *it9 << std::endl;
  std::vector<int>::iterator it10 = arr.insert(arr.begin(), 2, 10);
  std::cout << "it10: " << *it10 << std::endl;
  std::cout << "distance: " << std::distance(arr.begin(), it10) << std::endl;
  std::vector<int>::iterator it11 = arr.insert(arr.begin(), std::begin(arr2), std::end(arr2));
  std::cout << "it11: " << *it11 << std::endl;
  arr.insert(arr.begin(), {1, 2, 3, 4, 5});
  arr.insert(arr.end(), 16);

  // 引发：segmentation fault
  // arr.insert(arr.end() + 1, 10);

  // This is the container end if the operation erased the last element in the sequence.
  std::vector<int>::iterator it12 = arr.erase(arr.end() - 1);
  std::cout << "it12: " << *it12 << std::endl;
  std::vector<int>::iterator it13 = arr.erase(arr.begin(), arr.begin() + 2);
  std::cout << "it13: " << *it13 << std::endl;

  std::vector<int> arr3 = {1, 2, 3, 4, 5};
  arr.swap(arr3);
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  std::cout << "capacity: " << arr.capacity() << std::endl;
  std::cout << "empty: " << arr.empty() << std::endl;
  arr.clear();
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  std::vector<int>::iterator it14 = arr.emplace(arr.begin(), 111);
  arr.emplace_back(2);
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

void CapacityTest() {
  std::vector<A> arr(10);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;

  // Requests that the vector capacity be at least enough to contain n elements.
  arr.reserve(3);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;

  arr.resize(4);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  // 内部会调用拷贝
  arr.resize(5, 10);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  arr.push_back(6);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  arr.assign(2, 10);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  // 比较奇怪
  arr.insert(arr.begin() + 11, 20);
  std::cout << "capacity: " << arr.capacity() << ", size: " << arr.size() << std::endl;
  for (const auto& val : arr) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::cout << "-------------------------------------MemberType-----------------------------------"
            << std::endl;
  MemberType();
  std::cout
      << "-------------------------------------ConstructFun-----------------------------------"
      << std::endl;
  ConstructFun();
  std::cout << "-------------------------------------MemberFun-----------------------------------"
            << std::endl;
  MemberFun();
  std::cout
      << "-------------------------------------CapacityTest-----------------------------------"
      << std::endl;
  CapacityTest();
}