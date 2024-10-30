#include <set>
#include <iostream>
#include <string>

// template < class T,                        // set::key_type/value_type
//            class Compare = less<T>,        // set::key_compare/value_compare           
//            class Alloc = allocator<T>      // set::allocator_type           
// > class set;

class A {
public:
    A() {
        std::cout << "construct" << std::endl;
    }
    explicit A(int a):a(a) {
        std::cout << "another construct" << std::endl;
    }
    ~A() {
        std::cout << "deconstruct" << std::endl;
    }

    A(const A &) {
        std::cout << "copy construct" << std::endl;
    }

    A& operator=(const A &) {
        std::cout << "copy assign construct" << std::endl;
        return *this;
    }

    A(A&&) {
        std::cout << "move construct" << std::endl;
    }

    A& operator=(A&&) {
        std::cout << "move assign construct" << std::endl;
        return *this;
    }

    bool operator<(const A &a) const {
        return this->a < a.a;
    }

    friend std::ostream& operator<<(std::ostream &output, const A &a) { 
        output << a.a;
        return output;            
    }

    bool operator==(const A &a) const {
        return this->a != a.a;
    }

public:
    int a = 0;
    double b = 0.0;
};

void BasicSetMemberTypes() {
    std::set<int> s;
    if(std::is_same<std::set<int>::key_type, int>::value) {
      std::cout << "set<int>::key_type is int" << std::endl;
    }
    if(std::is_same<std::set<int>::value_type, int>::value) {
      std::cout << "set<int>::value_type is int" << std::endl;
    }
    if(std::is_same<std::set<int>::key_compare, std::less<int>>::value) {
      std::cout << "set<int>::key_compare is std::less<int>" << std::endl;
    }
    if(std::is_same<std::set<int>::value_compare, std::less<int>>::value) {
      std::cout << "set<int>::value_compare is std::less<int>" << std::endl;
    }
    if(std::is_same<std::set<int>::allocator_type, std::allocator<int>>::value) {
      std::cout << "set<int>::allocator_type is std::allocator<int>" << std::endl;
    }
    if(std::is_same<std::set<int>::reference, int&>::value) {
      std::cout << "set<int>::reference is int&" << std::endl;
    }
    if(std::is_same<std::set<int>::pointer, int*>::value) {
      std::cout << "set<int>::pointer is int*" << std::endl;
    }
    if(std::is_same<std::set<int>::pointer, std::allocator<int>::pointer>::value) {
      std::cout << "set<int>::pointer is std::allocator<int>::pointer" << std::endl;
    }
    if(std::is_same<std::set<int>::iterator, std::iterator<std::bidirectional_iterator_tag, int>>::value) {
      std::cout << "set<int>::iterator is std::iterator<std::bidirectional_iterator_tag, int>" << std::endl;
    } else {
      std::cout << "set<int>::iterator is not std::iterator<std::bidirectional_iterator_tag, int>" << std::endl;
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

  //1.iterator，看起来是个双向的迭代器
  std::cout << "s.begin: " << *s.begin() << std::endl;
  std::cout << "s.end: " << *(--s.end()) << std::endl;
  std::cout << "s.rbegin: " << *s.rbegin() << std::endl;
  std::cout << "s.rend: " << *(--s.rend()) << std::endl;
  std::cout << "s.cbegin: " << *s.cbegin() << std::endl;
  std::cout << "s.cend: " << *(--s.cend()) << std::endl;
  std::cout << "s.crbegin: " << *s.crbegin() << std::endl;
  std::cout << "s.crend: " << *(--s.crend()) << std::endl;

  //2.capacity
  std::cout << "s.size: " << s.size() << std::endl;
  std::cout << "s.max_size: " << s.max_size() << std::endl;
  std::cout << "s.empty: " << s.empty() << std::endl;

  //3.modifiers
  std::pair<std::set<std::string>::iterator, bool> ret = s.insert("6");
  if(ret.second) {
    std::cout << "insert 6: " << ret.second << ", value: " << *(ret.first) << std::endl;
  } else {
    std::cout << "insert 6 failed" << std::endl;
  }

  std::pair<std::set<std::string>::iterator, bool> ret2 = s.insert("6");
  if(ret2.second) {
    std::cout << "insert 6: " << ret2.second << ", value: " << *(ret2.first) << std::endl;
  } else {
    std::cout << "insert 6 failed" << std::endl;
  }

}

void Insert() {
  //3.modifiers
  A a(11);
  A b(12);
  A c(13);
  std::set<A> s1;
  std::pair<std::set<A>::iterator, bool> ret = s1.insert(a);
  if(ret.second) {
    std::cout << "insert a: " << ret.second << ", value: " << *(ret.first) << std::endl;
  } else {
    std::cout << "insert a failed" << std::endl;
  }

  std::pair<std::set<A>::iterator, bool> ret2 = s1.insert(c);
  if(ret2.second) {
    std::cout << "insert a: " << ret2.second << ", value: " << *(ret2.first) << std::endl;
  } else {
    std::cout << "insert a failed" << std::endl;
  }
}

int main() {
  std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
  BasicSetMemberTypes();
  std::cout << "--------------------------------BasicMember--------------------------------" << std::endl;
  BasicMember();
  std::cout << "--------------------------------BasicConstructor--------------------------------" << std::endl;
  BasicConstructor();
  std::cout << "--------------------------------Insert--------------------------------" << std::endl;
  Insert();
  return 0;
} 