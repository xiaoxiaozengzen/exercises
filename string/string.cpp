// template<
//     class CharT,
//     class Traits = std::char_traits<CharT>,
//     class Allocator = std::allocator<CharT>
// > class basic_string;

// using string=basic_string<char>

#include <iostream>
#include <string>
#include <type_traits>

void MemType() {
    if(std::is_same<std::string::value_type, char>::value) {
        std::cout << "string::value_type is char" << std::endl;
    }
    if(std::is_same<std::string::traits_type, std::char_traits<char>>::value) {
        std::cout << "string::traits_type is std::char_traits<char>" << std::endl;
    }
    if(std::is_same<std::string::allocator_type, std::allocator<char>>::value) {
        std::cout << "string::allocator_type is std::allocator<char>" << std::endl;
    }
    if(std::is_same<std::string::size_type, std::size_t>::value) {
        std::cout << "string::size_type is std::size_t" << std::endl;
    }
    if(std::is_same<std::string::difference_type, std::ptrdiff_t>::value) {
        std::cout << "string::difference_type is std::ptrdiff_t" << std::endl;
    }
    if(std::is_same<std::string::reference, char&>::value) {
        std::cout << "string::reference is char&" << std::endl;
    }
    if(std::is_same<std::string::const_reference, const char&>::value) {
        std::cout << "string::const_reference is const char&" << std::endl;
    }
    if(std::is_same<std::string::pointer, char*>::value) {
        std::cout << "string::pointer is char*" << std::endl;
    }
    if(std::is_same<std::string::const_pointer, const char*>::value) {
        std::cout << "string::const_pointer is const char*" << std::endl;
    }
}

void ConFun() {
    std::string s1; // empty
    std::string s2(10, 'a'); // init from size and char
    std::cout << "s2: " << s2 << std::endl;
    char arr[] = {'a', 'b', 'c'};
    std::string s3(std::begin(arr), std::end(arr)); // init from iterator
    std::cout << "s3: " << s3 << ", size: " << s3.size() << std::endl;
    std::string s4({'a', 'b', 'c'}); // init from initializer_list
    std::cout << "s4: " << s4 << ", size: " << s4.size() << std::endl;
    std::string s5("abc"); // init from const char*
    std::cout << "s5: " << s5 << ", size: " << s5.size() << std::endl;
    std::string s6(s5); // copy-constructor
    std::cout << "s6: " << s6 << ", size: " << s6.size() << std::endl;
    std::string s7(std::move(s6)); // move-constructor 
    std::cout << "s7: " << s7 << ", size: " << s7.size() << std::endl;
    std::string s8(arr, 1); // init from pointer and size
    std::cout << "s8: " << s8 << ", size: " << s8.size() << std::endl;
    std::string s9(s5, 1); // init from string and pos
    std::cout << "s9: " << s9 << ", size: " << s9.size() << std::endl;
    std::string s10(s5, 1, 1); // init from string, pos and size
    std::cout << "s10: " << s10 << ", size: " << s10.size() << std::endl;
}

