#include <iostream>
#include <list>

// template<
//     class T,
//     class Alloc = std::allocator<T>
// > class list;

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
  std::list<int> list_int;
  if (std::is_same<std::list<int>::value_type, int>::value) {
    std::cout << "list_int.value_type is int" << std::endl;
  }
  if (std::is_same<std::list<int>::allocator_type, std::allocator<int>>::value) {
    std::cout << "list_int.allocator_type is std::allocator<int>" << std::endl;
  }
  if (std::is_same<std::list<int>::reference, int&>::value) {
    std::cout << "list_int.reference is int&" << std::endl;
  } else {
    std::cout << "list_int.reference is not int&" << std::endl;
  }
  if (std::is_same<std::list<int>::const_reference, const int&>::value) {
    std::cout << "list_int.const_reference is const int&" << std::endl;
  } else {
    std::cout << "list_int.const_reference is not const int&" << std::endl;
  }
  if (std::is_same<std::list<int>::pointer, int*>::value) {
    std::cout << "list_int.pointer is int*" << std::endl;
  } else {
    std::cout << "list_int.pointer is not int*" << std::endl;
  }
  if (std::is_same<std::list<int>::const_pointer, const int*>::value) {
    std::cout << "list_int.const_pointer is const int*" << std::endl;
  } else {
    std::cout << "list_int.const_pointer is not const int*" << std::endl;
  }
  if (std::is_same<std::list<int>::iterator, std::_List_iterator<int>>::value) {
    std::cout << "list_int.iterator is std::_List_iterator<int>" << std::endl;
  } else {
    std::cout << "list_int.iterator is not std::_List_iterator<int>" << std::endl;
  }
  if (std::is_same<std::list<int>::const_iterator, std::_List_const_iterator<int>>::value) {
    std::cout << "list_int.const_iterator is std::_List_const_iterator<int>" << std::endl;
  } else {
    std::cout << "list_int.const_iterator is not std::_List_const_iterator<int>" << std::endl;
  }
  if (std::is_same<std::list<int>::reverse_iterator,
                   std::reverse_iterator<std::_List_iterator<int>>>::value) {
    std::cout << "list_int.reverse_iterator is std::reverse_iterator<std::_List_iterator<int>>"
              << std::endl;
  } else {
    std::cout << "list_int.reverse_iterator is not std::reverse_iterator<std::_List_iterator<int>>"
              << std::endl;
  }
  if (std::is_same<std::list<int>::const_reverse_iterator,
                   std::reverse_iterator<std::_List_const_iterator<int>>>::value) {
    std::cout << "list_int.const_reverse_iterator is "
                 "std::reverse_iterator<std::_List_const_iterator<int>>"
              << std::endl;
  } else {
    std::cout << "list_int.const_reverse_iterator is not "
                 "std::reverse_iterator<std::_List_const_iterator<int>>"
              << std::endl;
  }
  if (std::is_same<std::list<int>::difference_type, std::ptrdiff_t>::value) {
    std::cout << "list_int.difference_type is std::ptrdiff_t" << std::endl;
  } else {
    std::cout << "list_int.difference_type is not std::ptrdiff_t" << std::endl;
  }
  if (std::is_same<std::list<int>::size_type, std::size_t>::value) {
    std::cout << "list_int.size_type is std::size_t" << std::endl;
  } else {
    std::cout << "list_int.size_type is not std::size_t" << std::endl;
  }
}

void ConFun() {
  // constructors used in the same order as described above:
  std::list<int> first;                                // empty list of ints
  std::list<int> an_first(4);                          // four ints
  std::list<int> second(4, 100);                       // four ints with value 100
  std::list<int> third(second.begin(), second.end());  // iterating through second
  std::list<int> fourth(third);                        // a copy of third
  std::list<int> an_fourth = {16, 2, 77, 29};          // list initialization

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16, 2, 77, 29};
  std::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  std::cout << "The contents of fifth are: ";
  for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
    std::cout << *it << ' ';

  std::cout << '\n';
}

