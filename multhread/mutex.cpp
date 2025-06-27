#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/**
 * 一些概念：
 * 
 * 1。原子操作：
 *   - 指一次不存在任何中断或者失败的互斥；
 *   - 其一般具有以下状态：
 *     * ① 该操作成功结束； 
 *     * ② 该操作根本未被执行，且未发现任何部分执行的状态；
 * 2.临界区：
 *   - 指一段代码，其对应进程需哟访问共享资源，而另一个进程也处于相同代码区域时，这段代码不会被执行
 * 3.互斥：
 *   - 指当一个进程处于临界区并访问共享资源时，没有其他进程会处于临界区并且访问任何相同的共享资源；
 * 4.死锁：
 *   - 互斥条件：进程要求对所分配的资源进行排它性控制，即在一段时间内某资源仅为一进程所占用。
 *   - 请求和保持条件：当进程因请求资源而阻塞时，对已获得的资源保持不放。
 *   - 进程已获得的资源在未使用完之前，不能剥夺，只能在使用完时由自己释放。
 *   - 发生死锁时，必然存在一个进程–资源的环形链。
 *   - 例子：
 *     * 进程A持有资源1，等待资源2；进程B持有资源2，等待资源1。
 *     * 若无外力介入，两个进程将永远处于阻塞状态。
 */

/**
 * @brief 一个可以上锁的互斥量，其提供独占访问的功能，不支持递归
 */
void mutex_test() {
  // member type
  if(std::is_same<std::mutex::native_handle_type, std::mutex::native_handle_type>::value) {
    std::cout << "std::mutex::native_handle_type is the same as itself." << std::endl;
  } else {
    std::cout << "std::mutex::native_handle_type is NOT the same as itself." << std::endl;
  }

  std::mutex mtx_handle;
  std::mutex::native_handle_type handle = mtx_handle.native_handle();

  // constructor
  std::mutex mtx;
#if 0
  mutex(const mutex&) = delete;  // no copy constructor
#endif

  // lock and unlock
  auto lock_test = [&](int n, char c) {
    mtx.lock();
    for (int i = 0; i < n; ++i) {
      std::cout << c;
    }
    std::cout << '\n';
    mtx.unlock();
  };
  std::thread th1(lock_test, 50, '*');
  std::thread th2(lock_test, 50, '$');
  th1.join();
  th2.join();

  volatile int counter(0);
  std::mutex mtx1; 

  /**
   * bool try_lock()
   *   - 该接口是非阻塞函数，会立即返回
   *   - 如果当前mutex没有被锁定，则会锁定它并返回true
   *   - 如果当前mutex已经被锁定，则不会锁定它并返回false
   */
  auto try_lock_test = [&]() {
    for (int i = 0; i < 10000; ++i) {
      if (mtx1.try_lock()) {  // only increase if currently not locked:
        ++counter;
        mtx1.unlock();
      }
    }
  };

  std::thread threads[10];
  for (int i = 0; i < 10; ++i) threads[i] = std::thread(try_lock_test);
  for (auto& th : threads) th.join();
  std::cout << counter << " successful increases of the counter.\n";
}

/**
 * @brief 死锁测试
 * 
 * 死锁是指两个或多个线程在执行过程中，因为争夺资源而造成的一种互相等待的现象。
 * 在这种情况下，线程无法继续执行，因为每个线程都在等待其他线程释放资源。
 * 
 * 解决死锁的方法包括：
 * 1. 避免死锁：通过设计避免死锁的发生，例如使用资源分配图、避免循环等待等。
 * 2. 检测和恢复：系统可以检测到死锁并采取措施恢复，例如终止某些线程或回滚操作。
 * 
 * 注意：一个线程中连续调用一个锁的lock()方法会导致死锁，因为它会尝试再次锁定已经被自己锁定的mutex。
 */