void MemFun() {
    // 1.iterator
    std::string s1("abcdefg");
    std::string::iterator it1 = s1.begin();
    std::string::const_iterator it2 = s1.cbegin();
    std::string::reverse_iterator it3 = s1.rbegin();
    std::string::const_reverse_iterator it4 = s1.crbegin();
    std::cout << "it1: " << *it1 << ", it2: " << *it2 << ", it3: " << *it3 << ", it4: " << *it4 << std::endl;

    // 2.capacity
    std::size_t size = s1.size();
    std::size_t length = s1.length();
    std::size_t max_size = s1.max_size();
    std::size_t capacity = s1.capacity();
    std::cout << "size: " << size << ", length: " << length << ", max_size: " << max_size << ", capacity: " << capacity << std::endl;
    s1.resize(10);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.resize(5, 'i');
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.reserve(20);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.reserve();
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.clear();
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    if(s1.empty()) {
        std::cout << "s1 is empty" << std::endl;
    }
    s1.resize(10, 'a');
    s1.shrink_to_fit();
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;

    // 3.element access
    char ch1 = s1[0];
    char ch2 = s1.at(1);
    s1.front() = 'b';
    char ch3 = s1.front();    
    char ch4 = s1.back();
    std::cout << "ch1: " << ch1 << ", ch2: " << ch2 << ", ch3: " << ch3 << ", ch4: " << ch4 << std::endl;

    // 4.modifiers
    // 4.1 +=
    std::string s2("abcdefghdefgh");
    const char* cstr = "def";
    char ch5 = 'g';
    s1+=s2;
    std::cout << "s1: " << s1 << std::endl;
    s1+=cstr;
    std::cout << "s1: " << s1 << std::endl;
    s1+=ch5;
    std::cout << "s1: " << s1 << std::endl;
    // 4.2 append
    s1.append(s2);
    std::cout << "s1: " << s1 << std::endl;
    s1.append(s2, 1, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.append(cstr);
    std::cout << "s1: " << s1 << std::endl;
    s1.append(cstr, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.append(3, ch5);
    std::cout << "s1: " << s1 << std::endl;
    s1.append(s2.begin(), s2.end());
    std::cout << "s1: " << s1 << std::endl;
    // 4.3 push_back
    s1.push_back('h');
    std::cout << "s1: " << s1 << std::endl;
    // 4.4 assign
    s1.assign(s2);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.assign(s2, 2, 3);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.assign(cstr);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.assign(cstr, 2);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.assign(3, ch5);
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    s1.assign(s2.begin(), s2.end());
    std::cout << "s1: " << s1 << ", size: " << s1.size() << ", length: " << s1.length() << ", capacity: " << s1.capacity() << std::endl;
    // 4.5 insert
    s1.insert(1, s2);
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(2, s2, 1, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(3, cstr);
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(4, cstr, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(5, 3, ch5);
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(s1.begin(), 'i');
    std::cout << "s1: " << s1 << std::endl;
    s1.insert(s1.begin(), s2.begin(), s2.end());
    std::cout << "s1: " << s1 << std::endl;
    // 4.6 erase
    std::string s3 = s1.erase(1, 2);
    std::cout << "s1: " << s1 << std::endl;
    std::string::iterator it5 = s1.erase(s1.begin());
    if(it5 != s1.end()) {
        std::cout << "it5: " << *it5 << std::endl;
    }
    std::string::iterator it6 = s1.erase(s1.begin(), s1.begin()+2);
    if(it6 != s1.end()) {
        std::cout << "it6: " << *it6 << std::endl;
    }
    // 4.7 replace
    s1 = "1234";
    s1.replace(1, 1, s2);
    std::cout << "s1: " << s1 << std::endl;
    s1.replace(2, 2, s2, 1, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.replace(3, 3, cstr);
    std::cout << "s1: " << s1 << std::endl;
    s1.replace(4, 4, cstr, 2);
    std::cout << "s1: " << s1 << std::endl;
    s1.replace(5, 5, 3, ch5);
    std::cout << "s1: " << s1 << std::endl;
    s1.replace(s1.begin(), s1.begin()+1, s2.begin(), s2.end());
    std::cout << "s1: " << s1 << std::endl;
    // 4.8 swap
    s1.swap(s2);
    std::cout << "s1: " << s1 << ", s2: " << s2 << std::endl;
    // 4.9 pop_back
    s1.pop_back();
    std::cout << "s1: " << s1 << std::endl;
    
    // 5.string operations
    const char* cstr1 = s1.c_str();
    std::cout << "cstr1: " << cstr1 << std::endl;
    const char* data = s1.data();
    std::cout << "data: " << data << std::endl;
    char arr[] = "12345";
    std::size_t ret = s1.copy(arr, 5, 1);
    std::cout << "arr: " << arr << ", ret: " << ret << std::endl;
}

int main() {
    std::cout << "======================MemType======================" << std::endl;
    MemType();
    std::cout << "======================ConFun======================" << std::endl;
    ConFun();
    std::cout << "======================MemFun======================" << std::endl;
    MemFun();
    return 0;
}