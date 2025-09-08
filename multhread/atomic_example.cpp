#include <sched.h>
#include <time.h>

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

/**
 * template <class T> struct atomic;
 * 
 * 拷贝构造函数和赋值运算符被删除
 */
void show_atomic_base() {
  std::atomic<int> defalut_value;
  std::atomic<int> value(10);

  /**************** general operation ****************** */
  std::cout << "is_lock_free: " << value.is_lock_free() << std::endl;
  value.store(20);
  int loda_ret = value.load();
  std::cout << "loda_ret: " << loda_ret << std::endl;
  int ret = value;
  std::cout << "ret: " << ret << std::endl;
  int before_ret = value.exchange(30);
  std::cout << "before_ret: " << before_ret << ", value: " << value << std::endl;

  /**
   * bool compare_exchange_weak (T& expected, T val, memory_order sync = memory_order_seq_cst) volatile noexcept
   * @brief 比较原子变量对象contained value和expected的值是否相等
   *        如果相等，则将原子变量对象contained value的值修改为val
   *        如果不相等，则将expected的值修改为原子变量对象contained value的值
   * @param expected 传入时表示预期值，传出时表示实际值
   * @param val 新值
   * @param sync 内存序，默认是memory_order_seq_cst
   * @return 如果原子变量对象contained value和expected的值相等，返回true，否则返回false
   * 
   * @note compare_exchange_weak() 允许失败，即实际obtain值和expected相等，但是函数返回false
   * @note compare_exchange_strong() 不允许失败，
   */
  int expected_value = 30;
  int new_value = 35;
  std::cout << "value: " << value << std::endl;
  bool is_same = value.compare_exchange_weak(expected_value, new_value);
  std::cout << "is_same: " << is_same << ", value: " << value
            << ", expected value: " << expected_value << ", new_value: " << new_value << std::endl;

  expected_value = 40;
  new_value = 45;
  is_same = value.compare_exchange_strong(expected_value, new_value);
  std::cout << "is_same: " << is_same << ", value: " << value
            << ", expected value: " << expected_value << ", new_value: " << new_value << std::endl;
}

void show_atomic_specifaction() {
  std::atomic<int> value(10);
  value.fetch_add(10);
  std::cout << "value: " << value << std::endl;

  value.fetch_sub(15);
  std::cout << "value: " << value << std::endl;

  value.fetch_and(10);
  std::cout << "value: " << value << std::endl;

  value++;
  std::cout << "value: " << value << std::endl;

  value--;
  std::cout << "value: " << value << std::endl;

  value += 10;
  std::cout << "value: " << value << std::endl;
}

/******************************CAS******************************* */
/**
 * CPU提供的一种原子操作CAS（Compare and Swap）,即比较并交换，这是一个原子操作，它包含三个操作数
 *    - 内存值V
 *    - 旧的预期值oldval 
 *    - 要修改的新值newval
 * 当且仅当内存值V等于旧的预期值oldval时，将内存值V修改为新值newval，否则什么都不做
 */

/**
 * atomic_flag提供了两种操作：
 *  - test_and_set(): 以原子方式将标志设置为true，并返回标志的先前值
 *  - clear(): 以原子方式将标志设置为false
 */
void show_atomic_flag() {
  /**
   * atomic_flag创建的时候状态是不确定的（可能是set，也可能是clear），除非显式地初始化
   * 这个宏ATOMIC_FLAG_INIT被定义成可以用来初始化atomic_flag对象为clear状态
   */
  std::atomic_flag fl = ATOMIC_FLAG_INIT;

  auto append = [&](int id) {
    while (fl.test_and_set()) {
    }
    std::cout << "id: " << id << std::endl;
    // 清楚标志位，设置成false。使得下次调用set_and_test()返回false
    fl.clear();
  };

  std::vector<std::thread> threads;

  for (int i = 0; i < 10; i++) {
    threads.push_back(std::thread(append, i));
  }

  for (int i = 0; i < 10; i++) {
    if (threads[i].joinable()) {
      threads[i].join();
    }
  }
}

