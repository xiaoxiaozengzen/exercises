#include <exception>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

void promise_base() {
  std::promise<int> p1;
  std::promise<int> p2 = std::promise<int>(std::allocator_arg, std::allocator<int>());
  std::promise<int> p3;

  std::future<int> f1 = p1.get_future();
  std::future<int> f2 = p2.get_future();
  std::future<int> f3 = p3.get_future();

  // swap
  p1.swap(p3);

  // 直接抛出异常 std::future_error
  // std::future<int> f2 = p1.get_future();

  std::thread t(
      [](std::future<int>& value) {
        int ret = value.get();
        std::cout << "promise_base ret: " << ret << std::endl;
      },
      std::ref(f1));

  std::thread t2(
      [](std::future<int>& value) {
        try {
          int ret = value.get();
          std::cout << "promise_base_2 ret: " << ret << std::endl;
        } catch (std::exception& ex) {
          std::cout << "Get exception: " << ex.what() << std::endl;
        }
      },
      std::ref(f2));

  std::thread t3(
      [](std::future<int>& value) {
        int ret = value.get();
        std::cout << "promise_base_3 ret: " << ret << std::endl;
      },
      std::ref(f3));

  p1.set_value(10);
  try {
    throw std::runtime_error("hahahaha");
  } catch (std::exception& ex) {
    p2.set_exception(std::current_exception());
  }

  std::thread t4([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int value = 22;
    p3.set_value_at_thread_exit(value);
    value = 32;
  });

  if (t.joinable()) {
    t.join();
  }
  if (t2.joinable()) {
    t2.join();
  }
  if (t3.joinable()) {
    t3.join();
  }
  if (t4.joinable()) {
    t4.join();
  }
}

void package_task_test() {
  std::packaged_task<int(int)> foo;                               // default-constructed
  std::packaged_task<int(int)> bar([](int x) { return x * 2; });  // initialized
  std::cout << "before: foo.valid() " << foo.valid() << ", var.valid() " << bar.valid()
            << std::endl;

  foo = std::move(bar);  // move-assignment
  std::cout << "after move: foo.valid() " << foo.valid() << ", var.valid() " << bar.valid()
            << std::endl;

  std::future<int> ret = foo.get_future();  // get future
  foo(10);                                  // spawn thread and call task
  int value = ret.get();                    // wait for the task to finish and get result
  std::cout << "The double of 10 is " << value << ".\n";

  std::packaged_task<int(int)> foo_delay([](int x) { return x * 3; });
  std::future<int> ret_delay = foo_delay.get_future();  // get future
  std::thread t([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    foo_delay.make_ready_at_thread_exit(20);
  });
  int value_delay = ret_delay.get();
  std::cout << "The three times of 10 is " << value_delay << ".\n";

  foo.reset();  // reset
  ret = foo.get_future();
  foo(40);
  value = ret.get();  // wait for the task to finish and get result
  std::cout << "The double of 40 is " << value << ".\n";

  if (t.joinable()) {
    t.join();
  }
}

void future_base() {
  std::promise<int> p1;
  std::future<int> f1 = p1.get_future();

  std::future<int> f2;
  std::cout << "f1.valid(): " << f1.valid() << ", f2.valid(): " << f2.valid() << std::endl;

  std::thread t([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    p1.set_value(1);
  });
  f1.wait();

  std::promise<int> p2;
  f2 = p2.get_future();
  std::thread t2([&]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    p2.set_value(100);
  });
  std::future_status status = f2.wait_for(std::chrono::seconds(1));
  if (status == std::future_status::ready) {
    std::cout << "f2 is ready" << std::endl;
  } else if (status == std::future_status::timeout) {
    std::cout << "f2 is timeout" << std::endl;
  } else if (status == std::future_status::deferred) {
    std::cout << "f2 is deferred" << std::endl;
  } else {
    std::cout << "f2 is unknowned" << std::endl;
  }
  // get默认会阻塞直到有结果返回
  int ret = f2.get();
#if 0
  // 再次get会抛出std::future_error异常
  ret = f2.get();
#endif
  std::cout << "f2.get = " << ret << std::endl;

  std::promise<int> p3;
  std::future<int> f3 = p3.get_future();
  // shared_future会将future的状态共享，可以多次get。f3被move到shared_1中，并且自身的状态被置为无效
  // 需要get返回值类型支持拷贝，因为get多次调用就是多次返回同一个值
  std::shared_future<int> shared_1(std::move(f3));
  std::shared_future<int> shared_2(shared_1);
  std::thread t3([&]() { p3.set_value(1000); });
  std::cout << "shread_1 get: " << shared_1.get() << std::endl;
  std::cout << "shread_1 get: " << shared_1.get() << std::endl;
  std::cout << "shread_2 get: " << shared_2.get() << std::endl;

  if (t.joinable()) {
    t.join();
  }
  if (t2.joinable()) {
    t2.join();
  }
  if (t3.joinable()) {
    t3.join();
  }
}

void asyn_base() {
  std::future<int> f1 = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 30;
  });
  std::cout << "async_base start " << std::endl;
  std::cout << "async_base f1.get " << f1.get() << std::endl;

  std::future<int> f2 = std::async(std::launch::deferred, []() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 300;
  });
  std::cout << "async_base f2.get " << f2.get() << std::endl;
}

void future_category_test() {
  std::promise<int> prom;

  try {
    prom.get_future();
    prom.get_future();  // throws a std::future_error of the future category
  } catch (std::future_error& e) {
    if (e.code().category() == std::future_category()) {
      std::cerr << "name: " << e.code().category().name() << std::endl;
      std::cerr << "future_error of the future category thrown\n";
    }
  }
}

int main() {
  promise_base();
  package_task_test();
  future_base();
  std::cout << "======================async=============" << std::endl;
  asyn_base();
  future_category_test();
}