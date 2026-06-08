#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

/**
 * 一个类，表示执行线程
 * 1.一个已经初始化的线程对象，表示一个active状态下的 thread of execution，
 *   这样的线程是joinable的，并且包含独一无二的thread id
 * 2.未初始化的线程对象，表示一个non-thread, 这样的线程不是joinable的，并且和所有非joinable的线程共享同一个id
 * 3.joinable的线程可以通过join和detach变成非joinable的线程，非joinable的线程不能再变成joinable的线程
 */

void MemberType() {
  // id
  std::thread::id id = std::this_thread::get_id();
  std::cout << "std::thread::id: " << id << std::endl;
  std::thread t_no_init;
  std::thread::id id_no_init = t_no_init.get_id();
  std::cout << "std::thread::id of no init thread: " << id_no_init << std::endl;

  std::thread t = std::thread([]() {
    std::thread::id id = std::this_thread::get_id();
    std::cout << "std::thread::id: " << id << std::endl;
    pid_t posix_thread_id = syscall(SYS_gettid);
    std::cout << "posix_thread_id: " << posix_thread_id << std::endl;
  });

  // native_handle_type
  std::thread::native_handle_type handle = t.native_handle();
  pthread_t t_id = t.native_handle();
  if (t.joinable()) {
    t.join();
  }
}

void thread_pthread() {
  int i = 2;
  std::thread t([&]() {
    while (i > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i--;
    }
  });

  pthread_t t_id = t.native_handle();
  pthread_setname_np(t_id, "nihao");

  char name[16];
  pthread_getname_np(t_id, name, sizeof(name));
  std::cout << "Thread name: " << name << std::endl;

  if (t.joinable()) {
    t.join();
  }
}

/**
 * thread会检查传入的参数是否可调用，如果不可调用会编译报错
 * 1.如果传入的参数是一个值，那么会进行一次复制，线程函数中使用的是复制的参数，因此对参数的修改不会影响到外部的变量
 * 2.如果传入的参数是一个引用，那么线程函数中使用的是外部的变量，因此对参数的修改会影响到外部的变量
 * 3.如果传入的参数是一个右值，那么会进行一次移动，线程函数中使用的是移动后的参数，因此对参数的修改会影响到外部的变量
 */
void thread_ref() {
#if 0
  // 编译报错：
  // error: static assertion failed: std::thread arguments must be invocable after conversion to rvalues
  int a = 10;
  std::thread t([](int& a) { a += 1; }, a);
  if (t.joinable()) {
    t.join();
  }
  std::cout << "thread_ref a: " << a << std::endl;
#endif

  int b = 20;
  std::thread t2([](int& b) { b += 1; }, std::ref(b));
  if (t2.joinable()) {
    t2.join();
  }
  std::cout << "thread_ref b: " << b << std::endl;

  int c = 30;
  std::thread t3([](int&& c) { c += 1; }, std::move(c));
  if (t3.joinable()) {
    t3.join();
  }
  std::cout << "thread_ref c: " << c << std::endl;

  int d = 40;
  std::thread t4([](int d) { d += 1; }, d);
  if (t4.joinable()) {
    t4.join();
  }
  std::cout << "thread_ref d: " << d << std::endl;
}

std::atomic<int> global_counter(0);

void increase_global(int n) {
  for (int i = 0; i < n; ++i) ++global_counter;
}

void increase_reference(std::atomic<int>& variable, int n) {
  for (int i = 0; i < n; ++i) ++variable;
}

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}
  void increase_member(int n) {
    for (int i = 0; i < n; ++i) fetch_add(1);
  }
};

