/**
 * Binary search is a fast search algorithm with run-time complexity of O(log n). 
 * This search algorithm works on the principle of divide and conquer. 
 * For this algorithm to work properly, the data collection should be in the sorted form.
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>

/****************************************************************/
// 搜索范围的左右边界，即left = 0还是left = -1，right = nums.lengh-1 还是right = nums.lengh；
// 搜索停止（循环结束）的条件，即while(left < right)与while(left <= right)的选择问题；
// 搜索时中间值能否加入左/右边界，即right = mid 还是right = mid-1，left = mid还是left = mid+1；
// mid怎么计算，即mid = left + (right - left) / 2还是mid = left + (right - left + 1) / 2；

// 搜索边界问题：
// 1.搜索大于target的第一个元素位置：
//   当target比所有元素都大时，[0, nums.size()-1]找不到对应元素，有边界必须扩大，即right = nums.size()；
//   而左边界不需要扩大，因为target比所有元素都小时，目标索引就是0
//   则搜索区间改成[0, nums.size()]

// 2.搜索小于target的最后一个元素位置：
//   当target比所有元素都小时，[0, nums.size()-1]找不到对应元素，左边界必须扩大，即令left=-1；
//   而右边界不需要扩大，因为target比所有元素都大时，目标索引就是nums.size()-1
//   则搜索区间改成[-1, nums.size()-1]

// 3.一般用于搜索区间是否含有target
//   target可能在数组中，也可能不在数组中，所以搜索区间为[0, nums.size()-1]，不需要扩大边界
//   target不在数组中时，循环结束，直接返回-1

// 注意：如果我们应根据题目要求选择是否扩充边界，如果扩充了，那么循环截止条件一定是while(left < right)
// 循环结束条件问题：
// 1.搜索区间[left, right]中一定存在target索引值时，循环结束条件为left < right。
//    因为当left == right时，目标索引就是left或者right，适用于上述的第1和第2种情况
//    甚至当情况三的搜索区间扩充为[-1, nums.size()]时，也适用

// 2.搜索区间[left, right]中可能存在target索引值时，循环结束条件为left <= right。

// 中间值归属问题：
// 1.对应边界问题1，当搜索的是大于6的最小值索引，如果num[mid] <= 6,则mid一定不是目标索引，此时left = mid + 1
//   如果num[mid] > 6,则mid可能是目标索引，此时right = mid

// 2.对应边界问题2，当搜索的是小于6的最大值索引，如果num[mid] >= 6,则mid一定不是目标索引，此时right = mid - 1
//   如果num[mid] < 6,则mid可能是目标索引，此时left = mid

// 3.对应边界问题3，当搜索的是是否存在6，如果num[mid] < 6,则mid一定不是目标索引，此时left = mid + 1
//   如果num[mid] > 6,则mid一定不是目标索引，此时right = mid - 1

// mid的计算方式问题：
// mid = left + (right - left) / 2，这种方式取靠左边的中位数
// mid = left + (right - left + 1) / 2，这种方式取靠右边的中位数

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
    //这个mid的位置是偏左的，当数组长度为奇数时候，mid为正中间，当数组长度为偶数时候，mid是靠近左边 
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

  // 循环退出的时:
  //  left值的含义是第一个大于match_timestamp的元素位置,或者数组的末尾(如果match_timestamp大于数组中的所有元素)
  //  right值的含义是最后一个小于match_timestamp的元素位置,或者-1(如果match_timestamp小于数组中的所有元素)

  // 1.match_timestamp=1.998,在数组中存在
  // left: 8, right: 10
  // data[8]: 1.898
  // data[10]: 2.098
  // Location: 9

  // 2.match_timestamp=1.999,不在数组中,但是在数组最大最小值范围内,则mid理论值在[left, right]之间
  // left: 10, right: 9
  // data[10]: 2.098
  // data[9]: 1.998
  // Location: -1

  // 3.match_timestamp=2.999,不在数组中，且大于数组最大值.则left此时为数组末尾,即data.size(),right此时为data.size() - 1
  // left: 16, right: 15
  // data[15]: 2.598
  // Location: -1

  // 4.match_timestamp=1.000,不在数组中，且小于最小值,则right此时为-1, left此时为0
  // left: 0, right: -1
  // data[0]: 1.098
  // Location: -1


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