/**
 * Binary search is a fast search algorithm with run-time complexity of O(log n). 
 * This search algorithm works on the principle of divide and conquer. 
 * For this algorithm to work properly, the data collection should be in the sorted form.
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>

/**
 * @brief Normal binary search
 * 
 * @note 二分查找的循环条件使用left <= right，否则若是left < right，会漏掉元素刚好是left位置或者right位置的情况
 */
void Normal() {
  std::deque<double> data = {
    1741155871.098, 1741155871.198, 1741155871.298, 1741155871.398, 1741155871.498,
    1741155871.598, 1741155871.698, 1741155871.798, 1741155871.898, 1741155871.998,
    1741155872.098, 1741155872.198, 1741155872.298, 1741155872.398, 1741155872.498,
    1741155872.598
  };

  double match_timestamp = 1741155871.998;
  int location = -1;
  std::size_t left = 0;
  std::size_t right = data.size() - 1;

  while(left <= right) {
    std::size_t mid = left + (right - left) / 2;
    if(data[mid] == match_timestamp) {
      location = mid;
      break;
    } else if(data[mid] < match_timestamp) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  std::cout << "left: " << left << ", right: " << right << std::endl;
  std::cout << "Location: " << location << std::endl;
}

void Interpolation() {
  std::deque<double> data = {
    1.098, 1.200, 1.298, 1.388, 1.498,
    1.598, 1.698, 1.798, 1.898, 1.998,
    2.098, 2.198, 2.298, 2.398, 2.498
  };

  double match_timestamp = 1.303;
  std::size_t left = 0;
  std::size_t right = data.size() - 1;

  while(left <= right) {
    std::size_t mid = left + (right - left) / 2;
    if(data[mid] == match_timestamp) {
      left = mid;
      break;
    } else if(data[mid] < match_timestamp) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  if(left == 0) {
    if(std::fabs(data[left] - match_timestamp) < 0.01) {
      std::cout << "Match success, in begin: " << left << std::endl;
    } else {
      std::cout << "Match failed, because interval_right > 0.01" << std::endl;
    }
  } else if (left == data.size()) {
    if(std::fabs(data[left] - match_timestamp) < 0.01) {
      std::cout << "Match success, in end: " << left << std::endl;
    } else {
      std::cout << "Match failed, because interval_left > 0.01" << std::endl;
    }
  } else {
    std::cout << "left - 1 :" << data[left - 1] << ", left: " << data[left] << std::endl;
    std::cout << "right :" << data[right] << ", right + 1: " << data[right + 1] << std::endl;
  }

  double prev = data[left - 1];
  double next = data[left];
  double ratio = (match_timestamp - prev) / (next - prev);
  double result = prev * (1 - ratio) + next * ratio;
  std::cout << "Result: " << result << std::endl;
}

int main() {
  std::cout << "====================Normal====================" << std::endl;
  Normal();
  std::cout << "====================Interpolation====================" << std::endl;
  Interpolation();
  return 0;
}