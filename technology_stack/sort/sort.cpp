#include <iostream>
#include <vector>

/**
 * @brief 冒泡排序：相邻元素两两比较，将较大元素交换到后面，则经过第一轮比较后，最大的元素会被交换到最后位置，类似冒泡上升
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 * 稳定排序
 */
void bubble_sort(std::vector<int>& arr) {
    // n-1趟排序
    for(int i = 0; i < arr.size() -1; i++) {
        // 每趟比较到未排序部分的最后一个元素
        for(int j = 0; j < arr.size() - 1 - i; j++) {
            if(arr[j] >  arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/**
 * @brief 选择排序：每一轮找到未排序部分最大/最小元素，放到未排序部分的开头/结尾
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 * 不稳定排序
 */
void selection_sort(std::vector<int>& arr) {
    for(int i = 0; i < arr.size() - 1; i++) {
        int max_index = 0;
        for(int j = 0; j < arr.size() - i; j++) {
            if(arr[j] > arr[max_index]) {
                max_index = j;
            }
        }
        std::swap(arr[max_index], arr[arr.size() - 1 - i]);
    }
}

/**
 * @brief 插入排序：保持左侧部分是有序的，每次将右侧第一个元素插入到左侧合适位置
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 * 稳定排序
 */
void insertion_sort(std::vector<int>& arr) {
    // 从第二个元素开始遍历
    for(int i = 1; i < arr.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j] < arr[j-1]) {
                std::swap(arr[j], arr[j-1]);
            }
        }
    }
}

/**
 * @brief 希尔排序：基于插入排序的一种更高效的改进版本。每次排序时，先将数组拆分成若干个序列，一个序列相邻元素的索引像个固定的间隔（gap），对每个序列进行插入排序，逐步缩小间隔，直到间隔为1时，进行最后一次插入排序
 * 时间复杂度：O(nlogn) ~ O(n^2)
 * 空间复杂度：O(1)
 * 不稳定排序
 */
void shell_sort(std::vector<int>& arr) { 
    int gap = arr.size() / 2;
    while(gap > 0) {
        for(int i = 0; i < gap; i++) { 
            for(int j = i + gap; j < arr.size(); j += gap) { // 对每个子序列进行排序
                for(int k = j; k - gap >= 0; k -= gap) { // 插入排序
                    if(arr[k] < arr[k - gap]) {
                        std::swap(arr[k], arr[k - gap]);
                    }
                }
            }

        }
        gap /= 2;
    }
}

/**
 * @brief 归并排序：采用分治法，在排序的过程中，把原来的数组变成左右两个数组，然后分别进行排序，
 *        当左右的子数组排序完毕之后，再合并这两个子数组形成一个新的排序数组。
 *        整个过程递归进行，当只剩下一个元素或者没有元素的时候就直接返回。
 * 时间复杂度：O(nlogn)
 * 空间复杂度：O(n)
 * 稳定排序
 */
void merge_sort(std::vector<int>& arr, int left, int right) {        
}

/**
 * @brief 快速排序：取第一个/最后一个元素作为分界点，把整个数组分成左右两侧，左边的元素小于或者等于分界点，右边的元素大于分界点，然后把分界点移动到中间；
 *        然后对左右子数组递归进行上述操作，直到子数组长度为1或者0时结束。
 * 时间复杂度：O(nlogn) ~ O(n^2)
 * 空间复杂度：O(logn)
 * 不稳定排序
 */
void quick_sort(std::vector<int>& arr, int left, int right) {
    if(left >= right) {
        return;
    }

    // 选取做左边的第一个元素作为分界点
    int lo = left + 1;  // 小于等于分界点元素的最右侧位置
    int hi = right;  // 大于分界点元素的最左侧位置

    while(lo <= hi) {
        // 大于分界点的元素放到右侧
        if(arr[lo] > arr[left]) {
            std::swap(arr[lo], arr[hi]);
            hi--;
        } else {
            lo++;
        }
    }

    // 将分界点放到中间
    lo--;
    std::swap(arr[left], arr[lo]);

    // 递归排序左右子数组
    quick_sort(arr, left, lo-1);
    quick_sort(arr, lo+1, right);
}

// 堆排序
// 计数排序
// 桶排序
// 二叉树排序

int main() {
    std::cout << "======= Bubble Sort =======" << std::endl;
    std::vector<int> data = {64, 34, 25, 34, 125, 22, 11, 90};
    bubble_sort(data);
    for(const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "======= Selection Sort =======" << std::endl;
    std::vector<int> data2 = {64, 34, 25, 34, 125, 22, 11, 90};
    selection_sort(data2);
    for(const auto& num : data2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "======= Insertion Sort =======" << std::endl;
    std::vector<int> data3 = {64, 34, 25, 34, 125, 22, 11, 90};
    insertion_sort(data3);
    for(const auto& num : data3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "======= Shell Sort =======" << std::endl;
    std::vector<int> data4 = {64, 34, 25, 34, 125, 22, 11, 90};
    shell_sort(data4);
    for(const auto& num : data4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "======= Merge Sort =======" << std::endl;
    
    std::cout << "======= Quick Sort =======" << std::endl;
    std::vector<int> data6 = {64, 34, 25, 34, 125, 22, 11, 90};
    quick_sort(data6, 0, data6.size() - 1);
    for(const auto& num : data6) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}