#include <iostream>
#include <string>
#include <unordered_set>

// template<class Key,                             // unordered_set::key_type/value_type
//          class Hash = sd::hash<Key>,            // unordered_set::hasher
//          class Pred = std::equal_to<Key>,       // unordered_set::key_equal
//          class Alloc = std::allocator<Key>      // unordered_set::allocator_type
// >class unordered_set;

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
  std::unordered_set<int> set_int;
  if (std::is_same<std::unordered_set<int>::key_type, int>::value) {
    std::cout << "std::unordered_set<int>::key_type is int" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::value_type, int>::value) {
    std::cout << "std::unordered_set<int>::value_type is int" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::hasher, std::hash<int>>::value) {
    std::cout << "std::unordered_set<int>::hasher is std::hash<int>" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::key_equal, std::equal_to<int>>::value) {
    std::cout << "std::unordered_set<int>::key_equal is std::equal_to<int>" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::allocator_type, std::allocator<int>>::value) {
    std::cout << "std::unordered_set<int>::allocator_type is std::allocator<int>" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::reference, int&>::value) {
    std::cout << "std::unordered_set<int>::reference is int&" << std::endl;
  } else {
    std::cout << "std::unordered_set<int>::reference is not int&" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::const_reference, const int&>::value) {
    std::cout << "std::unordered_set<int>::const_reference is const int&" << std::endl;
  } else {
    std::cout << "std::unordered_set<int>::const_reference is not const int&" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::pointer, int*>::value) {
    std::cout << "std::unordered_set<int>::pointer is int*" << std::endl;
  } else {
    std::cout << "std::unordered_set<int>::pointer is not int*" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::const_pointer, const int*>::value) {
    std::cout << "std::unordered_set<int>::const_pointer is const int*" << std::endl;
  } else {
    std::cout << "std::unordered_set<int>::const_pointer is not const int*" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::size_type, std::size_t>::value) {
    std::cout << "std::unordered_set<int>::size_type is std::size_t" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::difference_type, std::ptrdiff_t>::value) {
    std::cout << "std::unordered_set<int>::difference_type is std::ptrdiff_t" << std::endl;
  }
  if (std::is_same<std::unordered_set<int>::iterator,
                   std::iterator<std::forward_iterator_tag, const int>>::value) {
    std::cout << "std::unordered_set<int>::iterator is std::iterator<std::forward_iterator_tag, "
                 "const int>"
              << std::endl;
  } else {
    std::cout << "std::unordered_set<int>::iterator is not "
                 "std::iterator<std::forward_iterator_tag, const int>"
              << std::endl;
  }
}

void MemConFun() {
  // Minimum number of initial buckets.
  // This is not the number of elements in the container, but the minimum number of slots desired
  // for the internal hash table on construction.
  std::unordered_set<int> set_int2(10);

  std::unordered_set<std::string> first;                                // empty
  std::unordered_set<std::string> second({"red", "green", "blue"});     // init list
  std::unordered_set<std::string> third({"orange", "pink", "yellow"});  // init list
  std::unordered_set<std::string> fourth(second);                       // copy
  std::unordered_set<std::string> fifth(std::move(fourth));             // move
  std::unordered_set<std::string> sixth(fifth.begin(), fifth.end());    // range
}

