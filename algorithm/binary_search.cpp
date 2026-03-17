#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <vector>
#include <iomanip>

/******************************* 1.binary_search ********************************/

/**
 * template <class ForwardIterator, class T>
 * bool binary_search (ForwardIterator first,
 *                     ForwardIterator last,
 *                     const T& val);
 *
 * template <class ForwardIterator, class T, class Compare>
 * bool binary_search (ForwardIterator first,
 *                     ForwardIterator last,
 *                     const T& val,
 *                     Compare comp);
 * @brief 检测有序范围内元素，是否有与给定值相等的元素。
 *        有序范围内的元素必须按照所给定的比较函数comp相同的排序顺序进行排序。
 * 对于第一个版本：使用operator<进行比较，且当(!(a<b) && !(b<a))时，认为a==b
 * 对于第二个版本：使用comp进行比较，且当(!comp(a,b) && !comp(b,a))时，认为a==b
 * 两个版本的区别在于比较的方式不同，第一个版本使用operator<进行比较，第二个版本使用comp进行比较
 * compare函数返回true表示第一个参数小于第二个参数，返回false表示第一个参数不小于第二个参数。
 */

class SensorData {
 public:
  explicit SensorData(double v) : timestamp_(v), threshold_(0.02) {}
  double timestamp_;
  double threshold_;

  bool operator<(const SensorData& other) const {
    return timestamp_ < other.timestamp_;
  }

  friend std::ostream& operator<<(std::ostream& os, const SensorData& data) {
    os << data.timestamp_;
    return os;
  }

  friend bool operator<(const SensorData& lhs, const double& rhs) {
    return lhs.timestamp_ < rhs;
  }

  friend bool operator<(const double& lhs, const SensorData& rhs) {
    return lhs < rhs.timestamp_;
  }
};

/**
 * @brief   自定义比较函数，比较两个SensorData对象的timestamp_成员变量
 * @note 使用时候发现，compare函数的first并不总是容器中的元素，second也不总是用户传入的值，
 *       而是会根据算法的需要进行调整，因此在比较函数中打印出first和second的值，可以帮助我们理解算法的执行过程。
 */
bool my_compare_less(SensorData first, SensorData second) {
  std::stringstream ss;
  if(first < second) {
    ss << "first: "  << std::fixed << std::setprecision(3) << first << " is smaller than second: " << second << std::endl;
    std::cerr << ss.str() << std::endl;
    return true;
  } else {
    ss << "first: " << std::fixed << std::setprecision(3) << first << " is bigger than second: " << second << std::endl;
    std::cerr << ss.str() << std::endl;
    return false;
  }
}

/**
 * @brief 自定义比较函数，用于比较SensorData对象和double类型的值
 */
struct MyCompare {
  bool operator() (const SensorData& first, const SensorData& second) {
    std::stringstream ss;
    if(first < second) {
      ss << "MyCompareSS first: "  << std::fixed << std::setprecision(3) << first << " is smaller than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return true;
    } else {
      ss << "MyCompareSS first: " << std::fixed << std::setprecision(3) << first << " is bigger than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return false;
    }
  }
  bool operator() (const SensorData& first, const double& second) {
    std::stringstream ss;
    if(first < second) {
      ss << "MyCompareSD first: "  << std::fixed << std::setprecision(3) << first << " is smaller than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return true;
    } else {
      ss << "MyCompareSD first: " << std::fixed << std::setprecision(3) << first << " is bigger than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return false;
    }
  }
  bool operator() (const double& first, const SensorData& second) {
    std::stringstream ss;
    if(first < second) {
      ss << "MyCompareDS first: "  << std::fixed << std::setprecision(3) << first << " is smaller than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return true;
    } else {
      ss << "MyCompareDS first: " << std::fixed << std::setprecision(3) << first << " is bigger than second: " << second << std::endl;
      std::cerr << ss.str() << std::endl;
      return false;
    }
  }
};

void binary_search_example() {
  std::vector<SensorData> data;
  data.push_back(SensorData(1741155871.098));
  data.push_back(SensorData(1741155871.198));
  data.push_back(SensorData(1741155871.298));
  data.push_back(SensorData(1741155871.398));
  data.push_back(SensorData(1741155871.498));
  data.push_back(SensorData(1741155871.598));
  data.push_back(SensorData(1741155871.698));
  data.push_back(SensorData(1741155871.798));
  data.push_back(SensorData(1741155871.898));
  data.push_back(SensorData(1741155871.998));
  data.push_back(SensorData(1741155872.098));
  data.push_back(SensorData(1741155872.198));
  data.push_back(SensorData(1741155872.298));
  data.push_back(SensorData(1741155872.398));
  data.push_back(SensorData(1741155872.498));

  std::stringstream ss;
  // T类型跟迭代器元素类型不一样，使用自定义的比较函数
  double target_timestamp = 1741155871.799;
  bool existed = std::binary_search(data.begin(), data.end(), target_timestamp);
  if(existed) {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp << " existed";
    std::cout << ss.str() << std::endl;
  } else {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp << " not existed";
    std::cout << ss.str() << std::endl;
  }
  ss.str("");

  // T类型跟迭代器元素类型一样，使用自定义的比较函数
  SensorData target_timestamp2(1741155871.799);
  bool existed2 = std::binary_search(data.begin(), data.end(), target_timestamp2, my_compare_less);
  if(existed2) {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp2 << " existed";
    std::cout << ss.str() << std::endl;
  } else {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp2 << " not existed";
    std::cout << ss.str() << std::endl;
  }
  ss.str("");

  // T类型跟迭代器元素类型不一样，使用自定义的比较函数
  double target_timestamp3 = 1741155871.799;
  bool existed3 = std::binary_search(data.begin(), data.end(), target_timestamp3, MyCompare());
  if(existed3) {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp3 << " existed";
    std::cout << ss.str() << std::endl;
  } else {
    ss << "match_time: " << std::fixed << std::setprecision(3) << target_timestamp3 << " not existed";
    std::cout << ss.str() << std::endl;
  }
}