void ConFun() {
  std::thread t;  // default constructor
  if (t.joinable()) {
    t.join();
  }

  // std::thread t2 = t1; // copy constructor is deleted
  std::thread t3 = std::move(t);  // move constructor
  if (t3.joinable()) {
    t3.join();
  }

  // initialize
  std::cout << "increase global counter with increase_global" << std::endl;
  std::thread t4(increase_global, 10);
  if (t4.joinable()) {
    t4.join();
  }
  std::cout << "global_counter: " << global_counter.load() << std::endl;

  std::cout << "increase counter (foo) with increase_reference" << std::endl;
  std::atomic<int> foo(0);
  std::thread t5 = std::thread(increase_reference, std::ref(foo), 10);
  if (t5.joinable()) {
    t5.join();
  }
  std::cout << "foo: " << foo.load() << std::endl;

  std::cout << "increase counter (bar) with 10 struct C" << std::endl;
  C bar;
  std::thread t6 = std::thread(&C::increase_member, &bar, 15);
  if (t6.joinable()) {
    t6.join();
  }
  std::cout << "bar: " << bar.load() << std::endl;
}

void MemFun() {
  std::thread t([]() { std::cout << "t, thread id: " << std::this_thread::get_id() << std::endl; });
  if (t.joinable()) {
    std::cout << "t, thread id: " << t.get_id() << " is joinable" << std::endl;
    t.join();
  }

  std::thread t3(
      []() { std::cout << "t3, thread id: " << std::this_thread::get_id() << std::endl; });
  pthread_t t_id = t3.native_handle();
  pthread_setname_np(t_id, "nihao");
  if (t3.joinable()) {
    t3.join();
  }

  if (t.joinable()) {
    t.join();
  } else {
    std::cout << "t, is not joinable" << std::endl;
  }

  std::thread t2(
      []() { std::cout << "t2, thread id: " << std::this_thread::get_id() << std::endl; });

  t.swap(t2);
  if (t.joinable()) {
    std::cout << "t, thread id: " << t.get_id() << " is joinable" << std::endl;
    t.join();
  } else {
    std::cout << "t, is not joinable" << std::endl;
  }
  if (t2.joinable()) {
    std::cout << "t2, thread id: " << t2.get_id() << " is joinable" << std::endl;
    t2.join();
  } else {
    std::cout << "t2, is not joinable" << std::endl;
  }

  std::cout << "hardware_concurrency: " << std::thread::hardware_concurrency() << std::endl;
}

class A {
 public:
  A() { std::cout << "construct" << std::endl; }

  explicit A(std::string a) : a(a) { std::cout << "another construct" << std::endl; }

  ~A() { std::cout << "deconstruct" << std::endl; }

  A(const A& other) {
    std::cout << "copy construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(const A& other) {
    std::cout << "copy assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

  A(A&& other) {
    std::cout << "move construct" << std::endl;
    this->a = other.a;
  }

  A& operator=(A&& other) {
    std::cout << "move assign construct" << std::endl;
    this->a = other.a;
    return *this;
  }

 public:
  std::string a = "";
};

class Base {
 public:
  Base() { std::cout << "Base construct" << std::endl; }

  virtual ~Base() { std::cout << "Base deconstruct" << std::endl; }

 public:
  virtual void Print(A& a) { std::cout << "Base Print: " << a.a << std::endl; }
};

class Derived : public Base {
 public:
  Derived() { std::cout << "Derived construct" << std::endl; }

  ~Derived() { std::cout << "Derived deconstruct" << std::endl; }