/********************自旋锁的简单实现******************************/
inline void yield(size_t k) noexcept {
  if (k < 4) {
  } else if (k < 16) {
    // The pause instruction improves the performance of spin-wait loops. When
    // executing a "spin-wait loop," a Pentium 4 or Intel Xeon processor suffers
    // a severe performance penalty when exiting the loop because it detects a
    // possible memory order violation. The pause instruction provides a hint to
    // the processor that the code sequence is a spin-wait loop. The processor
    // uses this hint to avoid the memory order violation in most situations,
    // which greatly improves processor performance. For this reason, it is
    // recommended that a PAUSE instruction be placed in all spin-wait loops.
    // The PAUSE instruction is only available on Pentium 4, Intel Xeon, and
    // later processors (IA-32 architectures that include the SSE2 instruction
    // set).
    // asm volatile("pause" ::: "memory");

    // But we're using the f2cking ARMv7, so we'll just do nothing here.
  } else if (k < 32 || k & 1) {
    sched_yield();
  } else {
    timespec ts = {0, 0};
    ts.tv_nsec = 1000;
    nanosleep(&ts, nullptr);
  }
}

class spinlock {
 public:
  std::atomic_flag v_ = ATOMIC_FLAG_INIT;
  size_t max_try_times = 0;

 public:
  bool try_lock() noexcept { return !v_.test_and_set(std::memory_order_acquire); }

  void lock() noexcept {
    size_t k = 0;
    for (; !try_lock(); ++k) {
      yield(k);
    }

    // Debug Info
    max_try_times = k > max_try_times ? k : max_try_times;
  }

  void unlock() noexcept { v_.clear(std::memory_order_release); }

 public:
  class scoped_lock {
   private:
    spinlock& sp_;

    scoped_lock(scoped_lock const&);
    scoped_lock& operator=(scoped_lock const&);

   public:
    explicit scoped_lock(spinlock& sp) noexcept : sp_(sp) { sp.lock(); }

    ~scoped_lock() { sp_.unlock(); }
  };
};

void TestSpinLock() {
  int a = 10;
  spinlock lc;

  auto fun = [&]() {
    spinlock::scoped_lock its_lock(lc);
    a += 1;
    std::cout << "a: " << a << std::endl;
  };

  std::vector<std::thread> threads;

  for (int i = 0; i < 10; i++) {
    threads.push_back(std::thread(fun));
  }

  for (int i = 0; i < 10; i++) {
    if (threads[i].joinable()) {
      threads[i].join();
    }
  }
}

void FunForAtomicCStyle() {
  std::atomic<int> value(10);
  bool is_lock_free = atomic_is_lock_free(&value);
  std::cout << "atomic_is_lock_free(&value): " << is_lock_free << std::endl;

  // 对已经初始化过的原子对象调用atomic_init()是未定义行为
  std::atomic<int> value2;
  atomic_init(&value2, 20);
  std::cout << "value2: " << value2.load() << std::endl;

  atomic_store(&value2, 30);
  std::cout << "value2: " << value2.load() << std::endl;

  int ret = atomic_load(&value2);
  std::cout << "atomic_load(&value2): " << ret << std::endl;

  int before_ret = atomic_exchange(&value2, 40);
  std::cout << "before_ret: " << before_ret << ", value2: " << value2.load() << std::endl;

  std::atomic_flag flag = ATOMIC_FLAG_INIT;
  bool is_set_before = atomic_flag_test_and_set(&flag);
  std::cout << "is_set_before: " << is_set_before << std::endl;
  atomic_flag_clear(&flag);

}

int main() {
  std::cout << "==================show_atomic_base====================" << std::endl;
  show_atomic_base();
  std::cout << "==================show_atomic_specifaction====================" << std::endl;
  show_atomic_specifaction();
  std::cout << "==================show_atomic_flag====================" << std::endl;
  show_atomic_flag();
  std::cout << "==================TestSpinLock====================" << std::endl;
  TestSpinLock();
  std::cout << "==================FunForAtomicCStyle====================" << std::endl;
  FunForAtomicCStyle();
  return 0;
}