void dead_lock_test() {
  std::mutex mtx1, mtx2;

  /**
   * lck1.lock
   * lck2.lock 会卡住，因为lck2在另一个线程中被锁定
   */
  auto task1 = [&]() {
    std::lock_guard<std::mutex> lck1(mtx1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lck2(mtx2);
    std::cout << "task 1 completed\n";
  };

  /**
   * lck2.lock
   * lck1.lock 会卡住，因为lck1在另一个线程中被锁定
   */
  auto task2 = [&]() {
    std::lock_guard<std::mutex> lck2(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> lck1(mtx1);
    std::cout << "task 2 completed\n";
  };

  std::thread th1(task1);
  std::thread th2(task2);

  th1.join();
  th2.join();
}

/**
 * @brief 跟mutex类似，但是提供了时间相关的接口
 */
void time_mutex_test() {
  std::timed_mutex tmtx;
  int value = 0;

  /**
   * bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
   * 
   * @brief 尝试在指定的时间内锁定互斥量，至多阻塞rel_time时间。
   * @return 如果成功锁定互斥量，则返回true；其他返回false。
   * 
   * @note 如果在同一个线程中连续调用try_lock_for，会导致死锁，产生为定义行为
   */
  auto fun1 = [&]() {
    for (int i = 0; i < 100; ++i) {
      if (tmtx.try_lock_for(std::chrono::milliseconds(10))) {  // try to lock for 10ms
        ++value;
        tmtx.unlock();
      } else {
        std::cout << "Failed to lock in fun1\n";
      }
    }
  };

  auto fun2 = [&]() {
    for (int i = 0; i < 100; ++i) {
      if (tmtx.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(10))) {  // try to lock until 10ms later
        ++value;
        tmtx.unlock();
      } else {
        std::cout << "Failed to lock in fun2\n";
      }
    }
  };

  std::thread th1(fun1);
  std::thread th2(fun2);
  th1.join();
  th2.join();
  std::cout << "Final value: " << value << std::endl;
}

/**
 * template <class Mutex> 
 * class lock_guard;
 * 
 * @brief 一个管理互斥量的类，其在构造时锁定互斥量，在析构时解锁互斥量。
 */
void lock_guard_test() {
  if(std::is_same<std::lock_guard<std::mutex>::mutex_type, std::mutex>::value) {
    std::cout << "std::lock_guard<std::mutex>::mutex_type is the same as std::mutex." << std::endl;
  } else {
    std::cout << "std::lock_guard<std::mutex>::mutex_type is NOT the same as std::mutex." << std::endl;
  }

  std::mutex mtx;
  int value = 0;

  /**
   * 1. locking initialization
   */
  auto increment_value = [&]() {
    std::lock_guard<std::mutex> lck(mtx);
    for(int i = 0; i < 100; ++i) {
      ++value;  // increment value
    }
  };

  /**
   * 2. adopting initialization
   * 
   * lock_guard(mutex_type& m, adopt_lock_t tag);
   * @brief 表示该锁已经被锁定，lock_guard不会尝试再次锁定它。
   */
  auto print_thread_id = [&](int id) {
    mtx.lock();
    std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);
    for(int i = 0; i < 100; ++i) {
      ++value;
    }
  };

  std::thread threads[10];
  for (int i = 0; i < 10; ++i) threads[i] = std::thread(print_thread_id, i + 1);
  for (auto& th : threads) th.join();
  std::cout << "Final value: " << value << std::endl;
}

/**
 * template <class Mutex> class unique_lock;
 */
