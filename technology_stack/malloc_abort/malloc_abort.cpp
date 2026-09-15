#include <iostream>
#include <cstdlib>
#include <cstring>

/**
 * 遇到了core在malloc的情况，这是因为遇到了堆破坏：
 *  1. 可能是double free
 *  2. 可能是free了一个不是malloc出来的指针
 *  3. 堆缓冲区溢出，向堆缓冲区写入了超过其大小的数据
 *
 * @note 这种core很难去定位问题，因为其一般发生在有问题代码执行完一段时间后
 *       或者跟core中显示的代码毫无关系
 * @note 可以使用地址消毒器sanitizer来定位问题，或者使用gdb的catch throw来捕获异常，或者使用valgrind来检测内存问题
 */

void test_malloc_abort() {
    int *p = (int *)malloc(sizeof(int));
    free(p);
    free(p); // double free
}

void test_malloc_abort2() {
    int *p = (int *)malloc(sizeof(int));
    free(p);
    p[0] = 1; // use after free
    std::cout << p[0] << std::endl;
}

void test_malloc_abort3() {
    int a = 10;
    int* p = &a;
    free(p); // free a pointer that was not allocated by malloc
}

void test_malloc_abort4() {
    char *p = (char *)malloc(16);
    char *q = (char *)malloc(16);
    memset(p, 'A', 40); // buffer overflow
    free(q); // glibc检测到堆损坏，直接abort奔溃
}

void test_malloc_abort5() {
    char* a = (char*)malloc(0x500);
    malloc(0x20);
    free(a);
    *(void**)((char*)a + 8) = (void*)0x4141414141414140UL;
    // printf("re-malloc...");
    malloc(0x500);

}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " <test_case_number>" << std::endl;
        return 1;
    }

    int test_case = std::stoi(argv[1]);
    switch(test_case) {
        case 1:
            test_malloc_abort();
            break;
        case 2:
            test_malloc_abort2();
            break;
        case 3:
            test_malloc_abort3();
            break;
        case 4:
            test_malloc_abort4();
            break;
        case 5:
            test_malloc_abort5();
            break;
        default:
            std::cout << "Invalid test case number: " << test_case << std::endl;
            return 1;
    }

    return 0;
}