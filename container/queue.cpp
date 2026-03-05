#include <iostream>
#include <queue>
#include <deque>
#include <list>
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

 private:
  int a = 0;
};

/**
 * template <class T, class Container = deque<T> > class queue;
 * @brief queue是一种专门用于FIFO场景设计的容器适配器，即基于底层容器（默认为deque）实现的先进先出数据结构。
 *        queue只允许在一端插入元素（称为队尾），在另一端删除元素（称为队头）。
 * @note 底层容器需要支持以下操作：
 *       - empty(): 判断容器是否为空
 *       - size(): 返回容器中元素的数量
 *       - front(): 访问队头元素
 *       - back(): 访问队尾元素
 *       - push_back(): 在队尾插入元素
 *       - pop_front(): 删除队头元素
 */

void member_type() {
    if(std::is_same<std::queue<A>::value_type, A>::value) {
        std::cout << "value_type is A" << std::endl;
    }
    if(std::is_same<std::queue<A>::container_type, std::deque<A>>::value) {
        std::cout << "container_type is deque<A>" << std::endl;
    }
    if(std::is_same<std::queue<A>::reference, A&>::value) {
        std::cout << "reference is A&" << std::endl;
    }
    if(std::is_same<std::queue<A>::const_reference, const A&>::value) {
        std::cout << "const_reference is const A&" << std::endl;
    }
    if(std::is_same<std::queue<A>::size_type, std::size_t>::value) {
        std::cout << "size_type is size_t" << std::endl;
    }
}

void construct_test() {
    std::deque<A> deq{A(1), A(2), A(3)};
    std::list<A> lst{A(4), A(5), A(6)};

    std::queue<A> q0;
    std::queue<A> q1(deq);
    std::queue<A> q2(std::move(deq));
    std::queue<A, std::list<A>> q3;
    std::queue<A, std::list<A>> q4(lst);

    std::cout << "q0 size: " << q0.size() << std::endl;
    std::cout << "q1 size: " << q1.size() << std::endl;
    std::cout << "q2 size: " << q2.size() << std::endl;
    std::cout << "q3 size: " << q3.size() << std::endl;
    std::cout << "q4 size: " << q4.size() << std::endl;
}

void member_function_test() {
    std::queue<A> q;
    std::cout << "empty: " << (q.empty()? "true" : "false") << std::endl;
    std::size_t size = q.size();
    std::cout << "size: " << size << std::endl;

    A a1(4);
    q.push(A(1));
    q.push(A(2));
    q.push(A(3));
    q.push(std::move(a1));

    A a2 = q.front();
    std::cout << "front: " << a2 << std::endl;
    q.front() = A(10); // 修改队头元素
    std::cout << "front after modification: " << q.front() << std::endl;
    A a3 = q.back();
    std::cout << "back: " << a3 << std::endl;
    q.back() = A(20); // 修改队尾元素
    std::cout << "back after modification: " << q.back() << std::endl;
    
    q.emplace(30); // 直接在队尾构造元素
    std::cout << "back after emplace: " << q.back() << std::endl;

    q.pop(); // 删除队头元素
    std::cout << "front after pop: " << q.front() << std::endl;
}

int main() {
  std::cout << "=============== member type ===============" << std::endl;
  member_type();
  std::cout << "=============== construct test ===============" << std::endl;
  construct_test();
  std::cout << "=============== member function test ===============" << std::endl;
  member_function_test();

  std::cout << "=============== end ===============" << std::endl;
  return 0;
}