void unique_lock_test() {
  if(std::is_same<std::unique_lock<std::mutex>::mutex_type, std::mutex>::value) {
    std::cout << "std::unique_lock<std::mutex>::mutex_type is the same as std::mutex." << std::endl;
  } else {
    std::cout << "std::unique_lock<std::mutex>::mutex_type is NOT the same as std::mutex." << std::endl;
  }

  /**
   * constructor:
   * 1. unique_lock() noexcept;
   *   - 默认构造函数，创建一个未锁定的unique_lock对象。
   * 2. unique_lock(mutex_type& m);
   *   - 构造一个管理m的unique_lock对象，并切调用m.lock()来锁定互斥量。必要时会阻塞
   * 3. unique_lock(mutex_type& m, try_to_lock_t tag);
   *   - 构造一个管理m的unique_lock对象，并调用m.try_lock()来尝试锁定互斥量。非阻塞
   * 4. unique_lock (mutex_type& m, defer_lock_t tag) noexcept;
   *   - 构造一个管理m的unique_lock对象，但不调用任何方法去锁定互斥量。而是保持m当前的状态
   * 5. unique_lock(mutex_type& m, adopt_lock_t tag) noexcept;
   *   - 构造一个管理m的unique_lock对象，并假设m已经被锁定。unique_lock不会尝试再次锁定它。
   *   - 但是在析构时会解锁m。如果m没有被锁定，则会导致未定义行为。
   * 6. template <class Rep, class Period>
   *    unique_lock (mutex_type& m, const chrono::duration<Rep,Period>& rel_time);
   *   - The object manages m, and attempts to lock it during rel_time by calling m.try_lock_for(rel_time).
   * 7.template <class Clock, class Duration>
   *   unique_lock (mutex_type& m, const chrono::time_point<Clock,Duration>& abs_time);
   *   - The object manages m, and attempts to lock it before abs_time by calling m.try_lock_until(abs_time).
   * 8. unique_lock (unique_lock&& x);
   *   - 移动构造函数，将u的获取时的状态转移到新创建的unique_lock对象中。
   *   - x将变得跟调用默认构造函数一样
   * 9. unique_lock(const unique_lock&) = delete;
   */

  std::mutex cur_mtx;
  {
    std::unique_lock<std::mutex> lck(cur_mtx);
    
    /**
     * mutex_type* release() noexcept;
     * 
     * @brief 释放对互斥量的所有权，并返回指向该互斥量的指针。
     * @note 其不会对互斥量进行lock或者unlock操作。
     */
    std::mutex* p_mtx = lck.release();
    std::cout << "Released mutex pointer: " << p_mtx << std::endl;
    std::cout << "mutex address: " << &cur_mtx << std::endl;

    /**
     * bool owns_lock() const noexcept;
     * 
     * @brief 返回当前unique_lock对象是否拥有互斥量的锁。
     * @return 
     *   - true：当拥有的mutex对象是locked状态(或者adopt_lock状态)时，并且没有被release或者unlock时，返回true
     *   - false：不符合上述情况的所有条件
     */
    std::cout << "owns_lock: " << (lck.owns_lock() ? "true" : "false") << std::endl;
    std::unique_lock<std::mutex> lck2(cur_mtx, std::adopt_lock);
    std::cout << "lck2 owns_lock: " << (lck2.owns_lock() ? "true" : "false") << std::endl;

    /**
     * mutex_type* mutex() const noexcept;
     * @brief 返回当前unique_lock对象管理的互斥量的指针。
     * 
     * @note 当前unique_lock并不会释放对互斥量的所有权，仍然会在析构时解锁互斥量。
     */
    std::mutex* p_mtx2 = lck2.mutex();
    std::cout << "Managed mutex pointer: " << p_mtx2 << std::endl;
  }

  /**
   * template <class Mutex1, class Mutex2, class... Mutexes>  
   * void lock (Mutex1& a, Mutex2& b, Mutexes&... cde);
   * 
   * @brief 锁定多个互斥量，如果有必要，阻塞直到所有互斥量都被锁定。
   * @note 该函数可以同时锁定多个互斥量，避免死锁的发生。
   * 
   * template <class Mutex1, class Mutex2, class... Mutexes>  
   * int try_lock (Mutex1& a, Mutex2& b, Mutexes&... cde);
   * @brief 按照参数顺序，使用它们的try_lock()方法尝试锁定多个互斥量。非阻塞。
   * @return
   *   - -1：如果所有互斥量都被锁定，则返回-1
   *   - n：返回锁失败的互斥量的索引，从0开始计数。
   */
  std::mutex foo, bar;

  auto task_a = [&]() {
    std::lock(foo, bar);
    std::unique_lock<std::mutex> lck1(foo, std::adopt_lock);
    std::unique_lock<std::mutex> lck2(bar, std::adopt_lock);
    std::cout << "task a, owns lock? " << ((lck1.owns_lock()) ? "is" : "no") << std::endl;
    std::cout << "task a, owns lock? " << ((lck1) ? "is" : "no") << std::endl;
  };

  auto task_b = [&]() {
    std::unique_lock<std::mutex> lck1, lck2;
    lck1 = std::unique_lock<std::mutex>(bar, std::defer_lock);
    lck2 = std::unique_lock<std::mutex>(foo, std::defer_lock);
    std::cout << "task b, owns lock? " << ((lck1.owns_lock()) ? "is" : "no") << std::endl;
    std::cout << "task b, owns lock? " << ((lck1) ? "is" : "no") << std::endl;
    std::lock(lck1, lck2);
    std::cout << "task b, owns lock? " << ((lck1.owns_lock()) ? "is" : "no") << std::endl;
    std::cout << "task b, owns lock? " << ((lck1) ? "is" : "no") << std::endl;

  };

  std::thread th1(task_a);
  std::thread th2(task_b);

  th1.join();
  th2.join();
}

/**
 * template <class Fn, class... Args>  
 * void call_once (once_flag& flag, Fn&& fn, Args&&... args);
 * 
 * @brief 调用函数fn，除非其他线程正在或者已经调用了使用一样的flag的call_once()。即保证fn只被调用一次
 * @note 即使相同的线程内部，也只有第一次调用call_once()时，fn才会被调用。
 */
void once_flag_test() {
  int winner;
  auto set_winner = [&](int x) { 
    std::cout << "Get x: " << x << std::endl;
    winner = x; 
  };
  std::once_flag winner_flag;

  auto wait_1000ms = [&](int id) {
    for (int i = 0; i < 1000; ++i) std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::call_once(winner_flag, set_winner, id);
  };

  std::thread threads[10];
  for (int i = 0; i < 10; ++i) threads[i] = std::thread(wait_1000ms, i + 1);
  std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";
  for (auto& th : threads) th.join();
  std::cout << "winner thread: " << winner << '\n';
}

int main() {
  std::cout << "===================== mutex test ====================" << std::endl;
  mutex_test();
  std::cout << "===================== dead lock test ====================" << std::endl;
#if 0
  dead_lock_test();
#endif
  std::cout << "===================== time mutex test ====================" << std::endl;
  time_mutex_test();
  std::cout << "===================== lock guard test ====================" << std::endl;
  lock_guard_test();
  std::cout << "===================== unique lock test ====================" << std::endl;
  unique_lock_test();
  std::cout << "===================== once flag test ====================" << std::endl;
  once_flag_test();
  return 0;
}