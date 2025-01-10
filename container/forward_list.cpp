#include <forward_list>
#include <iostream>
#include <string>
#include <type_traits>

// template<
//     class T,
//     class Alloc = std::allocator<T>
// > class forward_list;

class A {
 public:
  A() { std::cout << "construct" << std::endl; }

  explicit A(std::string a) : a(a) { std::cout << "another construct" << std::endl; }

  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A& other) {
    std::cout << "copy construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(const A& other) {
    std::cout << "copy assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  A(A&& other) {
    std::cout << "move construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(A&& other) {
    std::cout << "move assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  bool operator<(const A& a) const {
    std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
    return this->a < a.a;
  }

  friend std::ostream& operator<<(std::ostream& output, const A& a) {
    output << a.a;
    return output;
  }

  bool operator==(const A& a) const {
    std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
    return this->a == a.a;
  }

 public:
  std::string a = "";
};

void BasicSetMemberTypes() {
  std::forward_list<int> forward_list;
  if (std::is_same<std::forward_list<int>::value_type, int>::value) {
    std::cout << "value_type is int" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::allocator_type, std::allocator<int>>::value) {
    std::cout << "allocator_type is std::allocator<int>" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::reference, int&>::value) {
    std::cout << "reference is int&" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::const_reference, const int&>::value) {
    std::cout << "const_reference is const int&" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::pointer, int*>::value) {
    std::cout << "pointer is int*" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::const_pointer, const int*>::value) {
    std::cout << "const_pointer is const int*" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::iterator, std::_Fwd_list_iterator<int>>::value) {
    std::cout << "iterator is std::_Fwd_list_iterator<int>" << std::endl;
  } else {
    std::cout << "iterator is not std::_Fwd_list_iterator<int>" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::const_iterator,
                   std::_Fwd_list_const_iterator<int>>::value) {
    std::cout << "const_iterator is std::_Fwd_list_const_iterator<int>" << std::endl;
  } else {
    std::cout << "const_iterator is not std::_Fwd_list_const_iterator<int>" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::size_type, std::size_t>::value) {
    std::cout << "size_type is std::size_t" << std::endl;
  }
  if (std::is_same<std::forward_list<int>::difference_type, std::ptrdiff_t>::value) {
    std::cout << "difference_type is std::ptrdiff_t" << std::endl;
  }
}

void ConFun() {
  std::forward_list<int> first;                                // default: empty
  std::forward_list<int> second_1(3);                          // fill: 3 seventy-sevens
  std::forward_list<int> second(3, 77);                        // fill: 3 seventy-sevens
  std::forward_list<int> third(second.begin(), second.end());  // range initialization
  std::forward_list<int> fourth(third);                        // copy constructor
  std::forward_list<int> fifth(std::move(fourth));             // move ctor. (fourth wasted)
  std::forward_list<int> sixth = {3, 52, 25, 90};              // initializer_list constructor

  std::cout << "first:";
  for (int& x : first) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "second_1:";
  for (int& x : second_1) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "second:";
  for (int& x : second) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "third:";
  for (int& x : third) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "fourth:";
  for (int& x : fourth) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "fifth:";
  for (int& x : fifth) std::cout << " " << x;
  std::cout << '\n';
  std::cout << "sixth:";
  for (int& x : sixth) std::cout << " " << x;
  std::cout << '\n';
}