void MemFun() {
  // Elements can be inserted or removed, but not modified while in the container.
  std::unordered_set<int> set_int = {1, 2, 3, 4, 5};

  // 1.capacity
  std::cout << "set_int.empty(): " << set_int.empty() << std::endl;
  std::cout << "set_int.size(): " << set_int.size() << std::endl;
  std::cout << "set_int.max_size(): " << set_int.max_size() << std::endl;

  // 2.iterator
  std::unordered_set<int>::iterator it = set_int.begin();
  std::cout << "set_int.begin(): " << *it << std::endl;
  // std::unordered_set<int>::iterator it2 = set_int.end();
  // std::cout << "set_int.end(): " << *(it2) << std::endl;
  std::unordered_set<int>::const_iterator cit = set_int.cbegin();
  std::cout << "set_int.cbegin(): " << *cit << std::endl;
  std::unordered_set<int>::local_iterator lit = set_int.begin(0);
  std::cout << "set_int.begin(0): " << *(lit) << std::endl;

  // 3.element find
  std::unordered_set<int>::iterator it3 = set_int.find(3);
  if (it3 != set_int.end()) {
    std::cout << "set_int.find(3): " << *it3 << std::endl;
  } else {
    std::cout << "set_int.find(3) not found" << std::endl;
  }
  std::unordered_set<int>::iterator it4 = set_int.find(6);
  if (it4 != set_int.end()) {
    std::cout << "set_int.find(6): " << *it4 << std::endl;
  } else {
    std::cout << "set_int.find(6) not found" << std::endl;
  }
  std::unordered_set<int>::size_type count = set_int.count(3);
  std::cout << "set_int.count(3): " << count << std::endl;
  std::pair<std::unordered_set<int>::iterator, std::unordered_set<int>::iterator> range =
      set_int.equal_range(3);
  if (range.first != set_int.end()) {
    std::cout << "set_int.equal_range(3) first: " << *(range.first) << std::endl;
  } else {
    std::cout << "set_int.equal_range(3) first not found" << std::endl;
  }
  if (range.second != set_int.end()) {
    std::cout << "set_int.equal_range(3) second: " << *(range.second) << std::endl;
  } else {
    std::cout << "set_int.equal_range(3) second not found" << std::endl;
  }

  // 4.modifiers
  std::pair<std::unordered_set<int>::iterator, bool> ret = set_int.emplace(6);
  if (ret.second) {
    std::cout << "set_int.emplace(6) success: " << *(ret.first) << std::endl;
  } else {
    std::cout << "set_int.emplace(6) fail: " << *(ret.first) << std::endl;
  }
  std::pair<std::unordered_set<int>::iterator, bool> ret2 = set_int.emplace(5);
  if (ret2.second) {
    std::cout << "set_int.emplace(5) success: " << *(ret2.first) << std::endl;
  } else {
    std::cout << "set_int.emplace(5) fail: " << *(ret2.first) << std::endl;
  }
  std::unordered_set<int>::iterator ret3 = set_int.emplace_hint(set_int.begin(), 7);
  std::cout << "set_int.emplace_hint(7): " << *(ret3) << std::endl;
  std::unordered_set<int>::iterator ret4 = set_int.emplace_hint(set_int.begin(), 7);
  std::cout << "set_int.emplace_hint(7): " << *(ret4) << std::endl;
  // 4.1.insert
  std::pair<std::unordered_set<int>::iterator, bool> ret5 = set_int.insert(8);
  if (ret5.second) {
    std::cout << "set_int.insert(8) success: " << *(ret5.first) << std::endl;
  } else {
    std::cout << "set_int.insert(8) fail: " << *(ret5.first) << std::endl;
  }
  std::unordered_set<int>::iterator ret6 = set_int.insert(set_int.begin(), 9);
  std::cout << "set_int.insert(9): " << *(ret6) << std::endl;
  std::unordered_set<int> set_int2 = {10, 11, 12};
  set_int.insert(set_int2.begin(), set_int2.end());
  set_int.insert({13, 14, 15});
  // 4.2.erase
  std::unordered_set<int>::size_type erase_count = set_int.erase(6);
  std::cout << "set_int.erase(6): " << erase_count << std::endl;
  std::unordered_set<int>::iterator ret7 = set_int.erase(set_int.begin());
  std::cout << "set_int.erase(set_int.begin()): " << *(ret7) << std::endl;
  std::unordered_set<int>::iterator ret8 = set_int.erase(set_int.begin(), set_int.find(9));
  std::cout << "set_int.erase(set_int.begin(), set_int.find(9)): " << *(ret8) << std::endl;
  // 4.3.swap\clear
  std::unordered_set<int> set_int3 = {16, 17, 18};
  set_int.swap(set_int3);
  set_int.clear();

  // 5.bucket
  std::unordered_set<int> set_int4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << "set_int4.bucket_count(): " << set_int4.bucket_count() << std::endl;
  for (unsigned i = 0; i < set_int4.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for (auto lit = set_int4.begin(i); lit != set_int4.end(i); ++lit) {
      std::cout << " " << *lit;
    }
    std::cout << "\n";
  }
  std::cout << "set_int4.max_bucket_count(): " << set_int4.max_bucket_count() << std::endl;
  // Returns the number of elements in bucket n.
  std::cout << "set_int4.bucket_size(1): " << set_int4.bucket_size(1) << std::endl;
  // Returns the bucket number where the element with key k is located.
  std::cout << "set_int4.bucket(3): " << set_int4.bucket(3) << std::endl;

  // 6.hash policy
  float load_factor = set_int4.load_factor();  // load_factor = size / bucket_count
  std::cout << "set_int4.load_factor(): " << load_factor << std::endl;
  float max_load_factor = set_int4.max_load_factor();
  std::cout << "set_int4.max_load_factor(): " << max_load_factor << std::endl;
  set_int4.max_load_factor(0.5);
  max_load_factor = set_int4.max_load_factor();
  std::cout << "set_int4.max_load_factor(): " << max_load_factor << std::endl;

  // Sets the number of buckets in the container
  set_int4.rehash(10);
  std::cout << "set_int4.rehash(10): " << set_int4.bucket_count() << std::endl;

  // Sets the number of buckets in the container (bucket_count) to the most appropriate to contain
  // at least n elements.
  set_int4.reserve(20);
  std::cout << "set_int4.reserve(20): " << set_int4.bucket_count() << std::endl;

  // 7.observers
  std::unordered_set<int> set_int5 = {1, 2, 3, 4, 5};
  std::hash<std::unordered_set<int>::key_type> hash_fn = set_int5.hash_function();
  std::cout << "set_int5.hash_function()(1): " << hash_fn(1) << std::endl;
  std::equal_to<std::unordered_set<int>::key_type> key_eq = set_int5.key_eq();
  std::cout << "set_int5.key_eq()(1, 2): " << key_eq(1, 2) << std::endl;
}

