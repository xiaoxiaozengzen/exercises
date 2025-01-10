#include <iostream>
#include <set>
#include <string>

// template < class T,                        // set::key_type/value_type
//            class Compare = less<T>,        // set::key_compare/value_compare
//            class Alloc = allocator<T>      // set::allocator_type
// > class set;

class A {
 public:
  A() { std::cout << "construct" << std::endl; }
  explicit A(int a) : a(a) { std::cout << "another construct" << std::endl; }
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
  int a = 0;
};

void BasicSetMemberTypes() {
  std::set<int> s;
  if (std::is_same<std::set<int>::key_type, int>::value) {
    std::cout << "set<int>::key_type is int" << std::endl;
  }
  if (std::is_same<std::set<int>::value_type, int>::value) {
    std::cout << "set<int>::value_type is int" << std::endl;
  }
  if (std::is_same<std::set<int>::key_compare, std::less<int>>::value) {
    std::cout << "set<int>::key_compare is std::less<int>" << std::endl;
  }
  if (std::is_same<std::set<int>::value_compare, std::less<int>>::value) {
    std::cout << "set<int>::value_compare is std::less<int>" << std::endl;
  }
  if (std::is_same<std::set<int>::allocator_type, std::allocator<int>>::value) {
    std::cout << "set<int>::allocator_type is std::allocator<int>" << std::endl;
  }
  if (std::is_same<std::set<int>::reference, int&>::value) {
    std::cout << "set<int>::reference is int&" << std::endl;
  }
  if (std::is_same<std::set<int>::pointer, int*>::value) {
    std::cout << "set<int>::pointer is int*" << std::endl;
  }
  if (std::is_same<std::set<int>::pointer, std::allocator<int>::pointer>::value) {
    std::cout << "set<int>::pointer is std::allocator<int>::pointer" << std::endl;
  }
  if (std::is_same<std::set<int>::iterator,
                   std::iterator<std::bidirectional_iterator_tag, int>>::value) {
    std::cout << "set<int>::iterator is std::iterator<std::bidirectional_iterator_tag, int>"
              << std::endl;
  } else {
    std::cout << "set<int>::iterator is not std::iterator<std::bidirectional_iterator_tag, int>"
              << std::endl;
  }
}

void BasicConstructor() {
  // empty
  std::set<int> s1;

  // initializer list
  std::set<int> s2 = {1, 2, 3, 4, 5};

  // copy
  std::set<int> s3(s2);

  // range
  std::set<int> s4(s2.begin(), s2.end());

  // move
  std::set<int> s5 = s2;
  std::set<int> s6 = std::move(s2);
}

