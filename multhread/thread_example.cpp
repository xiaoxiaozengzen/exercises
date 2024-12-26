#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <iostream>
#include <thread>
#include <atomic>

void ThreadType() {
    std::thread::id id = std::this_thread::get_id();
    std::cout << "std::thread::id: " << id << std::endl;
    std::thread t = std::thread([]() {
        std::thread::id id = std::this_thread::get_id();
        std::cout << "std::thread::id: " << id << std::endl;
        pid_t posix_thread_id = syscall(SYS_gettid);
        std::cout << "posix_thread_id: " << posix_thread_id << std::endl;
    });
    std::thread::native_handle_type handle = t.native_handle();
    pthread_t t_id = t.native_handle();
    if(t.joinable()) {
        t.join();
    }
}

void thread_pthread() {
    int i = 2;
    std::thread t([&]() {
        while (i>0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            i--;
        }
    });

    pthread_t t_id = t.native_handle();
    pthread_setname_np(t_id, "nihao");

    if (t.joinable()) {
        t.join();
    }
}

void thread_ref() {
    int a = 10;
    std::thread t([](int& a) { a += 1; }, std::ref(a));

    int b = 20;
    std::thread t2([](int& b) { b += 1; }, std::ref(b));

    if (t.joinable()) {
        t.join();
    }
    if(t2.joinable()) {
        t2.join();
    }

    std::cout << "thread_ref a: " << a << std::endl;
    std::cout << "thread_ref b: " << b << std::endl;
}

std::atomic<int> global_counter(0);

void increase_global(int n) { for (int i=0; i<n; ++i) ++global_counter; }

void increase_reference(std::atomic<int>& variable, int n) { for (int i=0; i<n; ++i) ++variable; }

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}
  void increase_member (int n) { for (int i=0; i<n; ++i) fetch_add(1); }
};

void ConFun() {
    std::thread t; // default constructor
    if(t.joinable()) {
        t.join();
    }

    // std::thread t2 = t1; // copy constructor is deleted
    std::thread t3 = std::move(t); // move constructor
    if(t3.joinable()) {
        t3.join();
    }

    // initialize
    std::cout << "increase global counter with increase_global" << std::endl;
    std::thread t4(increase_global, 10);
    if(t4.joinable()) {
        t4.join();
    }
    std::cout << "global_counter: " << global_counter.load() << std::endl;

    std::cout << "increase counter (foo) with increase_reference" << std::endl;
    std::atomic<int> foo(0);
    std::thread t5 = std::thread(increase_reference, std::ref(foo), 10);
    if(t5.joinable()) {
        t5.join();
    }
    std::cout << "foo: " << foo.load() << std::endl;

    std::cout << "increase counter (bar) with 10 struct C" << std::endl;
    C bar;
    std::thread t6 = std::thread(&C::increase_member, &bar, 15);
    if(t6.joinable()) {
        t6.join();
    }
    std::cout << "bar: " << bar.load() << std::endl;
}

void MemFun() {
    std::thread t([]() {
        std::cout << "t, thread id: " << std::this_thread::get_id() << std::endl;
    });
    if(t.joinable()) {
        std::cout << "t, thread id: " << t.get_id() << " is joinable"<< std::endl;
        t.join();
    }

    std::thread t3([]() {
        std::cout << "t3, thread id: " << std::this_thread::get_id() << std::endl;
    });
    pthread_t t_id = t3.native_handle();
    pthread_setname_np(t_id, "nihao");
    if(t3.joinable()) {
        t3.join();
    }

    if(t.joinable()) {
        t.join();
    } else {
        std::cout << "t, is not joinable"<< std::endl;
    }

    std::thread t2([]() {
        std::cout << "t2, thread id: " << std::this_thread::get_id() << std::endl;
    });

    t.swap(t2);
    if(t.joinable()) {
        std::cout << "t, thread id: " << t.get_id() << " is joinable"<< std::endl;
        t.join();
    } else {
        std::cout << "t, is not joinable"<< std::endl;
    }
    if(t2.joinable()) {
        std::cout << "t2, thread id: " << t2.get_id() << " is joinable"<< std::endl;
        t2.join();
    } else {
        std::cout << "t2, is not joinable"<< std::endl;
    }

    std::cout << "hardware_concurrency: " << std::thread::hardware_concurrency() << std::endl;
}

int main() {
    pid_t pid = getpid();
    std::cout << "pid: " << pid << std::endl;
    pid_t posix_thread_id = syscall(SYS_gettid);
    std::cout << "posix_thread_id: " << posix_thread_id << std::endl;
    std::thread::id id = std::this_thread::get_id();
    std::cout << "std::thread::id: " << id << std::endl;
    std::cout << "--------------------------ThreadType----------------------------" << std::endl;
    ThreadType();
    std::cout << "--------------------------thread_pthread----------------------------" << std::endl;
    thread_pthread();
    std::cout << "--------------------------thread_ref----------------------------" << std::endl;
    thread_ref();
    std::cout << "--------------------------ConFun----------------------------" << std::endl;
    ConFun();
    std::cout << "--------------------------MemFun----------------------------" << std::endl;
    MemFun();
}