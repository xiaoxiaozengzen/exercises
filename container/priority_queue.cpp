#include <iostream>
#include <queue>
#include <vector>
#include <type_traits>

class A {
 public:
  A() { 
    // std::cout << "construct" << std::endl; 
  }

  explicit A(int a) : a(a) { 
    // std::cout << "construct with a" << std::endl; 
  }

  ~A() { 
    // std::cout << "deconstruct" << std::endl; 
  }

  A(const A& other) {
    this->a = other.a;
    // std::cout << "copy construct" << std::endl;
  }

  A& operator=(const A& other) {
    this->a = other.a;
    // std::cout << "copy assignment" << std::endl;
    return *this;
  }

  A(A&& other) {
    this->a = other.a;
    // std::cout << "move construct" << std::endl;
  }

  A& operator=(A&& other) {
    this->a = other.a;
    // std::cout << "move assignment" << std::endl;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const A& a) {
    os << a.a;
    return os;
  }

  bool operator<(const A& other) const {
    return this->a < other.a;
  }

  bool operator>(const A& other) const {
    return this->a > other.a;
  }

 private:
  int a = 0;
};

/**
 * @brief 优先级队列，一种容器适配器，保证第一个元素永远是优先级最高的元素。只有容器back的元素才能popped，即priority_queue的top元素。
 * template <class T, 
 *           class Container = vector<T>, 
 *           class Compare = less<typename Container::value_type> > 
 * class priority_queue
 * @note 底层容器需要支持这些操作：empty(), size(), front(), push_back(), pop_back()，并且可以支持随机迭代器
 *       deque跟vector都满足要求，默认是vector
 * @note Compare是一个二元谓词，用于比较元素的优先级，默认是less，即优先级高的元素会被放在前面（最大堆）
 */

void member_type_test() {
    if(std::is_same<std::priority_queue<A>::value_type, A>::value) {
        std::cout << "value_type is A" << std::endl;
    }
    if(std::is_same<std::priority_queue<A>::container_type, std::vector<A>>::value) {
        std::cout << "container_type is vector<A>" << std::endl;
    }
    if(std::is_same<std::priority_queue<A>::reference, A&>::value) {
        std::cout << "reference is A&" << std::endl;
    }
    if(std::is_same<std::priority_queue<A>::const_reference, const A&>::value) {
        std::cout << "const_reference is const A&" << std::endl;
    }
    if(std::is_same<std::priority_queue<A>::size_type, std::size_t>::value) {
        std::cout << "size_type is size_t" << std::endl;
    }
}

struct my_less {
    bool operator()(const A& a1, const A& a2) const {
        // 反转比较逻辑，使得优先级低的元素被放在前面（最小堆）
        return a1 < a2; // 这里直接使用A的operator<，如果需要更复杂的逻辑可以修改
    }
};

struct my_greater {
    bool operator()(const A& a1, const A& a2) const {
        // 反转比较逻辑，使得优先级高的元素被放在前面（最大堆）
        return a1 > a2; // 这里直接使用A的operator>，如果需要更复杂的逻辑可以修改
    }
};

void construct_test() {
    std::vector<A> vec = {A(3), A(1), A(4), A(1), A(5)};

    std::priority_queue<A> pq_default;
    std::priority_queue<A, std::vector<A>, my_less> pq_custom(my_less(), vec);
    std::priority_queue<A, std::vector<A>> pq1(vec.begin(), vec.end());
    std::priority_queue<A, std::vector<A>, my_greater> pq2(vec.begin(), vec.end(), my_greater());
}

void member_function_test() {
    std::vector<A> vec = {A(3), A(1), A(4), A(1), A(5)};
    std::priority_queue<A, std::vector<A>, my_less> pq(vec.begin(), vec.end(), my_less());
    
    std::cout << "empty: " << (pq.empty()? "true" : "false") << std::endl;
    std::size_t size = pq.size();
    std::cout << "size: " << size << std::endl;
    A top = pq.top();
    std::cout << "top: " << top << std::endl;
    pq.push(A(2));
    pq.emplace(5);
    std::cout << "new top after push/emplace: " << pq.top() << std::endl;
    pq.pop();
    std::cout << "new top after pop: " << pq.top() << std::endl;
}

struct Task {
    int priority;
    int seq;

    bool operator<(const Task& other) const {
        // 优先级高的任务应该排在前面，所以这里使用greater
        return priority < other.priority;
    }
};

/**
 * @brief 优先级队列是不稳定的，即使两个元素优先级相同，后入的元素也不一定排在前面。下面的测试演示了这一点。
 */
void secure_pop_test() {
    std::priority_queue<Task> task_queue;
    task_queue.push({3, 1});
    task_queue.push({1, 2});
    task_queue.push({4, 3});
    task_queue.push({2, 4});
    task_queue.push({4, 5}); // 同优先级，后入的排在前面

    while (!task_queue.empty()) {
        Task t = task_queue.top();
        std::cout << "Processing task with priority: " << t.priority << ", seq: " << t.seq << std::endl;
        task_queue.pop();
    }
}

int main() {
    std::cout << "=================== member type test ==================" << std::endl;
    member_type_test();
    std::cout << "=================== construct test ==================" << std::endl;
    construct_test();
    std::cout << "=================== member function test ==================" << std::endl;
    member_function_test();
    std::cout << "=================== secure pop test ==================" << std::endl;
    secure_pop_test();

    return 0;
}