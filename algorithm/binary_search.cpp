/**
 * template <class ForwardIterator, class T>
 * bool binary_search (ForwardIterator first,
 *                     ForwardIterator last,
 *                     const T& val);
 */

/**
 * template <class ForwardIterator, class T, class Compare>
 * bool binary_search (ForwardIterator first,
 *                     ForwardIterator last,
 *                     const T& val,
 *                     Compare comp);
 */


/**
 * 对于第一个版本：使用operator<进行比较，且当(!(a<b) && !(b<a))时，认为a==b
 * 对于第二个版本：使用comp进行比较，且当(!comp(a,b) && !comp(b,a))时，认为a==b
 * 两个版本的区别在于比较的方式不同，第一个版本使用operator<进行比较，第二个版本使用comp进行比较
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>
#include <sstream>

void Version1() {
  std::deque<double> data = {
    1741155871.098, 1741155871.198, 1741155871.298, 1741155871.398, 1741155871.498,
    1741155871.598, 1741155871.698, 1741155871.798, 1741155871.898, 1741155871.998,
    1741155872.098, 1741155872.198, 1741155872.298, 1741155872.398, 1741155872.498
  };

  double match_timestamp = 1741155871.256;

  bool existed = std::binary_search(data.begin(), data.end(), match_timestamp);
  if(existed) {
    std::cout << "match_time: " << match_timestamp << " existed" << std::endl;
  } else {
    std::cout << "match_time: " << match_timestamp << " not existed" << std::endl;
  }

  // 队列的长度为1也可以
  std::deque<std::uint32_t> data2 = {10};
  bool existed2 = std::binary_search(std::begin(data2), std::end(data2), 10);
  if(existed2) {
    std::cout << "macth value: " << std::endl;
  } else {
    std::cout << "match value failed!" << std::endl;
  }
}

bool com(double first, double second) {
  std::stringstream ss;
  if(std::fabs(first - second) > 0.02) {
    ss << "first: " << first << " - " << " second: " << second << " is bigger 0.02" << std::endl;
    std::cerr << ss.str() << std::endl;
    return true;
  } else {
    ss << "first: " << first << " - " << " second: " << second << " is smaller 0.02" << std::endl;
    std::cerr << ss.str() << std::endl;
    return false;
  }
}

void Version2() {
  std::deque<double> data = {
    1.098, 1.198, 1.298, 1.398, 1.498,
    1.598, 1.698, 1.798, 1.898, 1.998,
    2.098, 2.198, 2.298, 2.398, 2.498
  };

  double match_timestamp = 1.288;
  std::cout << "diff: " << std::fabs(1.298 - match_timestamp) << std::endl;

  bool existed = std::binary_search(data.begin(), data.end(), match_timestamp, com);
  if(existed) {
    std::cout << "match_time: " << match_timestamp << " existed" << std::endl;
  } else {
    std::cout << "match_time: " << match_timestamp << " not existed" << std::endl;
  }
}

int main() {
  std::cout << "====================Version1====================" << std::endl;
  Version1();
  std::cout << "====================Version2====================" << std::endl;
  Version2();
  return 0;
}