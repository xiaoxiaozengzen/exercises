#pragma once

#include <chrono>
#include <deque>

/**
 * @brief 求频率
 *
 */
class Frequency {
 public:
  /**
   * @brief
   * 记录n个数量的t(两帧的时间差值)，当n=50的时候就不在增长(最久的会删除，最新的会添加到末尾)。然后算平均频率
   *
   *
   * @return double
   */
  double update() {
    auto time = std::chrono::steady_clock::now();
    double diff = std::chrono::duration<double>(time - last_).count();
    last_ = time;
    q_.push_back(diff);
    double del = 0;
    if (q_.size() > window_size_) {
      del = q_.front();
      q_.pop_front();
    }
    sum_ = sum_ + diff - del;
    return 1 / sum_ * static_cast<double>(q_.size());
  }

 private:
  size_t window_size_ = 50;
  double sum_ = 0;
  // 存储相邻两针时间差的序列
  std::deque<double> q_;
  std::chrono::steady_clock::time_point last_ = std::chrono::steady_clock::now();
};
