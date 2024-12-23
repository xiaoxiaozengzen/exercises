#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

// template<
//     class Key,                                              // unordered_map::key_type
//     class T,                                                // unordered_map::mapped_type
//     class Hash = std::hash<Key>,                            // unordered_map::hasher
//     class Pred = std::equal_to<Key>,                        // unordered_map::key_equal
//     class Alloc = std::allocator<std::pair<const Key,T>>    // unordered_map::allocator_type
// > class unordered_map;

class A {
public:
    A() {
        std::cout << "construct" << std::endl;
    }

    explicit A(std::string a):a(a) {
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
    std::string a = "";
};

void BasicSetMemberTypes() {
    std::unordered_map<double, int> m;
    if(std::is_same<std::unordered_map<double, int>::key_type, double>::value) {
        std::cout << "key_type is double" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::mapped_type, int>::value) {
        std::cout << "mapped_type is int" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::value_type, std::pair<const double, int>>::value) {
        std::cout << "value_type is pair<const double, int>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::hasher, std::hash<double>>::value) {
        std::cout << "hasher is std::hash<double>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::key_equal, std::equal_to<double>>::value) {
        std::cout << "key_equal is std::equal_to<double>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::allocator_type, std::allocator<std::pair<const double, int>>>::value) {
        std::cout << "allocator_type is std::allocator<std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::reference, std::pair<const double, int>&>::value) {
        std::cout << "reference is std::pair<const double, int>&" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::const_reference, const std::pair<const double, int>&>::value) {
        std::cout << "const_reference is const std::pair<const double, int>&" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::pointer, std::pair<const double, int>*>::value) {
        std::cout << "pointer is std::pair<const double, int>*" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::const_pointer, const std::pair<const double, int>*>::value) {
        std::cout << "const_pointer is const std::pair<const double, int>*" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::size_type, std::size_t>::value) {
        std::cout << "size_type is std::size_t" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::difference_type, std::ptrdiff_t>::value) {
        std::cout << "difference_type is std::ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::iterator, std::iterator<std::input_iterator_tag, std::pair<const double, int>>>::value) {
        std::cout << "iterator is std::iterator<std::input_iterator_tag, std::pair<const double, int>>" << std::endl;
    } else {
        std::cout << "iterator is not std::iterator<std::input_iterator_tag, std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::const_iterator, std::iterator<std::input_iterator_tag, const std::pair<const double, int>>>::value) {
        std::cout << "const_iterator is std::iterator<std::input_iterator_tag, const std::pair<const double, int>>" << std::endl;
    } else {
        std::cout << "const_iterator is not std::iterator<std::input_iterator_tag, const std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::local_iterator, std::iterator<std::input_iterator_tag, std::pair<const double, int>>>::value) {
        std::cout << "local_iterator is std::iterator<std::input_iterator_tag, std::pair<const double, int>>" << std::endl;
    } else {
        std::cout << "local_iterator is not std::iterator<std::input_iterator_tag, std::pair<const double, int>>" << std::endl;
    }
    if(std::is_same<std::unordered_map<double, int>::const_local_iterator, std::iterator<std::input_iterator_tag, const std::pair<const double, int>>>::value) {
        std::cout << "const_local_iterator is std::iterator<std::input_iterator_tag, const std::pair<const double, int>>" << std::endl;
    } else {
        std::cout << "const_local_iterator is not std::iterator<std::input_iterator_tag, const std::pair<const double, int>>" << std::endl;
    }   
}

void ConFun() {
    std::unordered_map<std::string, int> m0 = {{"a", 1}, {"b", 2}, {"c", 3}};
    std::unordered_map<std::string, int> m1; // default
    std::unordered_map<std::string, int> m2(10); // initial bucket count
    std::unordered_map<std::string, int> m3(10, std::hash<std::string>()); // initial bucket count and hash function
    std::unordered_map<std::string, int> m4(10, std::hash<std::string>(), std::equal_to<std::string>()); // initial bucket count, hash function and key equal function
    std::unordered_map<std::string, int> m5(m0.begin(), m0.end()); // range
    std::unordered_map<std::string, int> m6(m0); // copy
    std::unordered_map<std::string, int> m7(std::move(m0)); // move
    std::unordered_map<std::string, int> m8 ={
        {"a", 1},
        {"b", 2},
        {"c", 3}
    }; // initializer list

}

void MemFun() {
    std::unordered_map<std::string, int> m = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };

