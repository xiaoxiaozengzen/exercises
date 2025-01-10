#include <iostream>
#include <mutex>
#include <thread>

// 存储器指定符，参考 https://www.cnblogs.com/bwbfight/p/18025752
/**
 * thread_local
 * thread_local关键字是C++11引入的，用于声明线程局部存储变量。线程局部存储变量是指每个线程都有自己的变量，线程之间互不干扰。
 */
//

// 对于全局变量，每个线程都会在线程初始化时拷贝一个自己的x副本，互不影响
std::mutex cout_mutex;  //方便多线程打印， 加锁指示为了方便多线程打印
thread_local int x = 1;
void thread_func(const std::string& thread_name) {
  for (int i = 0; i < 10; i++) {
    x++;
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
  }
}

// 局部变量，每个线程都会有自己的副本
std::mutex local_count_mutex;
void local_thread_func(const std::string& thread_name) {
  for (int i = 0; i < 3; ++i) {
    //只在每个线程创建时初始化一次，之后的每次调用都是上一次的值
    // 如果不加thread_local，相当于局部变量
    // 如果改成static int x = 1;，每次输出的结果都是不相同的，是线程不安全的,没有在锁里面
    thread_local int x = 1;
    x++;
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
  }
}

int main() {
  std::thread t1(thread_func, "t1");
  std::thread t2(thread_func, "t2");
  t1.join();
  t2.join();
  std::cout << "main thread: x = " << x << std::endl;
  std::thread t3(local_thread_func, "t3");
  std::thread t4(local_thread_func, "t4");
  t3.join();
  t4.join();
  return 0;
}