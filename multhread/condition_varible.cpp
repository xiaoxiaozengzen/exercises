// condition_variable::wait (with predicate)
#include <condition_variable>  // std::condition_variable
#include <iostream>            // std::cout
#include <mutex>               // std::mutex, std::unique_lock
#include <thread>              // std::thread, std::this_thread::yield

std::string get_current_time() {
  auto now = std::chrono::system_clock::now();
  int sec = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
  std::uint32_t nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % 1000000000;
  std::string time_str = "[" + std::to_string(sec) + "." + std::to_string(nanosec) + "]";
  return time_str;
}

/**
 * void wait (unique_lock<mutex>& lck);
 * @brief 阻塞当前线程，并释放锁，直到被通知为止。被通知时，停止阻塞并重新获取锁。
 * 
 * template <class Predicate> void wait (unique_lock<mutex>& lck, Predicate pred);
 * @brief 当pred为flase时，会一直阻塞当前线程。只有当pred为true时，接收到notifaction才会停止阻塞。
 * @note 注意如果在wait之前，pred已经为true了，那么wait不会阻塞。
 * 
 * @note 其中2）可以认为是这样实现的：
 *       while (!pred())
 *          wait(lck);
 */
void wait_test() {
  std::mutex mtx;
  std::condition_variable cv;

  int value = 0;
  std::cerr << get_current_time() << "value = " << value << std::endl;

  auto fun1 = [&]() {
    std::cerr << get_current_time() << "fun1" << std::endl;
    return value == 0;
  };
  std::thread t1([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, fun1);
    std::cerr << get_current_time() << "Thread 1: value = " << value << std::endl;
  });

  auto fun2 = [&]() {
    std::cerr << get_current_time() << "fun2" << std::endl;
    return value == 1;
  };
  std::thread t2([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, fun2);
    std::cerr << get_current_time() << "Thread 2: value = " << value << std::endl;
  });

  std::this_thread::sleep_for(std::chrono::seconds(2));
  {
    std::unique_lock<std::mutex> lck(mtx);
    value = 1;
    cv.notify_all();
  }

  t1.join();
  t2.join();
  std::cerr << get_current_time() << "value = " << value << std::endl;
}


/**
 * template <class Clock, class Duration>
 * cv_status wait_until(unique_lock<mutex>& lck, const chrono::time_point<Clock,Duration>& abs_time);
 * 
 * @brief 阻塞当前线程，直到被通知或者超时。
 * @note wait_for底层是基于wait_until实现的。
 * 
 * enum class cv_status { 
 *    no_timeout,
 *    timeout 
 * };
 */
void wait_until_test() {
  std::mutex mtx;
  std::condition_variable cv;

  int value = 0;
  std::cerr << get_current_time() << "value = " << value << std::endl;

  std::thread t1([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    auto status = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(1));
    if (status == std::cv_status::timeout) {
      std::cerr << get_current_time() << "Thread 1: timeout" << std::endl;
    }
    std::cerr << get_current_time() << "Thread 1: value = " << value << std::endl;
  });

  std::thread t2([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    auto status = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(3));
    if (status == std::cv_status::timeout) {
      std::cerr << get_current_time() << "Thread 2: timeout" << std::endl;
    }
    std::cerr << get_current_time() << "Thread 2: value = " << value << std::endl;
  });

  std::this_thread::sleep_for(std::chrono::seconds(2));
  {
    std::unique_lock<std::mutex> lck(mtx);
    value = 1;
    cv.notify_all();
  }
  t1.join();
  t2.join();
}

/**
 * template <class Clock, class Duration, class Predicate>
 * bool wait_until(unique_lock<mutex>& lck, const chrono::time_point<Clock,Duration>& abs_time, Predicate pred);
 * 
 * @note 只有当pred为false时，才会阻塞当前线程。
 * @note 只有pred为true时，notify才会让当前线程停止阻塞。
 * @note 如果在wait_until之前，pred已经为true了，那么wait_until不会阻塞。
 * 
 * @note 这个函数的实现是这样的：
 *       while (!pred())
 *          if ( wait_until(lck,abs_time) == cv_status::timeout)
 *             return pred();
 *       return true;
 */
void wait_until_pred_test() {
  std::mutex mtx;
  std::condition_variable cv;

  int value = 0;

  // 因为pred在wait_until之前已经为true了，所以wait_until不会阻塞。函数会直接返回true。
  auto fun1 = [&]() {
    std::cerr << get_current_time() << "fun1" << std::endl;
    return value == 0;
  };
  std::thread t1([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    bool ret = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(1), fun1);
    std::cerr << get_current_time() << "Thread 1: value = " << value << ", ret: " << (ret?"true":"false") << std::endl;
  });

  // 会超时，此时pred为false。函数返回pred，即false。
  auto fun2 = [&]() {
    std::cerr << get_current_time() << "fun2" << std::endl;
    return value == 1;
  };
  std::thread t2([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    bool ret = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(1), fun2);
    std::cerr << get_current_time() << "Thread 2: value = " << value << ", ret: " << (ret?"true":"false") << std::endl;
  });

  // 不会超时，此时pred为true。函数返回pred，即true。
  auto fun3 = [&]() {
    std::cerr << get_current_time() << "fun3" << std::endl;
    return value == 1;
  };
  std::thread t3([&]() {
    std::unique_lock<std::mutex> lck(mtx);
    bool ret = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(5), fun3);
    std::cerr << get_current_time() << "Thread 3: value = " << value << ", ret: " << (ret?"true":"false") << std::endl;
  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
  {
    std::unique_lock<std::mutex> lck(mtx);
    value = 1;
    cv.notify_all();
  }
  t1.join();
  t2.join();
  t3.join();
}

/**
 * void notify_all_at_thread_exit (condition_variable& cond, unique_lock<mutex> lck);
 * 
 * @brief 在当前线程退出时，自动调用notify_all。
 * @param cond 条件变量
 * @param lck 锁
 */
void fun_test() {
  std::mutex mtx;
  std::condition_variable cv;
  
  bool ready = false;

  auto print_id = [&](int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) {
      cv.wait(lck);
    }

    std::cout << get_current_time() << "thread " << id << '\n';
  };

  auto go = [&]() {
    std::unique_lock<std::mutex> lck(mtx);
    std::notify_all_at_thread_exit(cv, std::move(lck));
    ready = true;

    std::this_thread::sleep_for(std::chrono::seconds(3));
  };

  std::thread threads[10];
  for (int i = 0; i < 10; ++i) threads[i] = std::thread(print_id, i);

  std::cout << get_current_time() <<  "10 threads ready to race...\n";

  std::thread(go).detach();

  for (auto& th : threads){
    th.join();
  }
}

int main() {
  std::cout << "=============wait_test================" << std::endl;
  wait_test();
  std::cout << "===============wait_until_test==============" << std::endl;
  wait_until_test();
  std::cout << "===============wait_until_pred_test==============" << std::endl;
  wait_until_pred_test();
  std::cout << "===============fun_test==============" << std::endl;
  fun_test();
  return 0;
}