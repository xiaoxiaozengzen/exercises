#include <regex>
#include <iostream>
#include <string>
#include <locale>

/**
 * 正则表达式子句法和语义：
 * 1.基本字符串匹配：
 *   - abcd: 匹配字符串 "abcd"
 * 2.元字符(特殊符号)：
 *  - .: 匹配任意单个字符
 *  - ^: 匹配字符串的开头
 *  - $: 匹配字符串的结尾
 *  - *: 匹配前一个字符零次或多次
 *  - +: 匹配前一个字符一次或多次
 *  - ?: 匹配前一个字符零次或一次
 *  - {n}: 匹配前一个字符恰好 n 次
 *  - {n,}: 匹配前一个字符至少 n 次
 *  - {n,m}: 匹配前一个字符至少 n 次，至多 m 次
 * 3.字符类：
 *   - [abc]: 匹配字符 'a'、'b' 或 'c'
 *   - [^abc]: 匹配除 'a'、'b' 或 'c' 之外的任意字符
 *   - [a-z]: 匹配小写字母 'a' 到 'z' 之间的任意字符
 *   - [A-Z]: 匹配大写字母 'A' 到 'Z' 之间的任意字符
 *   - [0-9]: 匹配数字 '0' 到 '9' 之间的任意字符
 * 4.转义字符：
 *   - \d: 匹配任意数字，相当于 [0-9]
 *   - \D: 匹配任意非数字字符，相当于 [^0-9]
 *   - \w: 匹配任意字母、数字或下划线，相当于 [a-zA-Z0-9_]
 *   - \W: 匹配任意非字母、数字或下划线字符，相当于 [^a-zA-Z0-9_]
 *   - \s: 匹配任意空白字符（空格、制表符、换行符等），相当于 [ \t\n\r\f\v]
 *   - \S: 匹配任意非空白字符，相当于 [^ \t\n\r\f\v]
 * 5.分组和捕获：
 *   - (abc): 匹配字符串 "abc"
 *   - (a|b): 匹配字符 'a' 或 'b'
 * 6.贪婪与非贪婪匹配：
 *   - *、 +、? 等元字符默认是贪婪的，即尽可能多地匹配字符。
 *   - ?*、 +?、?? 等形式可以使匹配变为非贪婪的，即尽可能少地匹配字符。
 * 7.边界匹配：
 *   - \b: 匹配单词边界，即单词的开头或结尾。
 *   - \B: 匹配非单词边界，即单词内部的边界。
 */


/**
 * template <class charT, class traits = regex_traits<charT> >
 * class basic_regex;
 */
void basic_regex_example() {
    std::basic_regex<char> rgx("ab*c");
    if(std::is_same<std::basic_regex<char>::value_type, char>::value) {
        std::cout << "The basic_regex is using char as its value type." << std::endl;
    } else {
        std::cout << "The basic_regex is not using char as its value type." << std::endl;
    }
    if(std::is_same<std::basic_regex<char>::flag_type, std::regex_constants::syntax_option_type>::value) {
        std::cout << "The basic_regex is using regex_constants::syntax_option_type as its flag type." << std::endl;
    } else {
        std::cout << "The basic_regex is not using regex_constants::syntax_option_type as its flag type." << std::endl;
    }

    /**
     * @brief std::regex_constants，其下有三种类型，具体可能通过枚举或者int实现，可以支持&和|操作符。
     * 1. std::regex_constants::syntax_option_type
     *  - 用于regex的构造和assign
     *  - 例如：
     *     *   - std::regex_constants::icase: 忽略大小写
     *     *   - std::regex_constants::nosubs: 不捕获子表达式
     *     *   - std::regex_constants::ECMAScript: 使用ECMAScript语法
     * 2. std::regex_constants::match_flag_type
     *  - 用于regex_match、regex_search和regex_replace函数
     *  - 例如：
     *     *   - std::regex_constants::match_default: 默认匹配行为
     *     *   - std::regex_constants::match_not_bol: 不将目标序列的开头视为行的开头
     * 3. std::regex_constants::error_type
     *  - 用于regex_error
     */

    /****************** construct ******************/
    std::basic_regex<char> rgx1;
    std::basic_regex<char> rgx2(rgx1);
    std::basic_regex<char> rgx3(std::move(rgx1));
    std::basic_regex<char> rgx4("ab*c", std::regex_constants::icase);
    std::basic_regex<char> rgx5("ab*c");
    char pattern[] = "ab*c";
    std::basic_regex<char> rgx6(pattern, pattern + sizeof(pattern) - 1, std::regex_constants::icase);
    std::basic_regex<char> rgx7({'a', 'b', '*', 'c'}, std::regex_constants::icase);
    std::basic_regex<char> rgx8("ab*c", 2, std::regex_constants::icase);

    /****************** member fun ******************/
    rgx1.assign(rgx2);
    rgx1.assign(std::move(rgx3));
    rgx1.assign("ab*c", std::regex_constants::icase);

    // 获取正则表达式的捕获分组(即括号括起来的部分)数量
    unsigned ret = rgx5.mark_count();
    std::cout << "The regex has " << ret << " capturing groups." << std::endl;
    std::basic_regex<char> rgx9("(sub)");
    unsigned ret2 = rgx9.mark_count();
    std::cout << "The regex has " << ret2 << " capturing groups." << std::endl;
    std::regex_constants::syntax_option_type flags = rgx5.flags();
    std::cout << "The regex flags: " << flags << ", ECMASCRIPT: " << std::regex_constants::ECMAScript << std::endl;
    std::locale loc = rgx5.getloc();
    std::cout << "The regex locale: " << loc.name() << std::endl;
}

