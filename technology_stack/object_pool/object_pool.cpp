#pragma once

#include <atomic>
#include <bitset>
#include <functional>
#include <memory>
#include <vector>

#include "spin_lock.hpp"

namespace ObjectPool {

template <typename T>
class ObjectPool {
 public:
  using type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using shared_pointer = std::shared_ptr<T>;
  using weak_pointer = std::weak_ptr<T>;
  using deleter_type = std::function<void(pointer)>;
  using cleaner_type = std::function<void(pointer)>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  constexpr static size_type type_size = sizeof(T);
  constexpr static size_type FixedSize = 512;

 protected:
  std::unique_ptr<T[]> buffer_{nullptr};
  size_type capacity_{0};
  deleter_type deleter_;
  cleaner_type cleaner_{nullptr};
  std::bitset<FixedSize> bitmap_;
  devastator::realtime::spinlock sp_;

  size_t find_first() const noexcept {
    size_t index = 0;
    for (; index < capacity_; ++index) {
      if (bitmap_.test(index)) {
        return index;
      }
    }
    return index;
  }

  pointer allocate() noexcept {
    devastator::realtime::spinlock::scoped_lock lock_guard(sp_);
    if (bitmap_.count() == 0) {
      return nullptr;
    }
    auto index = find_first();
    if (index >= capacity_) {
      return nullptr;
    }
    bitmap_.reset(index);
    return buffer_.get() + index;
  }

  void deallocate(pointer p) noexcept {
    devastator::realtime::spinlock::scoped_lock lock_guard(sp_);
    difference_type index = p - buffer_.get();
    if (index < 0 || index >= static_cast<difference_type>(capacity_)) {
      return;
    }
    bitmap_.set(index);
  }

  bool is_from_pool(pointer p) const noexcept {
    return p >= buffer_.get() && p < buffer_.get() + capacity_;
  }

 public:
  ObjectPool() = default;

  explicit ObjectPool(size_type n) { init(n); }

  explicit ObjectPool(size_type n, cleaner_type &&cleaner) : cleaner_(std::move(cleaner)) {
    init(n);
  }

  ObjectPool(const ObjectPool &) = delete;
  ObjectPool &operator=(const ObjectPool &) = delete;

  ObjectPool(ObjectPool &&) = delete;
  ObjectPool &operator=(ObjectPool &&) = delete;

  ~ObjectPool() = default;

  /// @brief  init object pool
  /// @param n  object pool size: really allocated object nums
  /// @note  it should be called before use object pool, and only once
  /// @note exception safe: if failed, object pool will be empty
  void init(size_type n) {
    try {
      buffer_ = std::make_unique<T[]>(n);
    } catch (std::bad_alloc &e) {
      buffer_ = nullptr;
      capacity_ = 0;
      return;
    }

    capacity_ = n;
    bitmap_.reset();

    for (size_type i = 0; i < n; ++i) {
      bitmap_.set(i);
    }
  }

  /// @brief  get object pool available size
  /// @return  available size
  size_type size() noexcept {
    devastator::realtime::spinlock::scoped_lock lock_guard(sp_);
    return bitmap_.count();
  }

  size_type capacity() const noexcept { return capacity_; }

  bool empty() noexcept {
    devastator::realtime::spinlock::scoped_lock lock_guard(sp_);
    return bitmap_.none();
  }

  bool full() noexcept {
    devastator::realtime::spinlock::scoped_lock lock_guard(sp_);
    return bitmap_.count() == capacity_;
  }

  bool regist_deleter(deleter_type &&deleter) noexcept {
    if (deleter_ != nullptr) {
      return false;
    }
    deleter_ = std::move(deleter);
    return true;
  }

  bool regist_cleaner(cleaner_type &&cleaner) noexcept {
    if (cleaner_ != nullptr) {
      return false;
    }
    cleaner_ = std::move(cleaner);
    return true;
  }

  /// @brief try to get a shared pointer from object pool
  /// @return  shared pointer, nullptr if object pool is empty
  /// @note need to check the return value before use it
  [[nodiscard]] shared_pointer get_shared_pointer() {
    auto p = allocate();
    return shared_pointer(p, [this](pointer p) {
      if (p != nullptr) {
        cleaner_(p);
        deallocate(p);
      }
    });
  }

  /// @brief try to get a ctype pointer from object pool
  /// @return ctype pointer, nullptr if object pool is empty
  /// @note need to check the return value before use it

  [[nodiscard]] T *get() noexcept {
    auto p = allocate();
    return p;
  }

  void put(T *p) noexcept {
    cleaner_(p);
    deallocate(p);
  }
};
}  // namespace ObjectPool
