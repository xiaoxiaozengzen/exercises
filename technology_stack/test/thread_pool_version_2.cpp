#include <stdlib.h>
#include <iostream>

#include "thread_pool/version_2.hpp"

void test(int id) {
  printf("test %d\n", id);
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test2(int id) {
  while(true) {
    printf("test2 %d\n", id);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void test3(int id) {
  while(true) {
    printf("test3 %d\n", id);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void test4(int id) {
  while(true) {
    printf("test4 %d\n", id);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  ctpl::thread_pool pool(2);

  pool.push(test);
  pool.push(test2);
  pool.push(test3);
  pool.push(test4);
}