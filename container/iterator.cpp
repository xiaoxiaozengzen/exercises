#include <iterator>
#include <iostream>
#include <vector>
#include <typeinfo>

// template <class Category,              // iterator::iterator_category          
//           class T,                     // iterator::value_type          
//           class Distance = ptrdiff_t,  // iterator::difference_type          
//           class Pointer = T*,          // iterator::pointer          
//           class Reference = T&         // iterator::reference          > 
// class iterator;

class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator=(const MyIterator& mit) {p = mit.p;return *this;}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

void BasicIter() {
    int numbers[] = {1, 2, 3, 4, 5};
    MyIterator begin(numbers);
    MyIterator another_begin(begin);
    MyIterator end(numbers + 5);
    for (MyIterator it = another_begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void Input() {
    std::vector<int> nu;
    std::vector<int>::iterator it_nu = nu.begin();    

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v.begin();
    std::cout << "begin == end? " << (it == v.end()) << std::endl;
    std::cout << "begin: " << *it << std::endl;
}

void Output() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v.begin();
    *it = 6;
    for(const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // 先使用it，再将it进行加1操作
    *it++ = 7;
    for(const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "it: " << *it << std::endl;

    /** seg fault */
    // std::vector<int>::iterator it2;
    // std::cout << "it2: " << *it2 << std::endl;
}

void Forward() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it;
    it = v.begin();
    std::cout << "it: " << *it << std::endl;

    std::vector<int>::iterator it2 = ++it;
    std::cout << "it2: " << *it2 << std::endl;

    it = it2;
    std::cout << "it: " << *it << std::endl;

    it++;
    std::cout << "it: " << *it << ", it2: " << *it2 << std::endl;
}

void Bidirectional() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v.end();

    it--;
    std::cout << "it: " << *it << std::endl;
}

void Random() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v.begin();

    std::vector<int>::iterator it2 = it + 2;
    std::cout << "it2: " << *it2 << std::endl;

    if (it < it2) {
        std::cout << "it < it2" << std::endl;
    } else {
        std::cout << "it >= it2" << std::endl;
    }

    it2 += 1;
    std::cout << "it2: " << *it2 << std::endl;

    std::cout << "it: " << it[2] << std::endl;
    std::cout << "it2: " << it2[-1] << std::endl;
}

void Traits() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int>::iterator it = v.begin();

    if(std::is_same<std::vector<int>::iterator::value_type, int>::value) {
        std::cout << "std::vector<int>::iterator::value_type is int" << std::endl;
    }

    if(std::is_same<std::iterator_traits<std::vector<int>::iterator>::value_type, int>::value) {
        std::cout << "value_type is int" << std::endl;
    }
    if(std::is_same<std::iterator_traits<std::vector<int>::iterator>::iterator_category, std::random_access_iterator_tag>::value) {
        std::cout << "iterator_category is random_access_iterator_tag" << std::endl;
    }
    if(std::is_same<std::iterator_traits<std::vector<int>::iterator>::difference_type, std::ptrdiff_t>::value) {
        std::cout << "difference_type is ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::iterator_traits<std::vector<int>::iterator>::pointer, int*>::value) {
        std::cout << "pointer is int*" << std::endl;
    }
    if(std::is_same<std::iterator_traits<std::vector<int>::iterator>::reference, int&>::value) {
        std::cout << "reference is int&" << std::endl;
    }
}

void Fun() {
    
}


int main() {
    std::cout << "--------------------------------BasicIter--------------------------------" << std::endl;
    BasicIter();
    std::cout << "--------------------------------Input--------------------------------" << std::endl;
    Input();
    std::cout << "--------------------------------Output--------------------------------" << std::endl;
    Output();
    std::cout << "--------------------------------Forward--------------------------------" << std::endl;
    Forward();
    std::cout << "--------------------------------Bidirectional--------------------------------" << std::endl;
    Bidirectional();
    std::cout << "--------------------------------Random--------------------------------" << std::endl;
    Random();
    std::cout << "--------------------------------Traits--------------------------------" << std::endl;
    Traits();
    return 0;
}