void BasicMember() {
  std::set<std::string> s = {"1", "2", "3", "4", "5"};

  // 1.iterator，看起来是个双向的迭代器
  std::cout << "s.begin: " << *s.begin() << std::endl;
  std::cout << "s.end: " << *(--s.end()) << std::endl;
  std::cout << "s.rbegin: " << *s.rbegin() << std::endl;
  std::cout << "s.rend: " << *(--s.rend()) << std::endl;
  std::cout << "s.cbegin: " << *s.cbegin() << std::endl;
  std::cout << "s.cend: " << *(--s.cend()) << std::endl;
  std::cout << "s.crbegin: " << *s.crbegin() << std::endl;
  std::cout << "s.crend: " << *(--s.crend()) << std::endl;

  // 2.capacity
  std::cout << "s.size: " << s.size() << std::endl;
  std::cout << "s.max_size: " << s.max_size() << std::endl;
  std::cout << "s.empty: " << s.empty() << std::endl;

  // 3.modifiers
  // 3.1 insert
  std::pair<std::set<std::string>::iterator, bool> ret = s.insert("6");
  if (ret.second) {
    std::cout << "insert 6: " << ret.second << ", value: " << *(ret.first) << std::endl;
  } else {
    std::cout << "insert 6 failed, old is: " << *(ret.first) << std::endl;
  }

  std::pair<std::set<std::string>::iterator, bool> ret2 = s.insert("6");
  if (ret2.second) {
    std::cout << "insert 6: " << ret2.second << ", value: " << *(ret2.first) << std::endl;
  } else {
    std::cout << "insert 6 failed, old is: " << *(ret2.first) << std::endl;
  }

  std::set<std::string>::iterator ret3 = s.insert(s.end(), "7");
  std::cout << "insert 7: " << *ret3 << std::endl;

  std::string v[3] = {"7", "8", "9"};
  s.insert(v, v + 3);
  std::cout << "s.size: " << s.size() << std::endl;

  s.insert({"10", "11", "12"});
  std::cout << "s.size: " << s.size() << std::endl;

  std::cout << "s: ";
  for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // 3.2. erase
  std::set<std::string>::iterator ret4 = s.erase(s.begin());  // 被擦除元素的紧邻元素
  if (ret4 != s.end()) {
    std::cout << "erase begin: " << *ret4 << std::endl;
  } else {
    std::cout << "erase begin failed" << std::endl;
  }

  int ret5 = s.erase("7");
  std::cout << "erase 7: " << ret5 << std::endl;

  std::set<std::string>::iterator ret6 = s.erase(s.begin(), ++s.begin());
  if (ret6 != s.end()) {
    std::cout << "erase begin begin+2: " << *ret6 << std::endl;
  } else {
    std::cout << "erase begin failed" << std::endl;
  }

  // 3.3. swap
  std::set<std::string> s2 = {"13", "14", "15"};
  s.swap(s2);

  // 3.4. clear
  // s.clear();

  // 3.5. emplace
  std::pair<std::set<std::string>::iterator, bool> ret7 = s.emplace("16");
  if (ret7.second) {
    std::cout << "emplace 16: " << ret7.second << ", value: " << *(ret7.first) << std::endl;
  } else {
    std::cout << "emplace 16 failed, old is: " << *(ret7.first) << std::endl;
  }
  std::pair<std::set<std::string>::iterator, bool> ret8 = s.emplace("16");
  if (ret8.second) {
    std::cout << "emplace 16: " << ret8.second << ", value: " << *(ret8.first) << std::endl;
  } else {
    std::cout << "emplace 16 failed, old is: " << *(ret8.first) << std::endl;
  }

  // 3.6. emplace_hint
  std::set<std::string>::iterator ret9 = s.emplace_hint(s.end(), "17");
  std::cout << "emplace_hint 17: " << *ret9 << std::endl;

  // 4. observers
  std::set<std::string>::key_compare com = s.key_comp();
  std::cout << "key_comp: " << com("1", "2") << std::endl;

  std::set<std::string>::value_compare com2 = s.value_comp();
  std::cout << "value_comp: " << com2("1", "2") << std::endl;

  std::cout << "s: ";
  for (auto it = s.begin(); it != s.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // 5. operations
  std::set<std::string>::iterator ret10 = s.find("16");
  if (ret10 != s.end()) {
    std::cout << "find 16: " << *ret10 << std::endl;
  } else {
    std::cout << "find 16 failed" << std::endl;
  }

  std::cout << "count 16: " << s.count("16") << std::endl;

  std::set<std::string>::iterator itlow, itup;
  // lower_bound: The function uses its internal comparison object (key_comp) to determine this,
  // returning an iterator to the first element for which key_comp(element,val) would return false.
  // upper_bound: The function uses its internal comparison object (key_comp) to determine this,
  // returning an iterator to the first element for which key_comp(val,element) would return true.
  itlow = s.lower_bound("12");
  itup = s.upper_bound("13");
  std::cout << "lower_bound 12: " << *itlow << std::endl;
  std::cout << "upper_bound 13: " << *itup << std::endl;

  std::pair<std::set<std::string>::iterator, std::set<std::string>::iterator> ret11 =
      s.equal_range("14");
  std::cout << "equal_range 14: " << *ret11.first << ", " << *ret11.second << std::endl;

  // 6. allocator
  std::allocator<std::string> alloc = s.get_allocator();
  std::string* p = alloc.allocate(5);
  *p = "18";
  std::cout << "alloc address: " << p << ", value: " << *p << std::endl;
  alloc.deallocate(p, 5);
}

void Insert() {
  // 3.modifiers
  A a(12);
  A b(12);
  A c(13);
  A d(10);
  A e(11);
  std::set<A> s1;
  std::pair<std::set<A>::iterator, bool> ret = s1.insert(a);
  if (ret.second) {
    std::cout << "insert a: " << ret.second << ", value: " << *(ret.first) << std::endl;
  } else {
    std::cout << "insert a failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret2 = s1.insert(c);
  if (ret2.second) {
    std::cout << "insert c: " << ret2.second << ", value: " << *(ret2.first) << std::endl;
  } else {
    std::cout << "insert c failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret3 = s1.insert(b);
  if (ret3.second) {
    std::cout << "insert b: " << ret3.second << ", value: " << *(ret3.first) << std::endl;
  } else {
    std::cout << "insert b failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret4 = s1.insert(d);
  if (ret4.second) {
    std::cout << "insert d: " << ret4.second << ", value: " << *(ret4.first) << std::endl;
  } else {
    std::cout << "insert d failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret5 = s1.insert(e);
  if (ret5.second) {
    std::cout << "insert e: " << ret5.second << ", value: " << *(ret5.first) << std::endl;
  } else {
    std::cout << "insert e failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret6 = s1.emplace(14);
  if (ret6.second) {
    std::cout << "insert 14: " << ret6.second << ", value: " << *(ret6.first) << std::endl;
  } else {
    std::cout << "insert 14 failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret7 = s1.emplace(14);
  if (ret7.second) {
    std::cout << "insert 14: " << ret7.second << ", value: " << *(ret7.first) << std::endl;
  } else {
    std::cout << "insert 14 failed" << std::endl;
  }

  std::cout << "s1 size: " << s1.size() << std::endl;

  if (a < b) {
    std::cout << "a < b" << std::endl;
  } else {
    std::cout << "a !< b" << std::endl;
  }

  if (b < a) {
    std::cout << "b < a" << std::endl;
  } else {
    std::cout << "b !< a" << std::endl;
  }
}

int main() {
  std::cout << "--------------------------------BasicSetMemberTypes--------------------------------"
            << std::endl;
  BasicSetMemberTypes();
  std::cout << "--------------------------------BasicMember--------------------------------"
            << std::endl;
  BasicMember();
  std::cout << "--------------------------------BasicConstructor--------------------------------"
            << std::endl;
  BasicConstructor();
  std::cout << "--------------------------------Insert--------------------------------"
            << std::endl;
  Insert();
  return 0;
}