void MemFun() {
  std::forward_list<int> my_list = {1, 2, 3, 4, 5};

  // 1. iterator
  std::forward_list<int>::iterator it =
      my_list.before_begin();  // 不要解引用，这个是为了emplace_after等接口使用的
  std::forward_list<int>::iterator it1 = my_list.begin();
  std::cout << "my_list.begin():" << *it1 << std::endl;
  std::forward_list<int>::iterator it2 = my_list.end();
  std::forward_list<int>::const_iterator it3 = my_list.cbefore_begin();
  std::forward_list<int>::const_iterator it4 = my_list.cbegin();
  std::cout << "my_list.cbegin():" << *it4 << std::endl;
  std::forward_list<int>::const_iterator it5 = my_list.cend();

  // 2. capacity
  std::cout << "my_list.empty():" << my_list.empty() << std::endl;
  std::cout << "my_list.max_size():" << my_list.max_size() << std::endl;

  // 3. element access
  std::forward_list<int>::reference ref = my_list.front();
  std::cout << "my_list.front():" << ref << std::endl;
  ref = 20;
  std::cout << "my_list.front():" << my_list.front() << std::endl;

  // 4. modifiers
  // 4.1 assign
  int arr[] = {1, 2, 3, 4, 5};
  my_list.assign(arr, arr + 5);
  my_list.assign(5, 100);
  my_list.assign({6, 7, 8, 9, 10});
  // 4.2 emplace_front
  my_list.emplace_front(11);
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  // 4.3 push_front
  my_list.push_front(10);
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  // 4.4 pop_front
  my_list.pop_front();
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  // 4.5 emplace_after
  std::forward_list<int>::iterator it6 = my_list.emplace_after(my_list.begin(), 12);
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  std::cout << "it6:" << *it6 << std::endl;
  // 4.6 insert_after
  // return: An iterator that points to the last of the newly inserted elements, or position if no
  // element was inserted.
  std::forward_list<int>::iterator it7 = my_list.insert_after(my_list.begin(), 13);
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  std::cout << "it7:" << *it7 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it7) << std::endl;
  std::forward_list<int>::iterator it8 = my_list.insert_after(my_list.begin(), 4, 14);
  std::cout << "my_list.begin():" << *my_list.begin() << std::endl;
  std::cout << "it8:" << *it8 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it8) << std::endl;
  std::forward_list<int>::iterator it9 = my_list.insert_after(my_list.begin(), {15, 16, 17});
  std::cout << "it9:" << *it9 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it9) << std::endl;
  std::forward_list<int>::iterator it10 = my_list.insert_after(my_list.begin(), arr, arr + 5);
  std::cout << "it10:" << *it10 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it10) << std::endl;
  // 4.7 erase_after
  std::forward_list<int>::iterator it11 = my_list.erase_after(my_list.begin());
  std::cout << "it11:" << *it11 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it11) << std::endl;
  std::forward_list<int>::iterator it12 = my_list.erase_after(my_list.begin(), it11);
  std::cout << "it12:" << *it12 << std::endl;
  std::cout << "distance:" << std::distance(my_list.begin(), it12) << std::endl;
  // 4.8 swap
  std::forward_list<int> my_list1 = {1, 2, 3, 4, 5};
  my_list.swap(my_list1);
  // 4.9 resize
  my_list.resize(10);
  my_list.resize(15, 100);
  // 4.10 clear
  my_list1.clear();

  // 5. operations
  // 5.1 splice_after
  std::forward_list<int> my_list2 = {1, 2, 3, 4, 5};
  std::forward_list<int> my_list3 = {6, 7, 8, 9, 10};
  std::forward_list<int> my_list4 = {11, 12, 13, 14, 15};
  my_list2.splice_after(my_list2.before_begin(), my_list3);
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // 指向迭代器要传输位置之前的元素
  my_list2.splice_after(my_list2.before_begin(), my_list4, my_list4.before_begin());
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // transfers the range (first,last) from fwdlst into the container.
  my_list2.splice_after(my_list2.before_begin(), my_list4, my_list4.before_begin(), my_list4.end());
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // 5.2 remove
  my_list2.remove(1);
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // a predicate implemented as a function:
  auto single_digit = [](const int& value) -> bool { return (value < 10); };
  // a predicate implemented as a class:
  struct is_odd_class {
   public:
    bool operator()(const int& value) { return (value % 2) == 1; }
  };
  my_list2.remove_if(single_digit);
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  my_list2.remove_if(is_odd_class());
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // 5.3 unique
  my_list2.unique();
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // a binary predicate implemented as a function:
  auto same_integral_part = [](int first, int second) { return (first == second); };
  // a binary predicate implemented as a class:
  struct is_near_class {
   public:
    bool operator()(int first, int second) { return ((first - second) < 5); }
  };
  my_list2.unique(same_integral_part);
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  //  binary_pred(*i,*(i-1)), i start from second, remove i from the forward_list if the predicate
  //  returns true.
  my_list2.unique(is_near_class());
  std::cout << "my_list2:";
  for (int& x : my_list2) std::cout << " " << x;
  std::cout << '\n';
  // 5.4 merge
  std::forward_list<int> my_list5 = {1, 3, 5, 7, 9};
  std::forward_list<int> my_list6 = {2, 4, 6, 8, 10};
  std::forward_list<int> my_list7 = {1, 3, 5, 7, 9};
  std::forward_list<int> my_list8 = {2, 4, 6, 8, 10};
  my_list5.merge(my_list6);
  std::cout << "my_list5:";
  for (int& x : my_list5) std::cout << " " << x;
  std::cout << '\n';
  my_list7.merge(my_list8, [](int first, int second) { return (first < second); });
  std::cout << "my_list7:";
  for (int& x : my_list7) std::cout << " " << x;
  std::cout << '\n';
  // 5.5 sort
  std::forward_list<int> my_list9 = {5, 3, 1, 2, 4};
  my_list9.sort();
  std::cout << "my_list9:";
  for (int& x : my_list9) std::cout << " " << x;
  std::cout << '\n';
  my_list9.sort([](int first, int second) { return (first > second); });
  std::cout << "my_list9:";
  for (int& x : my_list9) std::cout << " " << x;
  std::cout << '\n';
  // 5.6 reverse
  my_list9.reverse();
  std::cout << "my_list9:";
  for (int& x : my_list9) std::cout << " " << x;
  std::cout << '\n';
}

int main() {
  std::cout << "--------------------------------BasicSetMemberTypes--------------------------------"
            << std::endl;
  BasicSetMemberTypes();
  std::cout << "--------------------------------ConFun--------------------------------"
            << std::endl;
  ConFun();
  std::cout << "--------------------------------MemFun--------------------------------"
            << std::endl;
  MemFun();
}