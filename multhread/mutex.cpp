// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <vector>

void mutex_test() {
  std::mutex mtx;           // mutex for critical section

  auto print_block = [&](int n, char c) {
    // critical section (exclusive access to std::cout signaled by locking mtx):
    mtx.lock();
    for (int i=0; i<n; ++i) { std::cout << c; }
    std::cout << '\n';
    mtx.unlock();
  };


  volatile int counter (0); // non-atomic counter
  std::mutex mtx1;           // locks access to counter

  auto attempt_10k_increases = [&]() {
    for (int i=0; i<10000; ++i) {
      if (mtx1.try_lock()) {   // only increase if currently not locked:
        ++counter;
        mtx1.unlock();
      }
    }
  };


  std::mutex::native_handle_type handle = mtx.native_handle();

  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
      threads[i] = std::thread(attempt_10k_increases);

  for (auto& th : threads) th.join();
  std::cout << counter << " successful increases of the counter.\n";
}

void lock_guard_test() {
  std::mutex mtx;

  auto print_thread_id = [&](int id) {
    mtx.lock();
    std::lock_guard<std::mutex> lck (mtx, std::adopt_lock);
    std::cout << "thread #" << id << '\n';
  };

  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_thread_id,i+1);

  for (auto& th : threads) th.join();

}

void unique_lock_test() {
  // base
  std::mutex foo,bar;

  auto task_a = [&]() {
    std::lock (foo,bar);         // simultaneous lock (prevents deadlock)
    std::unique_lock<std::mutex> lck1 (foo,std::adopt_lock);
    std::unique_lock<std::mutex> lck2 (bar,std::adopt_lock);
    std::cout << "task a, owns lock? " << ((lck1.owns_lock())?"is":"no") << std::endl;
    std::cout << "task a, owns lock? " << ((lck1)?"is":"no") << std::endl;
    // (unlocked automatically on destruction of lck1 and lck2)
  };

  auto task_b = [&]() {
    // foo.lock(); bar.lock(); // replaced by:
    std::unique_lock<std::mutex> lck1, lck2;
    lck1 = std::unique_lock<std::mutex>(bar,std::defer_lock);
    lck2 = std::unique_lock<std::mutex>(foo,std::defer_lock);
    std::cout << "task b, owns lock? " << ((lck1.owns_lock())?"is":"no") << std::endl;
    std::cout << "task b, owns lock? " << ((lck1)?"is":"no") << std::endl;
    std::lock (lck1,lck2);       // simultaneous lock (prevents deadlock)
    // (unlocked automatically on destruction of lck1 and lck2)
  };

  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  // release
  std::mutex mtx;
  int count = 0;
  auto print_count_and_unlock = [&](std::mutex* p_mtx) {
    std::cout << "count: " << count << '\n';
    p_mtx->unlock();
  };
  auto task = [&]() {
    std::unique_lock<std::mutex> lck(mtx);
    ++count;
    print_count_and_unlock(lck.release());
  };
  std::vector<std::thread> threads;
  for (int i=0; i<10; ++i)
    threads.emplace_back(task);

  for (auto& x: threads) x.join();
}

void once_flag_test() {
  int winner;
  auto set_winner = [&](int x) { winner = x; };
  std::once_flag winner_flag;

  auto wait_1000ms = [&](int id) {
    // count to 1000, waiting 1ms between increments:
    for (int i=0; i<1000; ++i)
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // claim to be the winner (only the first such call is executed):
    std::call_once (winner_flag,set_winner,id);
  };  

  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(wait_1000ms,i+1);

  std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";

  for (auto& th : threads) th.join();
  std::cout << "winner thread: " << winner << '\n';
}

void func_lock() {
  std::mutex foo,bar;
  std::mutex foo1,bar1;

  auto task_a = [&] () {
    // foo.lock(); bar.lock(); // replaced by:
    std::lock (foo,bar);
    std::cout << "task a\n";
    foo.unlock();
    bar.unlock();
  };

  auto task_b = [&] () {
    int ret = std::try_lock (bar1,foo1);
    std::cout << "task b: ret " << ret << std::endl;;
    bar1.unlock();
    foo1.unlock();
  };

  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();  
}

int main ()
{
  mutex_test();
  lock_guard_test();
  unique_lock_test();
  once_flag_test();
  func_lock();
  return 0;
}