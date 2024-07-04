#include <future>
#include <iostream>
#include <memory>
#include <exception>

void promise_base() {
    std::promise<int> p1;
    std::promise<int> p2 = std::promise<int>(std::allocator_arg,std::allocator<int>());
    std::promise<int> p3;

    std::future<int> f1 = p1.get_future();
    std::future<int> f2 = p2.get_future();
    std::future<int> f3 = p3.get_future();

    // swap
    p1.swap(p3);

    // 直接抛出异常 std::future_error
    // std::future<int> f2 = p1.get_future();

    std::thread t([](std::future<int>& value) {
        int ret = value.get();
        std::cout << "promise_base ret: " << ret << std::endl;
    }, std::ref(f1));

    std::thread t2([](std::future<int>& value) {
        try {
            int ret = value.get();
            std::cout << "promise_base_2 ret: " << ret << std::endl;
        } catch (std::exception& ex) {
            std::cout << "Get exception: " << ex.what()<< std::endl;
        }

    }, std::ref(f2));

    std::thread t3([](std::future<int>& value) {
        int ret = value.get();
        std::cout << "promise_base_3 ret: " << ret << std::endl;
    }, std::ref(f3));

    p1.set_value(10);
    try {
        throw std::runtime_error("hahahaha");
    } catch (std::exception& ex) {
        p2.set_exception(std::current_exception());
    }

    std::thread t4([&](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        p3.set_value_at_thread_exit(12);
    });

    if(t.joinable()) {
        t.join();
    }
    if(t2.joinable()) {
        t2.join();
    }
    if(t3.joinable()) {
        t3.join();
    }
    if(t4.joinable()) {
        t4.join();
    }
}

int main() {
    promise_base();
}