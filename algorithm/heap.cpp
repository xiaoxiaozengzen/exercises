#include <iostream>
#include <algorithm>
#include <vector>

/**
 * 堆的核心价值是：快速拿到当前最大/最小值，同时支持动态插入。
 * 1. 堆只保证堆顶元素是最大/最小的，其他元素满足堆的性质，但不保证完全有序。
 * 2. 全排序代价高，堆只维护部分有序
 * 3. 实际应用：
 *    - 优先队列：需要频繁获取最大/最小元素的场景，如任务调度、事件驱动系统等。
 *    - 堆排序：一种基于堆的数据结构的排序算法，时间复杂度为O(n log n)，空间复杂度为O(1)。
 *    - Top K问题：在大量数据中快速找到前K个最大/最小元素，如排行榜、流式数据处理等。
 */

/**
 * template <class RandomAccessIterator>  
 * void make_heap (RandomAccessIterator first, RandomAccessIterator last);
 *
 * template <class RandomAccessIterator, class Compare> 
 * void make_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp );
 *
 * @note make_heap()函数将范围[first, last)内的元素重新排列成一个堆。
 */
void make_heap_example() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};

    // 对v中的元素进行堆排序，默认是最大堆，即最大的元素排在第一个，剩下元素满足堆的性质(但是不保证完全有序)
    // STL的堆算法把堆顶放在区间的first位置，堆的其他元素放在[first+1, last)的位置上，满足堆的性质
    std::make_heap(v.begin(), v.end());
    std::cout << "Max element: " << v.front() << std::endl; // 输出堆顶元素，即最大元素
    for(const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /**
     * 需要保证[first, last-1)已经是一个堆，才能使用push_heap()函数调整[fiirst, last)范围内的元素，使得它们满足堆的性质。]
     */
    v.push_back(10);
    // 重新调整堆，使得新元素10也满足堆的性质
    std::push_heap(v.begin(), v.end());
    std::cout << "Max element after push_heap: " << v.front() << std::endl; // 输出新的堆顶元素，即最大元素
    for(const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /**
     * 需要保证[first, last)已经是一个堆，会将堆顶元素放到区间的last-1位置上，并调整[first, last-1)范围内的元素，使得它们满足堆的性质。
     * 注意：pop_heap()函数并不会真正删除堆顶元素，而是将其移动到区间的last-1位置上，用户需要手动调用容器的pop_back()函数来删除这个元素。
     */
    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    std::cout << "Max element after pop_heap: " << v.front() << std::endl; // 输出新的堆顶元素，即次大元素
    for(const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    bool ret = std::is_heap(v.begin(), v.end());
    std::cout << "Is v a heap before sort_heap? " << (ret ? "Yes" : "No") << std::endl;

    /**
     * 需要保证[first, last)已经是一个堆，sort_heap操作后就不再是一个堆了，而是一个有序的范围，默认是升序排列，即最小元素排在第一个。
     */
    std::sort_heap(v.begin(), v.end());
    ret = std::is_heap(v.begin(), v.end());
    std::cout << "Is v a heap after sort_heap? " << (ret ? "Yes" : "No") << std::endl;
    std::cout << "sort heap and front element: " << v.front() << std::endl; // 输出排序后的第一个元素，即最小元素
    for(const auto& num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=============== make_heap_example ===============" << std::endl;
    make_heap_example();

    return 0;
}