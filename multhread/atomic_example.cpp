/**
https://cplusplus.com/reference/atomic/atomic/
*/

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

  // Compares the contents of the atomic object's contained value with expected:
  // if true, it replaces the contained value with value
  // if false, it replaces expected with the contained value .

  // 区别：
  // compare_exchange_weak() 允许失败，即实际obtain值和expected相等，但是函数返回false
  // compare_exchange_strong() 不允许失败，
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
// CPU提供的一种原子操作CAS（Compare and Swap）,即比较并交换，这是一个原子操作
// 它包含三个操作数，内存值V、旧的预期值oldval、要修改的新值newval
// 当且仅当内存值V等于旧的预期值oldval时，将内存值V修改为新值newval，否则什么都不做

// Atomic flags are boolean atomic objects that support two operations:
// test-and-set and clear.
void show_atomic_flag() {
  // The atomic_flag is in an unspecified state on construction (either set or clear) when no explicit enable 
  // This macro ATOMIC_FLAG_INIT is defined in such a way that it can be used to initialize an object of type atomic_flag to the clear state.
  std::atomic_flag fl = ATOMIC_FLAG_INIT;

  auto append = [&](int id) {
    // test_and_set()函数会将标志位设置为true，并返回原来的标志位
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