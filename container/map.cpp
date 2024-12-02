#include <map>
#include <iostream>
#include <functional>
#include <utility>
#include <memory>

// template<
//     class Key,                                              // map::key_type
//     class T,                                                // map::mapped_type
//     class Compare = std::less<Key>,                         // map::key_compare
//     class Alloc = std::allocator<std::pair<const Key,T>>    // map::allocator_type           
// > class map;

/**
 * note: Maps are typically implemented as binary search trees.
 */

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

    bool operator<(const A &a) const {
      std::cout << "operator<, this " << this->a << ", other: " << a.a << std::endl;
      return this->a < a.a;
    }

    friend std::ostream& operator<<(std::ostream &output, const A &a) { 
        output << a.a;
        return output;            
    }

    bool operator==(const A &a) const {
      std::cout << "operator==, this " << this->a << ", other: " << a.a << std::endl;
      return this->a == a.a;
    }

public:
    int a = 0;
};

void BasicSetMemberTypes() {
    std::map<double, int> map1;
    if(std::is_same<std::map<double, int>::key_type, double>::value) {
        std::cout << "map::key_type is double" << std::endl;
    }
    if(std::is_same<std::map<double, int>::mapped_type, int>::value) {
        std::cout << "map::mapped_type is int" << std::endl;
    }
    if(std::is_same<std::map<double, int>::value_type, std::pair<const double, int>>::value) {
        std::cout << "map::value_type is std::pair<const double, int>" << std::endl;
    } else {
        std::cout << "map::value_type is not std::pair<double, int>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::key_compare, std::less<double>>::value) {
        std::cout << "map::key_compare is std::less<double>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::value_compare, std::less<double>>::value) {
        std::cout << "value_compare is std::less<double>" << std::endl;
    } else {
        std::cout << "value_compare is not std::less<double>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::allocator_type, std::allocator<std::pair<const double, int>>>::value) {
        std::cout << "map::allocator_type is std::allocator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::reference, std::pair<const double, int>&>::value) {
        std::cout << "map::reference is std::pair<const double, int>&" << std::endl;
    }
    if(std::is_same<std::map<double, int>::const_reference, const std::pair<const double, int>&>::value) {
        std::cout << "map::const_reference is const std::pair<const double, int>&" << std::endl;
    }
    if(std::is_same<std::map<double, int>::pointer, std::pair<const double, int>*>::value) {
        std::cout << "map::pointer is std::pair<const double, int>*" << std::endl;
    }
    if(std::is_same<std::map<double, int>::const_pointer, const std::pair<const double, int>*>::value) {
        std::cout << "map::const_pointer is const std::pair<const double, int>*" << std::endl;
    }
    if(std::is_same<std::map<double, int>::iterator, std::_Rb_tree_iterator<std::pair<const double, int>>>::value) {
        std::cout << "map::iterator is std::_Rb_tree_iterator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::const_iterator, int>::value) {
        std::cout << "map::const_iterator is std::_Rb_tree_const_iterator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::reverse_iterator, int>::value) {
        std::cout << "map::reverse_iterator is std::reverse_iterator<std::_Rb_tree_iterator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::const_reverse_iterator, int>::value) {
        std::cout << "map::const_reverse_iterator is std::reverse_iterator<std::_Rb_tree_const_iterator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::map<double, int>::difference_type, std::ptrdiff_t>::value) {
        std::cout << "map::difference_type is std::ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::map<double, int>::size_type, std::size_t>::value) {
        std::cout << "map::size_type is std::size_t" << std::endl;
    }
}

void ConstructFun() {
    std::map<char,int> first;

    first['a']=10;
    first['b']=30;
    first['c']=50;
    first['d']=70;

    // range constructor
    std::map<char,int> second (first.begin(),first.end());

    std::map<char,int> third (second);

    std::map<char,int> fourth;

    // initializer list constructor
    std::map<char, int> fifth = {
        {'a', 10},
        {'b', 30},
        {'c', 50},
        {'d', 70}
    };
}