/**
 * @brief Returns whether the target sequence matches the regular expression rgx. 
 * The target sequence is either s or the character sequence between first and last, depending on the version used.
 * 
 * template <class charT, class traits>
 * bool regex_match (const charT* s, const basic_regex<charT,traits>& rgx, regex_constants::match_flag_type flags = regex_constants::match_default);
 * @param s The target sequence to match.
 * @param rgx The regular expression to match against.
 * @param flags Optional flags to modify the matching behavior.
 */
void regex_match_test() {
    std::string str = "subject";
    std::regex rgx("sub.*t");
    bool result = std::regex_match(str, rgx);
    if(result) {
       std::cout << "The string matches the regex." << std::endl;
    } else {
        std::cout << "The string does not match the regex." << std::endl;
    }
    std::string str2 = "subject";
    std::regex rgx2("^sub");
    bool result2 = std::regex_match(str2.c_str(), rgx2, std::regex_constants::match_not_bol);
    if(result2) {
         std::cout << "subject matches the regex ^sub with match_not_bol." << std::endl;
    } else {
        std::cout << "subject does not match the regex ^sub with match_not_bol." << std::endl;
    }
}

/**
 * template < class BidirectionalIterator, class Alloc = allocator< sub_match<BidirectionalIterator> > >  
 * class match_results;
 * 
 * @brief match_results 是一个模板类，用于存储正则表达式匹配的结果。
 */
void match_result_example() {
#if 0
    typedef match_results<const char*> cmatch;
    typedef match_results<const wchar_t*> wcmatch;
    typedef match_results<string::const_iterator> smatch;
    typedef match_results<wstring::const_iterator> wsmatch;
#endif

    std::cmatch cmatch_result;
    bool is_empty = cmatch_result.empty();
    std::cout << "cmatch_result is empty: " << std::boolalpha << is_empty << std::endl;
    std::string str = "Hello, nihao a, ll. Is your a llittee";
    std::regex rgx("ll");
    bool ret = std::regex_search(str.c_str(), cmatch_result, rgx);
    if(ret) {
        std::cout << "empty: " << std::boolalpha << cmatch_result.empty() << std::endl;
        std::cout << "size: " << cmatch_result.size() << std::endl;
        if (cmatch_result.ready()) {
            std::cout << "cmatch_result is ready." << std::endl;
        } else {
            std::cout << "cmatch_result is not ready." << std::endl;
        }
        std::cmatch::const_iterator it = cmatch_result.begin();
        std::cout << "First match: " << *it << std::endl;
        std::cout << "First match[0]: " << cmatch_result[0] << std::endl;
        std::cout << "Prefix of first match: " << cmatch_result.prefix() << std::endl;
        std::cout << "Suffix of first match: " << cmatch_result.suffix() << std::endl;
        std::cout << "First match length: " << cmatch_result.length(0) << std::endl;
        std::cout << "First match position: " << cmatch_result.position(0) << std::endl;
        std::cout << "First match str: " << cmatch_result.str(0) << std::endl;        
    } else {
        std::cout << "No match found." << std::endl;
    }
}

/**
 * @brief 是否目标字符串中的某个子串匹配正则表达式rgx。
 * 
 * template <class charT, class traits>
 * bool regex_search (const charT* s, const basic_regex<charT,traits>& rgx, regex_constants::match_flag_type flags = regex_constants::match_default);
 * 
 * emplate <class BidirectionalIterator, class charT, class traits>  
 * bool regex_search (BidirectionalIterator first, BidirectionalIterator last, const basic_regex<charT,traits>& rgx, regex_constants::match_flag_type flags = regex_constants::match_default);
 */
void regex_search_test() {
}

/**
 * template <class traits, class charT>  
 * basic_string<charT> regex_replace (const charT* s, const basic_regex<charT,traits>& rgx, const charT* fmt, regex_constants::match_flag_type flags = regex_constants::match_default);
 */
void regex_replace_test() {
    std::string str = "Hello, nihao a, ll. Is your a llittee";
    std::regex rgx("ll");
    std::string fmt = "XX";
    std::string result = std::regex_replace(str, rgx, fmt);
    std::cout << "Original string: " << str << std::endl;
    std::cout << "Replaced string: " << result << std::endl;
}

int main() {
    std::cout << "==================== Basic Regex Example ====================" << std::endl;
    basic_regex_example();
    std::cout << "==================== Regex Match Test ====================" << std::endl;
    regex_match_test();
    std::cout << "==================== Match Result Example ====================" << std::endl;
    match_result_example();
    std::cout << "==================== Regex Search Test ====================" << std::endl;
    regex_search_test();
    std::cout << "==================== Regex Replace Test ====================" << std::endl;
    regex_replace_test();
    
    return 0;
}