    // 1. capacity
    std::cout << "empty: " << m.empty() << std::endl;
    std::cout << "size: " << m.size() << std::endl;
    std::cout << "max_size: " << m.max_size() << std::endl;

    // 2. iterators
    std::unordered_map<std::string, int>::iterator it = m.begin();
    std::cout << "begin: " << it->first << ", " << it->second << std::endl;
    std::unordered_map<std::string, int>::local_iterator lit = m.begin(0); // iterator of bucket 0 
    std::cout << "begin(0): " << lit->first << ", " << lit->second << std::endl;

    // 3. element access
    std::unordered_map<std::string, int>::mapped_type& ref = m["a"];
    std::cout << "m[\"a\"]: " << ref << std::endl;
    std::unordered_map<std::string, int>::mapped_type& ref2 = m["d"];
    std::cout << "m[\"d\"]: " << ref2 << std::endl;
    std::unordered_map<std::string, int>::mapped_type& ref3 = m.at("b"); // throw out_of_range exception if not found
    std::cout << "m.at(\"b\"): " << ref3 << std::endl;

    // 4. element lookup
    std::unordered_map<std::string, int>::iterator it2 = m.find("a");
    if(it2 != m.end()) {
        std::cout << "find(\"a\"): " << it2->first << ", " << it2->second << std::endl;
    } else {
        std::cout << "find(\"a\") not found" << std::endl;
    }
    std::unordered_map<std::string, int>::iterator it3 = m.find("d");
    if(it3 != m.end()) {
        std::cout << "find(\"d\"): " << it3->first << ", " << it3->second << std::endl;
    } else {
        std::cout << "find(\"d\") not found" << std::endl;
    }
    std::unordered_map<std::string, int>::size_type count = m.count("a");
    std::cout << "count(\"a\"): " << count << std::endl;
    std::pair<std::unordered_map<std::string, int>::iterator, std::unordered_map<std::string, int>::iterator> range = m.equal_range("a");
    if(range.first != m.end()) {
        std::cout << "equal_range(\"a\"): " << range.first->first << ", " << range.first->second << std::endl;
    } else {
        std::cout << "equal_range(\"a\") not found" << std::endl;
    }
    if(range.second != m.end()) {
        std::cout << "equal_range(\"a\"): " << range.second->first << ", " << range.second->second << std::endl;
    } else {
        std::cout << "equal_range(\"a\") not found" << std::endl;
    }
    std::pair<std::unordered_map<std::string, int>::iterator, std::unordered_map<std::string, int>::iterator> rane2 = m.equal_range("e");
    if(rane2.first != m.end()) {
        std::cout << "equal_range(\"e\"): " << rane2.first->first << ", " << rane2.first->second << std::endl;
    } else {
        std::cout << "equal_range(\"e\") not found" << std::endl;
    }
    if(rane2.second != m.end()) {
        std::cout << "equal_range(\"e\"): " << rane2.second->first << ", " << rane2.second->second << std::endl;
    } else {
        std::cout << "equal_range(\"e\") not found" << std::endl;
    }

