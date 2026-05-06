#include <iostream>

/**
 * 前置声明中，类Node中只能声明AnotherNode指针和引用，不能声明对象，因为对象的大小是未知的
 *  - 函数Print(Node* node)不能载类中定义。若在类中定义，则需要让编译器事先知道AnotherNode的大小
 */

class AnotherNode;

class Node {
public:
  Node() {std::cout << "Node construct" << std::endl;}
  Node(int value) : value(value) {std::cout << "Node another construct" << std::endl;}
  ~Node() {std::cout << "Node deconstruct" << std::endl;}

  void Print(AnotherNode* node);

#if 0
  /**
   * 编译报错：error: invalid use of incomplete type ‘class AnotherNode’
   */
  void print2(AnotherNode* node) {
    std::cout << "node.value: " << node->value << std::endl;
  }
#endif

private:
  int value = 1;
};

class AnotherNode {
public:
  AnotherNode() {std::cout << "AnotherNode construct" << std::endl;}
  AnotherNode(int value) : value(value) {std::cout << "AnotherNode another construct" << std::endl;}
  ~AnotherNode() {std::cout << "AnotherNode deconstruct" << std::endl;}

public:
  int value = 1;
};

void Node::Print(AnotherNode* node) {
  std::cout << "node->value: " << node->value << std::endl;
}

int main() {
  Node node;
  AnotherNode another_node(10);
  node.Print(&another_node);

  return 0;
}