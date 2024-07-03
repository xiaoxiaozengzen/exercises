#include <thread>
#include <iostream>
#include <iostream>

void thread_base() {
    std::thread t([](){
        std::cout << "current t thread id: " << std::this_thread::get_id() << std::endl;
    });
    std::thread t_disable;
    std::thread t_swap([](){
        std::cout << "current swap thread id: " << std::this_thread::get_id() << std::endl;
    });

    // begin
    std::cout << "=============begin===============" << std::endl;
    if(t.joinable()) {
        std::cout << "t is joinable" << std::endl;
    } else {
        std::cout << "t is not joinable" << std::endl;
    }

    if(t_disable.joinable()){
        std::cout << "t_disable is joinable" << std::endl;
    } else {
        std::cout << "t_disable is not joinable" << std::endl;
    }

    if(t_swap.joinable()) {
        std::cout << "t_swap is joinable" << std::endl;
    } else {
        std::cout << "t_swap is not joinable" << std::endl;
    }

    std::thread::id id = t.get_id();
    std::cout << "thread id: " << id << std::endl;

    std::thread::native_handle_type handle = t.native_handle();

    std::thread::id id_disable = std::this_thread::get_id();
    std::cout << "thread id_disable: " << id_disable << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    t_disable = std::move(t);

    // move
    std::cout << "=============move===============" << std::endl;
    if(t.joinable()) {
        std::cout << "t is joinable" << std::endl;
    } else {
        std::cout << "t is not joinable" << std::endl;
    }

    if(t_disable.joinable()){
        std::cout << "t_disable is joinable" << std::endl;
    } else {
        std::cout << "t_disable is not joinable" << std::endl;
    }

    if(t_swap.joinable()) {
        std::cout << "t_swap is joinable" << std::endl;
    } else {
        std::cout << "t_swap is not joinable" << std::endl;
    }

    t.swap(t_swap);
    // swap
    std::cout << "=============swap===============" << std::endl;
    if(t.joinable()) {
        std::cout << "t is joinable" << std::endl;
    } else {
        std::cout << "t is not joinable" << std::endl;
    }

    if(t_disable.joinable()){
        std::cout << "t_disable is joinable" << std::endl;
    } else {
        std::cout << "t_disable is not joinable" << std::endl;
    }

    if(t_swap.joinable()) {
        std::cout << "t_swap is joinable" << std::endl;
    } else {
        std::cout << "t_swap is not joinable" << std::endl;
    }


    if(t.joinable()) {
        std::cout << "t is joinable" << std::endl;
        t.join();
    } else {
        std::cout << "t is not joinable" << std::endl;
    }

    if(t_disable.joinable()){
        std::cout << "t_disable is joinable" << std::endl;
        t_disable.join();
    } else {
        std::cout << "t_disable is not joinable" << std::endl;
    }

    if(t_swap.joinable()) {
        std::cout << "t_swap is joinable" << std::endl;
        t_swap.join();
    } else {
        std::cout << "t_swap is not joinable" << std::endl;
    }

    auto ret = std::thread::hardware_concurrency();
    std::cout << "hardware_concurrency: " << ret << std::endl;
}

void this_thread_test() {
    std::thread t([](){
        std::cout << "this_thread_test thread id: " << std::this_thread::get_id() << std::endl;
        std::cout << "this_thread_test sleep 1s" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "this_thread_test sleep 5s" << std::endl;
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        now = now + std::chrono::seconds(5);
        std::this_thread::sleep_until(now);
    });

    bool ready = false;
    std::thread t_yield([&](){
        while(!ready) {
            std::this_thread::yield();
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::cout << "this_thread_test call yield" << std::endl;
    ready = true;

    if(t.joinable()) {
        t.join();
    }

    if(t_yield.joinable()) {
        t_yield.join();
    }
}

void thread_pthread() {
    std::thread t([](){
        while(1) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    pthread_t t_id = t.native_handle();
    pthread_setname_np(t_id, "nihao");

    if(t.joinable()) {
        t.join();
    }
}

int main() {
    thread_base();
    this_thread_test();
    thread_pthread();
}