  void Print(A& a) override { std::cout << "Derived Print: " << a.a << std::endl; }
};

void ThreadTest() {
  A a("nihao");
  std::thread t([](A& a) { std::cout << "A a: " << a.a << std::endl; }, std::ref(a));
  if (t.joinable()) {
    t.join();
  }

  // 编译报错：error: static assertion failed: std::thread arguments must be invocable after
  // conversion to rvalues 错误是因为 std::thread 会将传入的参数转换为 rvalue，而 A
  // 类中没有移动构造函数，所以编译报错 std::thread t2([](A a) {
  //     std::cout << "A a: " << a.a << std::endl;
  // }, a);
  // if(t2.joinable()) {
  //     t2.join();
  // }

  std::shared_ptr<A> a_ptr = std::make_shared<A>("nihao");
  std::thread t3([](std::shared_ptr<A>& a_ptr) { std::cout << "A a: " << a_ptr->a << std::endl; },
                 std::ref(a_ptr));
  if (t3.joinable()) {
    t3.join();
  }

  std::unique_ptr<A> a_unique_ptr = std::make_unique<A>("nihao");
  std::thread t4(
      [](std::unique_ptr<A>& a_unique_ptr) {
        std::cout << "A a: " << a_unique_ptr->a << std::endl;
      },
      std::ref(a_unique_ptr));
  if (t4.joinable()) {
    t4.join();
  }

  std::shared_ptr<Base> base_ptr = std::make_shared<Derived>();
  std::thread t5(&Base::Print, base_ptr, std::ref(a));
  if (t5.joinable()) {
    t5.join();
  }

  auto& aa = a;
  std::thread t6([](A& a) { std::cout << "A a: " << a.a << std::endl; }, std::ref(aa));
  if (t6.joinable()) {
    t6.join();
  }

  // 报错：error: static assertion failed: std::thread arguments must be invocable after conversion
  // to rvalues const auto& aaa = a; std::thread t7([](A& a) {
  //     std::cout << "A a: " << a.a << std::endl;
  // }, std::ref(aaa));
  // if(t7.joinable()) {
  //     t7.join();
  // }

  const auto& aaaa = a;
  std::thread t8([](const A& a) { std::cout << "A a: " << a.a << std::endl; }, std::ref(aaaa));
  if (t8.joinable()) {
    t8.join();
  }
}


std::atomic<int> detach_counter(0);
/**
 * 当有嵌套的线程时，外层线程会等待内层线程结束后才会结束，因此外层线程的join会等待内层线程的join结束后才会返回
 * 1.当外层线程调用join时，如果内层线程还没有结束，那么外层线程会阻塞，直到内层线程结束后才会返回
 * 2.当外层线程调用detach时，外层线程会立即返回，内层线程会继续执行，直到内层线程结束后才会释放资源
 * 3.当外层线程调用join时，如果内层线程已经结束，那么外层线程会立即返回，不会阻塞
 * 4.当外层线程调用detach时，如果内层线程已经结束，那么外层线程会立即返回，不会阻塞
 *
 * 有些场景就需要 detach，它仅仅是让线程独立执行，并不会让调用它的线程等待它。
 * 1.detach线程函数内部是一个无限循环
 * 2.detach线程函数内部的循环需要有终止条件，且这个终止条件需要在外部线程中修改，这样才能让detach线程正常退出，否则会导致资源泄漏
 */
void join_detach_test() {
  std::thread t([&]() {
    for(;detach_counter.load() < 5;) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cerr << "join_detach_test, thread id: " << std::this_thread::get_id() << std::endl;
    }
    std::cerr << "join_detach_test, thread id: " << std::this_thread::get_id() << " is exiting" << std::endl;
  });
  if(t.joinable()) {
    t.detach();
  }

}

int main() {
  pid_t pid = getpid();
  std::cout << "pid: " << pid << std::endl;
  pid_t posix_thread_id = syscall(SYS_gettid);
  std::cout << "posix_thread_id: " << posix_thread_id << std::endl;
  std::thread::id id = std::this_thread::get_id();
  std::cout << "std::thread::id: " << id << std::endl;
  std::cout << "--------------------------MemberType----------------------------" << std::endl;
  MemberType();
  std::cout << "--------------------------thread_pthread----------------------------" << std::endl;
  thread_pthread();
  std::cout << "--------------------------thread_ref----------------------------" << std::endl;
  thread_ref();
  std::cout << "--------------------------ConFun----------------------------" << std::endl;
  ConFun();
  std::cout << "--------------------------MemFun----------------------------" << std::endl;
  MemFun();
  std::cout << "--------------------------ThreadTest----------------------------" << std::endl;
  ThreadTest();
  std::cout << "--------------------------join_detach_test----------------------------" << std::endl;
  std::thread t(join_detach_test);

  while(detach_counter.load() < 10) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    detach_counter.fetch_add(1);
    std::cerr << "main thread, thread id: " << std::this_thread::get_id() << ", detach_counter: " << detach_counter.load() << std::endl;
  }

  if (t.joinable()) {
    t.join();
  }

  return 0;
}