void MemFun() {
  std::list<int> mylist = {2, 16, 77, 29};

  // 1. iterator
  std::list<int>::iterator it = mylist.begin();
  std::cout << "mylist.begin(): " << *it << std::endl;
  std::list<int>::iterator it2 = mylist.end();
  it2--;
  std::cout << "mylist.end(): " << *(it2) << std::endl;
  std::list<int>::reverse_iterator rit = mylist.rbegin();
  std::cout << "mylist.rbegin(): " << *rit << std::endl;
  std::list<int>::reverse_iterator rit2 = mylist.rend();
  rit2--;
  std::cout << "mylist.rend(): " << *(rit2) << std::endl;
  std::list<int>::const_iterator cit = mylist.cbegin();
  std::cout << "mylist.cbegin(): " << *cit << std::endl;
  std::list<int>::const_reverse_iterator crit = mylist.crbegin();
  std::cout << "mylist.crbegin(): " << *crit << std::endl;

  // 2. capacity
  std::cout << "mylist.size(): " << mylist.size() << std::endl;
  std::cout << "mylist.max_size(): " << mylist.max_size() << std::endl;
  std::cout << "mylist.empty(): " << mylist.empty() << std::endl;

  // 3. element access
  std::list<int>::reference ref = mylist.front();
  ref = 100;
  std::cout << "mylist.begin(): " << *mylist.begin() << std::endl;
  std::list<int>::reference ref2 = mylist.back();
  ref2 = 200;
  std::cout << "mylist.rbegin(): " << *mylist.rbegin() << std::endl;

  // 4. modifiers
  // 4.1 assign
  int myints[] = {16, 2, 77, 29};
  mylist.assign(myints, myints + 4);
  mylist.assign(4, 100);
  mylist.assign({1, 2, 3, 4, 5});
  // 4.2 emplace_front
  mylist.emplace_front(10);
  std::cout << "mylist.begin(): " << *mylist.begin() << std::endl;
  // 4.3 push_front
  mylist.push_front(20);
  std::cout << "mylist.begin(): " << *mylist.begin() << std::endl;
  // 4.4 pop_front
  mylist.pop_front();
  std::cout << "mylist.begin(): " << *mylist.begin() << std::endl;
  // 4.4 emplace_back
  mylist.emplace_back(30);
  std::cout << "mylist.rbegin(): " << *mylist.rbegin() << std::endl;
  // 4.5 push_back
  mylist.push_back(40);
  std::cout << "mylist.rbegin(): " << *mylist.rbegin() << std::endl;
  // 4.6 pop_back
  mylist.pop_back();
  std::cout << "mylist.rbegin(): " << *mylist.rbegin() << std::endl;
  // 4.7 emplace
  std::list<int>::iterator em_1 = mylist.emplace(mylist.begin(), 50);
  std::cout << "em_1: " << *em_1 << std::endl;
  // 4.8 insert
  std::list<int>::iterator in_1 = mylist.insert(mylist.begin(), 60);
  std::cout << "in_1: " << *in_1 << std::endl;
  std::list<int>::iterator in_2 = mylist.insert(mylist.begin(), 2, 70);
  std::cout << "in_2: " << *in_2 << std::endl;
  std::list<int>::iterator in_3 = mylist.insert(mylist.begin(), myints, myints + 4);
  std::cout << "in_3: " << *in_3 << std::endl;
  std::list<int>::iterator in_4 = mylist.insert(mylist.begin(), {1, 2, 3, 4, 5});
  std::cout << "in_4: " << *in_4 << std::endl;
  std::list<int>::iterator num1 = mylist.begin();
  std::list<int>::iterator num2 = mylist.begin();
  num2++;
  std::list<int>::iterator num3 = mylist.begin();
  num3++;
  num3++;
  std::list<int>::iterator num4 = num3;
  num4--;
  std::cout << "num1: " << *num1 << ", num2: " << *num2 << ", num3: " << *num3
            << ", num4: " << *num4 << std::endl;
  // 4.9 erase
  std::list<int>::iterator era_1 = mylist.erase(mylist.begin());
  std::cout << "era_1: " << *era_1 << std::endl;
  era_1++;
  era_1++;
  std::list<int>::iterator era_2 = mylist.erase(mylist.begin(), era_1);
  std::cout << "era_2: " << *era_2 << std::endl;
  // 4.10 swap
  std::list<int> mylist2 = {1, 2, 3, 4, 5};
  mylist.swap(mylist2);
  // 4.11 resize
  mylist.resize(10);
  std::list<int>::iterator res_1 = mylist.end();
  res_1--;
  std::cout << "res_1: " << *res_1 << std::endl;
  mylist.resize(15, 20);
  std::list<int>::iterator res_2 = mylist.end();
  res_2--;
  std::cout << "res_2: " << *res_2 << std::endl;

  // 5. operations
  // 5.1 splice
  std::list<int> mylist3 = {1, 2, 3, 4, 5};
  std::list<int> mylist4 = {6, 7, 8, 9, 10};
  std::list<int> mylist5 = {11, 12, 13, 14, 15};
  std::list<int> mylist6 = {16, 17, 18, 19, 20};
  mylist3.splice(mylist3.begin(), mylist4);
  std::cout << "mylist3.begin(): " << *mylist3.begin() << ", mylist3.size: " << mylist3.size()
            << std::endl;
  std::cout << "mylist4.size(): " << mylist4.size() << std::endl;
  mylist3.splice(mylist3.begin(), mylist5, mylist5.begin());
  std::cout << "mylist3.begin(): " << *mylist3.begin() << ", mylist3.size: " << mylist3.size()
            << std::endl;
  std::cout << "mylist5.begin(): " << *mylist5.begin() << ", mylist5.size: " << mylist5.size()
            << std::endl;
  mylist3.splice(mylist3.begin(), mylist6, mylist6.begin(), mylist6.end());
  std::cout << "mylist3.begin(): " << *mylist3.begin() << ", mylist3.size: " << mylist3.size()
            << std::endl;
  std::cout << "mylist6.size(): " << mylist6.size() << std::endl;
  // 5.2 remove
  mylist3.remove(22);
  std::cout << "mylist3.size(): " << mylist3.size() << std::endl;
  mylist3.remove(20);
  std::cout << "mylist3.size(): " << mylist3.size() << std::endl;
  // 5.3 remove_if
  // a predicate implemented as a function:
  auto single_digit = [](const int& value) -> bool { return (value < 10); };
  // a predicate implemented as a class:
  struct is_odd {
    bool operator()(const int& value) { return (value % 2) == 1; }
  };
  mylist3.remove_if(single_digit);
  std::cout << "mylist3.size(): " << mylist3.size() << std::endl;
  mylist3.remove_if(is_odd());
  std::cout << "mylist3.size(): " << mylist3.size() << std::endl;
  // 5.4 unique
  // Notice that an element is only removed from the list container if it compares equal to the
  // element immediately preceding it. Thus, this function is especially useful for sorted lists.
  std::list<int> mylist7 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  std::list<int> mylist8 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  mylist7.unique();
  std::cout << "mylist7.size(): " << mylist7.size() << std::endl;
  // a binary predicate implemented as a function:
  auto same_integral_part = [](int first, int second) -> bool { return (first == second); };
  // a binary predicate implemented as a class:
  struct is_near {
    bool operator()(int first, int second) { return ((first - second) < 5); }
  };
  mylist8.unique(same_integral_part);
  std::cout << "mylist8.size(): " << mylist8.size() << std::endl;
  // 5.5 merge
  std::list<int> mylist9 = {1, 3, 5, 7, 9};
  std::list<int> mylist10 = {1, 4, 5, 8, 10};
  std::list<int> mylist11 = {2, 5, 11};
  mylist9.merge(mylist10);
  std::cout << "mylist9.size(): " << mylist9.size() << std::endl;
  for (auto it = mylist9.begin(); it != mylist9.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  auto comp = [](int a, int b) -> bool { return a < b; };
  mylist9.merge(mylist11, comp);
  std::cout << "mylist9.size(): " << mylist9.size() << std::endl;
  for (auto it = mylist9.begin(); it != mylist9.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  // 5.6 sort
  mylist9.sort();
  std::cout << "mylist9.begin(): " << *mylist9.begin() << std::endl;
  mylist9.sort([](int a, int b) -> bool { return a > b; });
  std::cout << "mylist9.begin(): " << *mylist9.begin() << std::endl;
  // 5.7 reverse
  mylist9.reverse();
  std::cout << "mylist9.begin(): " << *mylist9.begin() << std::endl;
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