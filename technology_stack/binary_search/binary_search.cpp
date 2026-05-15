#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>

/**
 *「二分查找binarysearch」是一种基于分治策略的高效搜索算法。
 * 它利用数据的有序性，每轮缩小一半搜索范围，直至找到目标元素或搜索区间为空为止
 * 例如：判断target是否在数组nums中：
 *   1.计算中间点索引：mid = left + (right - left) / 2
 *   2.比较nums[mid]与target的大小关系：
 *     a.如果nums[mid] == target，说明找到了目标元素，返回mid
 *     b.如果nums[mid] < target，说明目标元素在右半部分，更新left = mid + 1
 *     c.如果nums[mid] > target，说明目标元素在左半部分，更新right = mid - 1
 *   3.重复上述步骤，直到left > right，说明目标元素不存在于数组中，返回-1
 */

/**
 * 区间表示法：
 * 1. 双闭区间(推荐使用这种方式，因为更新边界的方式对称)：
 *    搜索区间为[left, right]，即left和right都包含在搜索范围内
 *    初始化时，left = 0，right = nums.size() - 1
 *    循环条件为while(left <= right)，因为当left == right时，目标索引就是left或者right
 *    更新边界时，left = mid + 1，right = mid - 1
 * 2. 左闭右开区间：
 *    搜索区间为[left, right)，即left包含在搜索范围内，right不包含在搜索范围内
 *    初始化时，left = 0，right = nums.size()
 *    循环条件为while(left < right)，因为当left == right时，搜索区间为空，说明目标元素不存在于数组中
 *    更新边界时，left = mid + 1，right = mid
 */

/**
 * mid的计算方式：
 * 因为left和right的值可能很大，left + right可能会溢出，所以mid的计算方式应该是下述方式之一，而不是mid = (left + right) / 2
 * mid = left + (right - left) / 2，这种方式取靠左边的中位数
 * mid = left + (right - left + 1) / 2，这种方式取靠右边的中位数
 */

/**
 * 二分查找的插入点：
 * 1.对于双闭区间，插入点为left，
 * 因为当循环结束时，left指向第一个大于target的元素，而right指向第一个小于target的元素
 *   
 */

/****************************************************************/

/**
 * @brief Normal binary search
 * 
 * @note 二分查找的循环条件使用left <= right，否则若是left < right，会漏掉元素刚好是left位置或者right位置的情况
 */
void Normal() {
  std::deque<double> data = {
    1.098, 1.198, 1.298, 1.398, 1.498,
    1.598, 1.698, 1.798, 1.898, 1.998,
    2.098, 2.198, 2.298, 2.398, 2.498,
    2.598
  };

  double match_timestamp = 1.000;
  int location = -1;
  int left = 0;
  int right = data.size() - 1;

  while(left <= right) {
    int mid = left + (right - left) / 2;
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
  if(left >=0 && left <= data.size() - 1) {
    std::cout << "data[" << left << "]: " << data[left] << std::endl;
  }
  if(right >= 0 && right <= data.size() - 1) {
    std::cout << "data[" << right << "]: " << data[right] << std::endl;
  }
   
  std::cout << "Location: " << location << std::endl;
}

void Interpolation() {
  std::deque<double> data = {
    1.098, 1.200, 1.298, 1.388, 1.498,
    1.598, 1.698, 1.798, 1.898, 1.998,
    2.098, 2.198, 2.298, 2.398, 2.498
  };

  double match_timestamp = 1.303;
  int left = 0;
  int right = data.size() - 1;

  while(left <= right) {
    int mid = left + (right - left) / 2;
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

  // 假设没有找到对应数据，则mid值在[left-1, left]之间，因为循环的时候left = mid + 1
  // 同理，mid值也在[right, right+1]之间，因为循环的时候right = mid - 1
  double prev = data[left - 1];
  double next = data[left];
  double ratio = (match_timestamp - prev) / (next - prev);
  if(ratio < 0 || ratio > 1) {
    std::cout << "Ratio is invalid: " << ratio << std::endl;
    return;
  }
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