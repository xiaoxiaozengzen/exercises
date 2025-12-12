#include <strings.h> // POSIX: strncasecmp
#include <string.h> // POSIX: strcpy

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

void fprintf_example() {
    int intValue = 123;
    float floatValue = 45.67f;
    const char *strValue = "Hello";

    /**
     * int fprintf(FILE *stream, const char *format, ...)
     * @brief 将格式化数据写入指定的文件流
     * @param stream 文件流指针
     * @param format 格式字符串
     * @param ... 输入变量
     * @return 写入的字符数
     */
    int count = fprintf(stdout, "intValue: %d, floatValue: %.2f, strValue: %s\n", intValue, floatValue, strValue);
    std::cout << "写入的字符数: " << count << std::endl;

    const char *filePath = "/mnt/workspace/cgz_workspace/Exercise/exercises/linux/output/test.txt";
    FILE *file = fopen(filePath, "w");
    if (file != nullptr) {
        count = fprintf(file, "intValue: %d, floatValue: %.2f, strValue: %s\n", intValue, floatValue, strValue);
        std::cout << "写入文件的字符数: " << count << std::endl;
        fclose(file);
    } else {
        std::cerr << "无法打开文件: " << filePath << std::endl;
    }
}

void strcpy_example() {
    const char *source = "Hello, World!";
    char destination[50];

    /**
     * @brief 复制字符串
     * @param dest 目标字符串缓冲区
     * @param src 源字符串
     * @return 指向目标字符串的指针
     */
    char *result = strcpy(destination, source);
    std::cout << "源字符串: " << source  << ", address: " << reinterpret_cast<void*>(const_cast<char*>(source)) << std::endl;
    std::cout << "目标字符串: " << destination << ", address: " << reinterpret_cast<void*>(destination) << std::endl;
    std::cout << "返回值: " << result << ", address: " << reinterpret_cast<void*>(result) << std::endl;
}

void strcat_example() {
    char buf[16] = "abc";
    const char *app = "123456789123456";
    
    /**
     * @brief 将dest的\0去掉，并将src的第一个字符写到该位置，然后在dest的末尾添加\0
     * @param dest 目标字符串缓冲区
     * @param src 源字符串
     * @return 指向目标字符串的指针
     */
    char* result = strcat(buf, app); // 可能会导致缓冲区溢出
    std::cout << "buf after strcat: " << buf << std::endl;
    std::cout << "result of strcat: " << result << std::endl;

    char buf_safe[10] = "abc";
    /**
     * @brief 将source的前num字符拼接到dest的末尾，并添加\0。若source的长度小于num，则只拼接source的全部内容。
     * @param destination 目标字符串缓冲区
     * @param source 源字符串
     * @param num 目标缓冲区大小
     * @return 指向目标字符串的指针
     */
    strncat(buf_safe, app, sizeof(buf_safe) - strlen(buf_safe) - 1); // 保证不会导致缓冲区溢出
    std::cout << "buf_safe after strncat: " << buf_safe << std::endl;
}

int main() {
    std::cout << "===================stracasecmp example===================" << std::endl;
    stracasecmp_example();
    std::cout << "===================sscanf example===================" << std::endl;
    sscanf_example();
    std::cout << "===================sprintf example===================" << std::endl;
    sprintf_example();
    std::cout << "===================fprintf example===================" << std::endl;
    fprintf_example();
    std::cout << "===================strcpy example===================" << std::endl;
    strcpy_example();
    std::cout << "===================strcat example===================" << std::endl;
    strcat_example();
    return 0;
}