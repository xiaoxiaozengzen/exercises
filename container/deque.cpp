#include <deque>
#include <iostream>
#include <type_traits>

// template<
//     class T,
//     class Alloc = allocator<T>
// > class deque;

/**
参考：https://cplusplus.com/reference/deque/deque/
deque跟vector比较像，但：
deque在头部插入和删除元素的效率更高，
deque不保证元素在内存中是连续的，所以不要用地址加offest的形式访问元素
在频繁的中间插入和删除元素时，deque会更繁琐相比list。
 */

class A {
public:
  A() {
    std::cout << "construct" << std::endl;
  }

  A(int a):a(a) {
    std::cout << "construct with a" << std::endl;
  }

  ~A() {
    std::cout << "deconstruct" << std::endl;
  }

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
    std::deque<int> mydeque;
    if(std::is_same<std::deque<int>::value_type, int>::value) {
        std::cout << "value_type is int" << std::endl;
    }
    if(std::is_same<std::deque<int>::allocator_type, std::allocator<int>>::value) {
        std::cout << "allocator_type is std::allocator<int>" << std::endl;
    }
    if(std::is_same<std::deque<int>::size_type, std::size_t>::value) {
        std::cout << "size_type is std::size_t" << std::endl;
    }
    if(std::is_same<std::deque<int>::difference_type, std::ptrdiff_t>::value) {
        std::cout << "difference_type is std::ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::deque<int>::reference, int&>::value) {
        std::cout << "reference is int&" << std::endl;
    }
    if(std::is_same<std::deque<int>::const_reference, const int&>::value) {
        std::cout << "const_reference is const int&" << std::endl;
    }
    if(std::is_same<std::deque<int>::pointer, int*>::value) {
        std::cout << "pointer is int*" << std::endl;
    }
    if(std::is_same<std::deque<int>::const_pointer, const int*>::value) {
        std::cout << "const_pointer is const int*" << std::endl;
    }
    if(std::is_same<std::deque<int>::iterator, std::iterator<std::random_access_iterator_tag, int>>::value) {
        std::cout << "iterator is std::iterator<std::random_access_iterator_tag, int>" << std::endl;
    } else {
        std::cout << "iterator is not std::iterator<std::random_access_iterator_tag, int>" << std::endl;
    }
    if(std::is_same<std::deque<int>::const_iterator, std::deque<int>::const_pointer>::value) {
        std::cout << "const_iterator is const_pointer" << std::endl;
    }
}

void Construct() {
    std::deque<int> mydeque;
    std::deque<int> mydeque2(5);
    std::deque<int> mydeque3(5, 10);
    std::deque<int> mydeque4(mydeque3);
    std::deque<int> mydeque5(mydeque3.begin(), mydeque3.end());
    std::deque<int> mydeque6 = {1, 2, 3, 4, 5};
}

void capacity_test() {
    std::deque<A> deq(2);
    std::cout << "size: " << deq.size() << std::endl;
    for(auto& a : deq) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    deq.resize(5);
    std::cout << "size: " << deq.size() << std::endl;
    for(auto& a : deq) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    deq.resize(3, 2);
    std::cout << "size: " << deq.size() << std::endl;
    for(auto& a : deq) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    std::cout << "shrink_to_fit" << std::endl;
    deq.shrink_to_fit();
}

void MemberFun() {
    std::deque<int> deq = {1, 2, 3, 4, 5};
    
    // 1. iterator
    std::deque<int>::iterator it = deq.begin();
    std::cout << "begin: " << *it << std::endl;
    std::deque<int>::iterator it2 = deq.end();
    std::cout << "end: " << *(it2 - 1) << std::endl;
    std::deque<int>::const_iterator cit = deq.cbegin();
    std::cout << "cbegin: " << *cit << std::endl;
    std::deque<int>::const_iterator cit2 = deq.cend();
    std::cout << "cend: " << *(cit2 - 1) << std::endl;
    std::deque<int>::reverse_iterator rit = deq.rbegin();
    std::cout << "rbegin: " << *rit << std::endl;
    std::deque<int>::reverse_iterator rit2 = deq.rend();
    std::cout << "rend: " << *(rit2 - 1) << std::endl;
    std::deque<int>::const_reverse_iterator crit = deq.crbegin();
    std::cout << "crbegin: " << *crit << std::endl;
    std::deque<int>::const_reverse_iterator crit2 = deq.crend();
    std::cout << "crend: " << *(crit2 - 1) << std::endl;

    // 2. capacity
    std::cout << "size: " << deq.size() << std::endl;
    std::cout << "max_size: " << deq.max_size() << std::endl;
    std::cout << "empty: " << deq.empty() << std::endl;

    // 3. element access
    std::deque<int>::reference it3 = deq.front();
    std::cout << "front: " << it3 << std::endl;
    it3 = 11;
    std::cout << "begin: " << *(deq.begin()) << std::endl; 
    std::deque<int>::reference it4 = deq.back();
    std::cout << "back: " << it4 << std::endl;
    std::cout << "deq[0]: " << deq[0] << std::endl;
    std::cout << "deq.at(0): " << deq.at(0) << std::endl;

    // 4. modifier
    int array[] = {1, 2, 3, 4, 5};
    deq.assign(std::begin(array), std::end(array));
    std::cout << "size: " << deq.size() << std::endl;
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    deq.assign(5, 10);
    std::cout << "size: " << deq.size() << std::endl;
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    deq.assign({11, 12, 13});
    std::cout << "size: " << deq.size() << std::endl;
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    deq.push_back(14);
    deq.push_front(10);
    deq.pop_back();
    deq.pop_front();

    std::deque<int>::iterator it5 = deq.insert(deq.begin(), 1);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::deque<int>::iterator it6 = deq.insert(deq.end(), 2, 2);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::deque<int>::iterator it7 = deq.insert(deq.begin() + 1, {3, 4, 5});
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::deque<int>::iterator it8 = deq.insert(deq.begin() + 2, std::begin(array), std::end(array));
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::deque<int>::iterator it9 = deq.erase(deq.begin());
    std::cout << "it9: " << *it9 << std::endl;
    std::deque<int>::iterator it10 = deq.erase(deq.begin(), deq.begin() + 2);
    std::cout << "it10: " << *it10 << std::endl;

    std::deque<int> deq2;
    deq2.swap(deq);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    deq.clear();
    std::cout << "size: " << deq.size() << std::endl;

    deq.emplace(deq.begin(), 1);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    deq.emplace_back(2);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    deq.emplace_front(3);
    for(const auto& val : deq) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::cout << "------------ Member Type ------------" << std::endl;
    MemberType();
    std::cout << "------------ Construct ------------" << std::endl;
    Construct();
    std::cout << "------------ capacity_test ------------" << std::endl;
    capacity_test();
    std::cout << "------------ Member Function ------------" << std::endl;
    MemberFun();
}