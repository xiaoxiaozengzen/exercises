#include <strings.h> // POSIX: strncasecmp

#include <iostream>

/**
 * int strncasecmp(const char *s1, const char *s2, size_t n);
 * int strcasecmp(const char *s1, const char *s2);
 * @brief 按照字节顺序逐个比较字符串s1和s2的前n个字符，忽略大小写差异。
 * @param s1 指向第一个字符串的指针。
 * @param s2 指向第二个字符串的指针。
 * @param n 要比较的最大字符数。
 * @return 如果s1小于s2，返回一个负值；如果s1大于s2，返回一个正值；如果相等，返回0。
 */
void stracasecmp_example() {
    const char *a = "HelloWorld";
    const char *b = "helloworld123";
    int ret = strncasecmp(a, b, 10); // 比较前10个字符
    if (ret == 0) {
      std::cout << "前10个字符忽略大小写后相等" << std::endl;
    } else if (ret < 0) {
      std::cout << "前10个字符忽略大小写后，a小于b" << std::endl;
    } else {
      std::cout << "前10个字符忽略大小写后，a大于b" << std::endl;
    }
}

void sscanf_example() {
    const char *str = "123 45.67 Hello";
    int intValue;
    float floatValue;
    char strValue[20];
    int anotherInt;  // 没有读取到的变量

    /**
     * @brief 从字符串中读取格式化数据
     * @param str 输入字符串
     * @param format 格式字符串
     * @param ... 输出变量的指针
     * @return 成功读取的项数
     */
    int count = sscanf(str, "%d %f %s %d", &intValue, &floatValue, strValue, &anotherInt);
    std::cout << "成功读取的项数: " << count << std::endl;
    std::cout << "intValue: " << intValue << std::endl;
    std::cout << "floatValue: " << floatValue << std::endl;
    std::cout << "strValue: " << strValue << std::endl;
}

void sprintf_example() {
    int intValue = 123;
    float floatValue = 45.67f;
    const char *strValue = "Hello";

    char buffer[100];
    /**
     * @brief 将格式化数据写入字符串
     * @param buffer 输出字符串缓冲区
     * @param format 格式字符串
     * @param ... 输入变量
     * @return 写入的字符数
     */
    int count = sprintf(buffer, "intValue: %d, floatValue: %.2f, strValue: %s", intValue, floatValue, strValue);
    std::cout << "写入的字符数: " << count << std::endl;
    std::cout << "buffer: " << buffer << std::endl;
}

int main() {
    std::cout << "===================stracasecmp example===================" << std::endl;
    stracasecmp_example();
    std::cout << "===================sscanf example===================" << std::endl;
    sscanf_example();
    std::cout << "===================sprintf example===================" << std::endl;
    sprintf_example();
    return 0;
}