/******************************* 2.upper_bound ********************************/
/**
 * template <class ForwardIterator, class T>
 * ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);
 * 
 * template <class ForwardIterator, class T, class Compare>
 * ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
 * 
 * @brief 在[first, last)范围内查找第一个大于val的元素位置，并返回指向该元素的迭代器。
 *        第一个版本默认使用operator<进行比较，第二个版本使用用户自定义的比较函数comp。
 *        容器中的元素也必须提前按照operator<或comp进行排序，否则结果未定义。
 * @note compare函数第一个参数永远是val，第二个参数永远是容器中的元素，
 *       compare函数的返回值为true时，认为第一个参数小于第二个参数。
 */

void upper_bound_example() {
  std::vector<SensorData> data;
  data.push_back(SensorData(1741155871.098));
  data.push_back(SensorData(1741155871.198));
  data.push_back(SensorData(1741155871.298));
  data.push_back(SensorData(1741155871.398));
  data.push_back(SensorData(1741155871.498));
  data.push_back(SensorData(1741155871.598));
  data.push_back(SensorData(1741155871.698));
  data.push_back(SensorData(1741155871.798));
  data.push_back(SensorData(1741155871.898));
  data.push_back(SensorData(1741155871.998));
  data.push_back(SensorData(1741155872.098));
  data.push_back(SensorData(1741155872.198));
  data.push_back(SensorData(1741155872.298));
  data.push_back(SensorData(1741155872.398));
  data.push_back(SensorData(1741155872.498));

  std::stringstream ss;

  // T类型跟迭代器元素类型不一样，使用自定义的比较函数
  double target_timestamp = 1741155871.798;
  std::vector<SensorData>::iterator up = std::upper_bound(data.begin(), data.end(), target_timestamp);
  if(up != data.end()) {
    ss << "upper_bound at position " << (up - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *up << std::endl;
    std::cout << ss.str() << std::endl;
  } else {
    std::cout << "upper_bound not found" << std::endl;
  }
  ss.str("");
  
  // T类型跟迭代器元素类型不一样，使用自定义的比较函数
  double target_timestamp2 = 1741155871.798;
  std::vector<SensorData>::iterator up2 = std::upper_bound(data.begin(), data.end(), target_timestamp2, MyCompare());
  if(up2 != data.end()) {
    ss << "upper_bound at position " << (up2 - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *up2 << std::endl;
    std::cout << ss.str() << std::endl;
  } else {
    std::cout << "upper_bound not found" << std::endl;
  }
}

/******************************* 3.lower_bound ********************************/
/**
 * template <class ForwardIterator, class T>
 * ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val);
 *
 * template <class ForwardIterator, class T, class Compare>
 * ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
 *
 * @brief 在[first, last)范围内查找第一个不小于val的元素位置(可以跟val相等)，并返回指向该元素的迭代器。
 *        第一个版本默认使用operator<进行比较，第二个版本使用用户自定义的比较函数comp。
 *        容器中的元素也必须提前按照operator<或comp进行排序，否则结果未定义。
 * @note compare函数第一个参数是容器中的元素，第二个参数是val，
 *       compare函数的返回值为true时，认为第一个参数小于第二个参数。
 */
void lower_bound_example() {
  std::vector<SensorData> data;
  data.push_back(SensorData(1741155871.098));
  data.push_back(SensorData(1741155871.198));
  data.push_back(SensorData(1741155871.298));
  data.push_back(SensorData(1741155871.398));
  data.push_back(SensorData(1741155871.498));
  data.push_back(SensorData(1741155871.598));
  data.push_back(SensorData(1741155871.698));
  data.push_back(SensorData(1741155871.798));
  data.push_back(SensorData(1741155871.898));
  data.push_back(SensorData(1741155871.998));
  data.push_back(SensorData(1741155872.098));
  data.push_back(SensorData(1741155872.198));
  data.push_back(SensorData(1741155872.298));
  data.push_back(SensorData(1741155872.398));
  data.push_back(SensorData(1741155872.498));

  std::stringstream ss;
  // T类型跟迭代器元素类型不一样，使用自定义的比较函数
  double target_timestamp = 1741155871.798;
  std::vector<SensorData>::iterator low = std::lower_bound(data.begin(), data.end(), target_timestamp, MyCompare());
  if(low != data.end()) {
    ss << "lower_bound at position " << (low - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *low << std::endl;
    std::cout << ss.str() << std::endl;
  } else {
    std::cout << "lower_bound not found" << std::endl;
  }
}

/******************************* 4.equal_range ********************************/
/**
 * template <class ForwardIterator, class T>
 * std::pair<ForwardIterator, ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);
 *
 * template <class ForwardIterator, class T, class Compare>
 * std::pair<ForwardIterator, ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
 *
 * @brief 在已排序的范围内查找与给定值相等的元素范围
 *        第一个版本默认使用operator<进行比较，第二个版本使用用户自定义的比较函数comp。
 *        容器中的元素也必须提前按照operator<或comp进行排序，否则结果未定义。
 *        通过!comp(a,b) && !comp(b,a)来判断a和b是否相等。
 * @return 如果没有找到相等于val的，则子范围长度为0，且都指向第一个大于val的地址(可以是last当val比所有元素都大)
 *         第一个相当于lower_bound，第二个相当于upper_bound
 * @note compare函数返回true表示第一个参数小于第二个参数，返回false表示第一个参数不小于第二个参数。
 */
void equal_range_example() {
  std::vector<SensorData> data;
  data.push_back(SensorData(1741155871.098));
  data.push_back(SensorData(1741155871.198));
  data.push_back(SensorData(1741155871.298));
  data.push_back(SensorData(1741155871.398));
  data.push_back(SensorData(1741155871.498));
  data.push_back(SensorData(1741155871.598));
  data.push_back(SensorData(1741155871.698));
  data.push_back(SensorData(1741155871.798));
  data.push_back(SensorData(1741155871.898));
  data.push_back(SensorData(1741155871.998));
  data.push_back(SensorData(1741155872.098));
  data.push_back(SensorData(1741155872.198));
  data.push_back(SensorData(1741155872.298));
  data.push_back(SensorData(1741155872.398));
  data.push_back(SensorData(1741155872.498));
  
   std::stringstream ss;
   // T类型跟迭代器元素类型不一样，使用自定义的比较函数
   double target_timestamp = 1741155871.798;
   std::pair<std::vector<SensorData>::iterator, std::vector<SensorData>::iterator> bounds = std::equal_range(data.begin(), data.end(), target_timestamp, MyCompare());
   std::size_t diff = bounds.second - bounds.first;
   if(diff > 0) {
    if(bounds.first != data.end()) {
      ss << "diff > 0 equal_range first at position " << (bounds.first - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds.first << std::endl;
      std::cout << ss.str() << std::endl;
    }
    ss.str("");
    if(bounds.second != data.end()) {
      ss << "diff > 0 equal_range second at position " << (bounds.second - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds.second << std::endl;
      std::cout << ss.str() << std::endl;
    }
   } else {
    if(bounds.first != data.end()) {
      ss << "diff == 0 equal_range not found, first at position " << (bounds.first - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds.first << std::endl;
      std::cout << ss.str() << std::endl;
    } else {
      std::cout << "diff == 0 equal_range not found, first is end" << std::endl;
    }
   }

   // T类型跟迭代器元素类型不一样，使用自定义的比较函数
   double target_timestamp2 = 1741155871.799;
   std::pair<std::vector<SensorData>::iterator, std::vector<SensorData>::iterator> bounds2 = std::equal_range(data.begin(), data.end(), target_timestamp2, MyCompare());
   std::size_t diff2 = bounds2.second - bounds2.first;
   if(diff2 > 0) {
    if(bounds2.first != data.end()) {
      ss << "diff2 > 0 equal_range first at position " << (bounds2.first - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds2.first << std::endl;
      std::cout << ss.str() << std::endl;
    }
    ss.str("");
    if(bounds2.second != data.end()) {
      ss << "diff2 > 0 equal_range second at position " << (bounds2.second - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds2.second << std::endl;
      std::cout << ss.str() << std::endl;
    }
   } else {
    if(bounds2.first != data.end()) {
      ss << "diff2 == 0 equal_range not found, first at position " << (bounds2.first - data.begin()) << ", value is " << std::fixed << std::setprecision(3) << *bounds2.first << std::endl;
      std::cout << ss.str() << std::endl;
    } else {
      std::cout << "diff2 == 0 equal_range not found, first is end" << std::endl;
    }
   }
}

int main() {
  std::cout << "==================== binary search ====================" << std::endl;
  binary_search_example();
  std::cout << "==================== upper bound ====================" << std::endl;
  upper_bound_example();
  std::cout << "==================== lower bound ====================" << std::endl;
  lower_bound_example();
  std::cout << "==================== equal range ====================" << std::endl;
  equal_range_example();
  return 0;
}