template <class T>
struct MyHash {
  std::size_t operator()(const T& t) const { return std::hash<std::string>()(t.a); }
};

void Rehash() {
  std::unordered_set<A, MyHash<A>> set_a;
  set_a.max_load_factor(1.0);
  set_a.reserve(5);
  set_a.emplace("1");
  set_a.emplace("2");
  set_a.emplace("3");
  set_a.emplace("4");
  set_a.emplace("5");
  std::cout << "set_a.size(): " << set_a.size() << ", set_a.bucket_count: " << set_a.bucket_count()
            << ", load_factor: " << set_a.load_factor() << std::endl;
  set_a.emplace("6");
  set_a.rehash(6);
  set_a.emplace("7");
  std::cout << "set_a.size(): " << set_a.size() << ", set_a.bucket_count: " << set_a.bucket_count()
            << ", load_factor: " << set_a.load_factor() << std::endl;
  set_a.erase(A("7"));
  std::cout << "set_a.size(): " << set_a.size() << ", set_a.bucket_count: " << set_a.bucket_count()
            << ", load_factor: " << set_a.load_factor() << std::endl;
  set_a.emplace("17");
  std::cout << "set_a.size(): " << set_a.size() << ", set_a.bucket_count: " << set_a.bucket_count()
            << ", load_factor: " << set_a.load_factor() << std::endl;
  set_a.emplace("21");
  std::cout << "set_a.size(): " << set_a.size() << ", set_a.bucket_count: " << set_a.bucket_count()
            << ", load_factor: " << set_a.load_factor() << std::endl;
  set_a.emplace("31");
  set_a.emplace("41");
  set_a.emplace("14");
  set_a.emplace("45");

  for (unsigned i = 0; i < set_a.bucket_count(); ++i) {
    std::cout << "bucket #" << i << " contains:";
    for (auto lit = set_a.begin(i); lit != set_a.end(i); ++lit) {
      std::cout << " " << *lit;
    }
    std::cout << "\n";
  }
}

int main() {
  std::cout << "--------------------------------BasicSetMemberTypes--------------------------------"
            << std::endl;
  BasicSetMemberTypes();
  std::cout << "--------------------------------MemConFun--------------------------------"
            << std::endl;
  MemConFun();
  std::cout << "--------------------------------MemFun--------------------------------"
            << std::endl;
  MemFun();
  std::cout << "--------------------------------Rehash--------------------------------"
            << std::endl;
  Rehash();
}