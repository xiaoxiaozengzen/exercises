#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "utility/rate.hpp"

int main() {
    Rate rate(10.0); // 10 Hz
    for (int i = 0; i < 5; ++i) {
        rate.sleep();
        std::chrono::seconds now_s = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());
        std::chrono::nanoseconds now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch());
        std::stringstream ss;
        ss << "[" << now_s.count() << "s " << std::setfill('0') << std::setw(9) << (now_ns.count() % 1000000000) << "ns]";

        std::cout << ss.str() << "Tick " << i + 1 << std::endl;
    }

    return 0;
}