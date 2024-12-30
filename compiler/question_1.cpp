/**
 * Question: auto/auto&/const auto& 类型的推导
 */

#include <iostream>
#include <thread>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> my_map = {
    {"a", 1},
    {"b", 2},
    {"c", 3}
};

std::unordered_map<std::string, std::thread> my_threads;
void my_fun(std::string& key) {
    std::cout << "key: " << key << std::endl;
}

std::unordered_map<std::string, std::thread> my_threads2;
void my_fun1(const std::string& key) {
    std::cout << "key: " << key << std::endl;
}

int main() {
  // 编译报错：error: static assertion failed: std::thread arguments must be invocable after conversion to rvalues
  // for(const auto& map_value : my_map) {
  //   my_threads[map_value.first] = std::thread(my_fun, std::ref(map_value.first));
  // }

  // for(auto& thread : my_threads) {
  //   if(thread.second.joinable()) {
  //       thread.second.join();
  //   }
  // }

  // 正常编译和运行
  for(const auto& map_value : my_map) {
    my_threads2[map_value.first] = std::thread(my_fun1, std::cref(map_value.first));
  }
  for(auto& thread : my_threads2) {
    if(thread.second.joinable()) {
        thread.second.join();
    }
  }
}