    // 5. modifiers
    // 5.1 emplace
    std::pair<std::unordered_map<std::string, int>::iterator, bool> result = m.emplace("d", 4);
    if(result.second) {
        std::cout << "emplace(\"d\", 4): " << result.first->first << ", " << result.first->second << std::endl;
    } else {
        std::cout << "emplace(\"d\", 4) failed, old value: " << result.first->first << ", " << result.first->second << std::endl; 
    }
    std::pair<std::unordered_map<std::string, int>::iterator, bool> result2 = m.emplace("e", 5);
    if(result2.second) {
        std::cout << "emplace(\"e\", 5): " << result2.first->first << ", " << result2.first->second << std::endl;
    } else {
        std::cout << "emplace(\"e\", 5) failed, old value: " << result2.first->first << ", " << result2.first->second << std::endl; 
    }
    // 5.2 emplace_hint
    std::unordered_map<std::string, int>::iterator it4 = m.emplace_hint(m.begin(), "f", 6);
    std::cout << "emplace_hint(\"f\", 6): " << it4->first << ", " << it4->second << std::endl;
    std::unordered_map<std::string, int>::iterator it5 = m.emplace_hint(m.begin(), "f", 7);
    std::cout << "emplace_hint(\"f\", 7): " << it5->first << ", " << it5->second << std::endl;
    // 5.3 insert
    std::pair<std::unordered_map<std::string, int>::iterator, bool> result3 = m.insert(std::make_pair("g", 7));
    if(result3.second) {
        std::cout << "insert(\"g\", 7): " << result3.first->first << ", " << result3.first->second << std::endl;
    } else {
        std::cout << "insert(\"g\", 7) failed, old value: " << result3.first->first << ", " << result3.first->second << std::endl; 
    }
    std::unordered_map<std::string, int>::iterator it6 = m.insert<std::pair<std::string, int>>(m.begin(), std::make_pair("h", 8));
    std::cout << "insert(\"h\", 8): " << it6->first << ", " << it6->second << std::endl;
    std::unordered_map<std::string, int>::iterator it7 = m.insert(m.begin(), std::make_pair("h", 9));
    std::cout << "insert(\"h\", 9): " << it7->first << ", " << it7->second << std::endl;
    std::unordered_map<std::string, int> m2 = {
        {"i", 9},
        {"j", 10},
        {"k", 11}
    };
    m.insert(m2.begin(), m2.end());
    m.insert({
        {"l", 12},
        {"m", 13},
        {"n", 14}
    });
    // 5.4 erase
    std::unordered_map<std::string, int>::iterator it8 = m.erase(m.begin());
    std::cout << "erase begin: " << it8->first << ", " << it8->second << std::endl;
    std::unordered_map<std::string, int>::size_type count2 = m.erase("a");
    std::cout << "erase(\"a\"): " << count2 << std::endl;
    std::unordered_map<std::string, int>::iterator it9 = m.erase(m.find("d"), m.end());
    if(it9 != m.end()) {
        std::cout << "erase(d, end): " << it9->first << ", " << it9->second << std::endl;
    } else {
        std::cout << "erase(d, end) is end" << std::endl;
    }
    m.clear();
    // 5.5 swap
    m.swap(m2);

    // 6. bucket interface
    std::unordered_map<std::string, int>::size_type bucket_count = m.bucket_count();
    std::cout << "bucket_count: " << bucket_count << std::endl;
    std::unordered_map<std::string, int>::size_type max_bucket_count = m.max_bucket_count();
    std::cout << "max_bucket_count: " << max_bucket_count << std::endl;
    std::unordered_map<std::string, int>::size_type bucket_size = m.bucket_size(0);
    std::cout << "bucket_size(0): " << bucket_size << std::endl;
    std::unordered_map<std::string, int>::size_type bucket = m.bucket("i");
    std::cout << "bucket(i): " << bucket << std::endl;
    std::unordered_map<std::string, int>::size_type bucket2 = m.bucket("qqqq");
    std::cout << "bucket(qqqq): " << bucket2 << std::endl;
    std::unordered_map<std::string, int>::iterator it10 = m.find("qqqq");
    if(it10 != m.end()) {
        std::cout << "find(\"qqqq\"): " << it10->first << ", " << it10->second << std::endl;
    } else {
        std::cout << "find(\"qqqq\") not found" << std::endl;
    }

    // 7. hash policy
    float load_factor = m.load_factor();
    std::cout << "load_factor: " << load_factor << std::endl;
    float max_load_factor = m.max_load_factor();
    std::cout << "max_load_factor: " << max_load_factor << std::endl;
    m.max_load_factor(0.5);
    std::cout << "load_factor: " << m.load_factor() << ", max_load_factor: " << m.max_load_factor() << std::endl;
    m.rehash(10);
    std::cout << "rehash(10): " << m.bucket_count() << ", load_factor: " << m.load_factor() << ", max_load_factor: " << m.max_load_factor() << std::endl;
    m.reserve(20);
    std::cout << "reserve(20): " << m.bucket_count() << ", load_factor: " << m.load_factor() << ", max_load_factor: " << m.max_load_factor() << std::endl;

    // 8. observers
    std::unordered_map<std::string, int>::hasher hash = m.hash_function();
    std::cout << "hash_function: " << hash("aaaaaa") << std::endl;
    std::unordered_map<std::string, int>::key_equal key_equal = m.key_eq();
    std::cout << "key_eq: " << key_equal("aaaaaa", "aaaaaa") << std::endl;

}

int main() {
    std::cout << "--------------------------------BasicSetMemberTypes--------------------------------" << std::endl;
    BasicSetMemberTypes();
    std::cout << "--------------------------------ConFun--------------------------------" << std::endl;
    ConFun();
    std::cout << "--------------------------------MemFun--------------------------------" << std::endl;
    MemFun();
}