void MemberFun() {
    std::map<char, int> map1 = {
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4}
    };

    // 1.iterator
    std::map<char, int>::iterator it = map1.begin();
    std::cout << "begin: " << it->first << ", " << it->second << std::endl;
    std::map<char, int>::const_iterator it2 = map1.end();
    it2--;
    std::cout << "end: " << it2->first << ", " << it2->second << std::endl;
    std::map<char, int>::reverse_iterator it3 = map1.rbegin();
    std::cout << "rbegin: " << it3->first << ", " << it3->second << std::endl;
    std::map<char, int>::const_reverse_iterator it4 = map1.rend();
    it4--;
    std::cout << "rend: " << it4->first << ", " << it4->second << std::endl;
    std::map<char, int>::const_iterator it5 = map1.cbegin();
    std::cout << "cbegin: " << it5->first << ", " << it5->second << std::endl;
    std::map<char, int>::const_iterator it6 = map1.cend();
    it6--;
    std::cout << "cend: " << it6->first << ", " << it6->second << std::endl;
    std::map<char, int>::const_reverse_iterator it7 = map1.crbegin();
    std::cout << "crbegin: " << it7->first << ", " << it7->second << std::endl;
    std::map<char, int>::const_reverse_iterator it8 = map1.crend();
    it8--;
    std::cout << "crend: " << it8->first << ", " << it8->second << std::endl;

    // 2.capacity
    std::cout << "size: " << map1.size() << std::endl;
    std::cout << "max_size: " << map1.max_size() << std::endl;
    std::cout << "empty: " << map1.empty() << std::endl;

    // 3. element access
    std::cout << "at: " << map1.at('a') << std::endl;
    std::cout << "operator[a]: " << map1['a'] << std::endl;
    // std::cout << "at: " << map1.at("e") << std::endl; // throw out_of_range
    std::cout << "operator[e]: " << map1['e'] << std::endl;

    // 4. modifiers
    // 4.1 insert
    std::pair<std::map<char, int>::iterator, bool> ret = map1.insert(std::pair<char, int>('f', 5));
    if(ret.second == true) {
        std::cout << "insert success, " << ret.first->second << std::endl;
    } else {
        std::cout << "insert failed" << std::endl;
    }
    std::pair<std::map<char, int>::iterator, bool> ret2 = map1.insert(std::pair<char, int>('f', 100));
    if(ret2.second == true) {
        std::cout << "insert success, " << ret2.first->second << std::endl;
    } else {
        std::cout << "insert failed" << std::endl;
    }
    std::pair<std::map<char, int>::iterator, bool> ret3 = map1.insert(std::pair<char, int>('e', 100));
    if(ret3.second == true) {
        std::cout << "insert success, " << ret3.first->second << std::endl;
    } else {
        std::cout << "insert failed" << std::endl;
    }
    std::map<char, int>::iterator it9 = map1.insert(map1.begin(), std::pair<char, int>('g', 6));
    std::cout << "insert: " << it9->first << ", " << it9->second << std::endl;
    std::map<char, int>::iterator it10 = map1.insert(map1.begin(), std::pair<char, int>('g', 100));
    std::cout << "insert: " << it10->first << ", " << it10->second << std::endl;
    std::map<char, int> map2 = {
        {'h', 7},
        {'i', 8},
        {'j', 9}
    };
    map1.insert(map2.begin(), map2.end());
    map1.insert({{'k', 10}, {'l', 11}});
    // 4.2 erase
    std::map<char, int>::iterator it11 = map1.erase(map1.begin());
    std::cout << "erase: " << it11->first << ", " << it11->second << std::endl;
    std::map<char, int>::size_type n = map1.erase('a');
    std::cout << "erase: " << n << std::endl;
    std::map<char, int>::size_type n2 = map1.erase('b');
    std::cout << "erase: " << n2 << std::endl;
    std::map<char, int>::iterator it12 = map1.erase(map1.begin(), map1.find('c'));
    std::cout << "erase: " << it12->first << ", " << it12->second << std::endl;
    // 4.3 swap
    map1.swap(map2);
    // 4.4 clear
    std::cout << "clear before size: " << map1.size() << std::endl; 
    map1.clear();
    std::cout << "clear after size: " << map1.size() << std::endl; 
    // 4.5 emplace
    std::pair<std::map<char, int>::iterator, bool> ret5 = map1.emplace('a', 1);
    if (ret5.second == true) {
        std::cout << "emplace success, " << ret5.first->first << ", " << ret5.first->second << std::endl;
    } else {
        std::cout << "emplace failed" << std::endl;
    }
    std::pair<std::map<char, int>::iterator, bool> ret6 = map1.emplace('a', 100);
    if (ret6.second == true) {
        std::cout << "emplace success, " << ret6.first->first << ", " << ret6.first->second << std::endl;
    } else {
        std::cout << "emplace failed" << std::endl;
    }
    // 4.6 emplace_hint
    std::map<char, int>::iterator it13 = map1.emplace_hint(map1.begin(), 'b', 2);
    std::cout << "emplace_hint: " << it13->first << ", " << it13->second << std::endl;
    std::map<char, int>::iterator it14 = map1.emplace_hint(map1.begin(), 'b', 200);
    std::cout << "emplace_hint: " << it14->first << ", " << it14->second << std::endl;
    
    // 5. observers
    std::map<char, int>::key_compare key_comp = map1.key_comp();
    std::cout << "key_comp: " << key_comp('a', 'b') << std::endl;
    std::map<char, int>::value_compare value_comp = map1.value_comp();
    std::cout << "value_comp: " << value_comp(std::pair<char, int>('a', 1), std::pair<char, int>('b', 2)) << std::endl;

    // 6. operations
    std::map<char, int>::iterator it15 = map1.find('a');
    if(it15 != map1.end()) {
        std::cout << "find: " << it15->first << ", " << it15->second << std::endl;
    } else {
        std::cout << "find failed" << std::endl;
    }
    std::map<char, int>::size_type n3 = map1.count('a');
    std::cout << "count: " << n3 << std::endl;
    std::map<char, int>::iterator it16 = map1.lower_bound('a');
    if(it16 != map1.end()) {
        std::cout << "lower_bound: " << it16->first << ", " << it16->second << std::endl;
    } else {
        std::cout << "lower_bound failed" << std::endl;
    }
    std::map<char, int>::iterator it17 = map1.upper_bound('b');
    if(it17 != map1.end()) {
        std::cout << "upper_bound: " << it17->first << ", " << it17->second << std::endl;
    } else {
        std::cout << "upper_bound failed" << std::endl;
    }
    std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret7 = map1.equal_range('a');
    if(ret7.first != map1.end()) {
        std::cout << "equal_range first: " << ret7.first->first << ", " << ret7.first->second << std::endl;
    } else {
        std::cout << "equal_range first failed" << std::endl;
    }
    if(ret7.second != map1.end()) {
        std::cout << "equal_range second: " << ret7.second->first << ", " << ret7.second->second << std::endl;
    } else {
        std::cout << "equal_range second failed" << std::endl;
    }
    std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret8 = map1.equal_range('c');
    if(ret8.first != map1.end()) {
        std::cout << "equal_range first: " << ret8.first->first << ", " << ret8.first->second << std::endl;
    } else {
        std::cout << "equal_range first failed" << std::endl;
    }
    if(ret8.second != map1.end()) {
        std::cout << "equal_range second: " << ret8.second->first << ", " << ret8.second->second << std::endl;
    } else {
        std::cout << "equal_range second failed" << std::endl;
    }


}

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
    BasicSetMemberTypes();
    std::cout << "--------------------------------ConstructFun--------------------------------" << std::endl;
    ConstructFun();
    std::cout << "--------------------------------MemberFun--------------------------------" << std::endl;
    MemberFun();
}