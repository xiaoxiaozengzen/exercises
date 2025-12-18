#include <string>
#include <vector>
#include <iostream>

std::string longest_unique_substring(const std::string& s, int& max_size) {
    if(s.empty()) {
        std::cerr << "Input string is empty." << std::endl;
        return "";
    }

    int left = 0;
    int right = 0;
    int max_length = 0;
    std::string substring;
    std::string result;

    while(left <= right && right < s.length()) {
        if(substring.find(s[right]) == std::string::npos) {
            substring += s[right];
            max_length = std::max(max_length, static_cast<int>(substring.length()));
            right++;
        } else {
            substring.erase(0, 1);
            left++;
        }

        if(substring.length() >= max_length) {
            result = substring;
        }
    }

    max_size = max_length;
    return result;
}

int main(int argc, char** argv) {
    std::string input;
    if (argc > 1) {
        input = argv[1];
    } else {
        std::cout << "Please provide an input string as a command line argument." << std::endl;
        return 1;
    }
    
    int max_size = 0;
    std::string result = longest_unique_substring(input, max_size);
    std::cout << "Size: " << max_size << ", Substring: " << result << ", str.size: " << result.size() << std::endl;

    return 0;
}