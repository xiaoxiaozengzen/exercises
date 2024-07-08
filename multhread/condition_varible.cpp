// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

void wait_test() {
    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0;
    auto shipment_available = [&]() -> bool {return cargo!=0;};

    auto consume = [&](int n) {
        for (int i=0; i<n; ++i) {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck,shipment_available);
            // consume:
            std::cout << cargo << '\n';
            cargo=0;
        }
    };

    std::thread consumer_thread (consume,10);

    // produce 10 items when needed:
    for (int i=0; i<10; ++i) {
        while (shipment_available()) std::this_thread::yield();
        std::unique_lock<std::mutex> lck(mtx);
        cargo = i+1;
        cv.notify_one();
    }

    consumer_thread.join();
    
}

void wait_until_test() {
    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0;
    auto shipment_available = [&]() -> bool {return cargo!=0;};

    auto consume = [&](int n) {
        std::unique_lock<std::mutex> lck(mtx);
        std::cv_status status = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(1));
        if (status == std::cv_status::timeout) {
            std::cout << "wait_until_test timeout" << std::endl;
        }
        // consume:
        std::cout << cargo << '\n';
    };

    std::thread consumer_thread (consume,10);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::unique_lock<std::mutex> lck(mtx);
    cargo = 2;
    cv.notify_one();

    consumer_thread.join();    
}

/**
while (!pred())
  if ( wait_until(lck,abs_time) == cv_status::timeout)
    return pred();
return true;
*/
void wait_until_pred_test() {
    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0;
    auto shipment_available = [&]() -> bool {return cargo!=0;};

    auto consume = [&](int n) {
        std::unique_lock<std::mutex> lck(mtx);
        bool status = cv.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(2), shipment_available);
        if (!status) {
            std::cout << "wait_until_pred_test fail" << std::endl;
        } else {
            std::cout << "wait_until_pred_test success" << std::endl;
        }
        // consume:
        std::cout << cargo << '\n';
    };

    std::thread consumer_thread (consume,10);

    std::this_thread::sleep_for(std::chrono::seconds(4));
    {
        std::unique_lock<std::mutex> lck(mtx);
        cargo = 2;
        cv.notify_one();
    }


    consumer_thread.join();    
}

void fun_test() {
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    auto print_id = [&] (int id) {
        std::unique_lock<std::mutex> lck(mtx);
        while (!ready) cv.wait(lck);
        // ...
        std::cout << "thread " << id << '\n';
    };

    auto go = [&] () {
        std::unique_lock<std::mutex> lck(mtx);
        std::notify_all_at_thread_exit(cv,std::move(lck));
        ready = true;

        std::this_thread::sleep_for(std::chrono::seconds(3));
    };

    std::thread threads[10];
    // spawn 10 threads:
    for (int i=0; i<10; ++i)
        threads[i] = std::thread(print_id,i);
    std::cout << "10 threads ready to race...\n";

    std::thread(go).detach();   // go!

    for (auto& th : threads) th.join();       
}

int main ()
{
    wait_test();
    std::cout << "==============" << std::endl;
    wait_until_test();
    std::cout << "==============" << std::endl;
    wait_until_pred_test();
    std::cout << "==============" << std::endl;
    fun_test();
    return 0;
}