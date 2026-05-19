#include <iostream>
#include <vector>
#include <string>

/**
 * 回文子串：
 * 1. 给定一个字符串 s，找出 s 中最长的回文子串。
 * 2. 回文子串是指正着读和反着读都一样的字符串。
 */

std::string longestPalindrome(const std::string& s) {

    return "";
}

int main() {
    std::string s = "babad";
    std::cout << "Input string: " << s << std::endl;
    std::string result = longestPalindrome(s);
    std::cout << "Longest palindromic substring: " << result << std::endl;

    return 0;
}