#include <iostream>

/**
 * C++中的friend关键字其实做这样的事情：
 *   - 在一个类中指明其他的类（或者）函数能够直接访问该类中的private和protected成员。
 *   - friend在类中的声明可以再public、protected和private的如何一个控制域中，而不影响其效果
 *     即都可以像普通函数一样调用，且都可以访问类的private成员变量
 */

class Node {
  friend class BinaryTree;

  // 正常情况下，friend函数在类中声明，类外定义
  friend void Print(Node* node);
public:
  Node() {std::cout << "Node construct" << std::endl;}
  Node(int value) : value(value) {std::cout << "Node another construct" << std::endl;}
  ~Node() {std::cout << "Node deconstruct" << std::endl;}

  /**
   * friend函数不是成员函数，不能访问this指针，因此不能直接访问成员变量，但可以通过参数访问成员变量
   * 这种做法相当于在类外定义了普通函数，然后inline到类中
   */
  friend void PrintPublic(Node* node) {
    std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
  }

#if 0
  /**
   * 编译报错： error: invalid use of ‘this’ in non-member function
   */
  friend void Print() {
    std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << this->value << std::endl;
  }
#endif

private:
  friend void PrintPrivate(Node* node) {
    std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
  }

private:
  int value = 1;
};

// 正常情况下，friend函数在类中声明，类外定义
void Print(Node* node) {
  std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
}

#if 0
/**
 * 编译报错： error: redefinition of ‘void PrintPublic(Node*)’
 */
void PrintPublic(Node* node) {
  std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
}
#endif

// 友元类BinaryTree可以访问Node的private成员变量value
class BinaryTree {
public:
  BinaryTree() {std::cout << "BinaryTree construct" << std::endl;}
  ~BinaryTree() {std::cout << "BinaryTree deconstruct" << std::endl;}
  void Set(Node* node) {
    root = node;
  }
  void Print() {
    std::cout <<  __FUNCTION__ << ":" << __LINE__ << ":" << "root->value: " << root->value << std::endl;
  }
  void Print(Node* node) {
    std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
  }
private:
  Node* root = nullptr;
};

int main() {
  Node node;
  BinaryTree tree;
  tree.Set(&node);
  tree.Print();

  Node node1(2);
  tree.Print(&node1);

  Print(&node);
  PrintPublic(&node);
  PrintPrivate(&node);

  return 0;
}