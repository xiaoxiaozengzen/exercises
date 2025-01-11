#pragma once

#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <list>
#include <mutex>

/**
 * @brief 推送策略
 */
enum class PushPolicy {
  blocking,     // 阻塞 直到队列腾出空间
  discard_old,  // 丢弃队列中最老的值
  discard,      // 丢弃当前入的值
};

template <typename T>
class MsgQueue {
 private:
  mutable std::mutex _mutex;
  std::condition_variable _cv_push;
  std::condition_variable _cv_pop;
  const size_t _capacity;  // _data容量
  std::deque<T> _data;
  const PushPolicy _policy;  // 队列满时的push策略
  bool _enable;

 public:
  MsgQueue(size_t capacity = 3, PushPolicy policy = PushPolicy::discard_old)
      : _capacity(capacity == 0 ? 1 : capacity), _policy(policy), _enable(true) {}
  MsgQueue(const MsgQueue &) = delete;
  MsgQueue(MsgQueue &&) = delete;
  MsgQueue &operator=(const MsgQueue &) = delete;
  MsgQueue &operator=(MsgQueue &&) = delete;
  ~MsgQueue() {}

  template <typename TR>
  int push(TR &&data) {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_data.size() >= _capacity) {
      switch (_policy) {
        case PushPolicy::blocking: {
          _cv_push.wait(lock, [this]() { return !(_data.size() >= _capacity && _enable); });
        } break;
        case PushPolicy::discard_old: {
          _data.pop_front();
        } break;
        default:
          return -1;
          break;
      }
    }
    if (!_enable || _data.size() >= _capacity) return -1;
    _data.push_back(std::forward<TR>(data));
    _cv_pop.notify_one();
    return 0;
  }

  template <typename TR>
  int operator<<(TR &&data) {
    return push(std::forward<TR>(data));
  }

  int pop(T &output) {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_data.empty()) {
      _cv_pop.wait(lock, [this]() { return !(_data.empty() && _enable); });
    }
    if (!_enable || _data.empty()) return -1;
    output = _data.front();
    _data.pop_front();
    _cv_push.notify_one();
    return 0;
  }
  
  void enable() {
    std::unique_lock<std::mutex> lock(_mutex);
    _enable = true;
  }
  void disable() {
    std::unique_lock<std::mutex> lock(_mutex);
    _enable = false;
    _data.clear();
    lock.unlock();
    _cv_pop.notify_one();
    _cv_push.notify_one();
  }
  void clear() {
    std::unique_lock<std::mutex> lock(_mutex);
    _data.clear();
  }

  bool empty() {
    std::unique_lock<std::mutex> lock(_mutex);
    return _data.empty();
  }
};