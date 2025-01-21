#include <iostream>

// C++中的friend关键字其实做这样的事情：在一个类中指明其他的类（或者）函数能够直接访问该类中的private和protected成员。
// friend在类中的声明可以再public、protected和private的如何一个控制域中，而不影响其效果

// 前置声明中，类Node中只能声明AnotherNode指针和引用，不能声明对象，因为对象的大小是未知的
// 函数Print(Node* node)不能载类中定义。若在类中定义，则需要让编译器事先知道AnotherNode的大小

class BinaryTree;
class AnotherNode;

class Node {
  friend class BinaryTree;
  friend void Print(Node* node);
public:
  Node() {std::cout << "Node construct" << std::endl;}
  Node(int value) : value(value) {std::cout << "Node another construct" << std::endl;}
  ~Node() {std::cout << "Node deconstruct" << std::endl;}

  void Print(AnotherNode* node);

private:
  int value = 1;
};

void Print(Node* node) {
  std::cout << __FUNCTION__ << ":" << __LINE__ << ":" << "node->value: " << node->value << std::endl;
}

class BinaryTree {
public:
  BinaryTree() {std::cout << "BinaryTree construct" << std::endl;}
  ~BinaryTree() {std::cout << "BinaryTree deconstruct" << std::endl;}
  void Set(Node* node) {
    root = node;
  }
  void Print() {
    std::cout << "root->value: " << root->value << std::endl;
  }
  void Print(Node* node) {
    std::cout << "node->value: " << node->value << std::endl;
  }
private:
  Node* root = nullptr;
};

class AnotherNode {
  friend class Node;
public:
  AnotherNode() {std::cout << "AnotherNode construct" << std::endl;}
  AnotherNode(int value) : value(value) {std::cout << "AnotherNode another construct" << std::endl;}
  ~AnotherNode() {std::cout << "AnotherNode deconstruct" << std::endl;}

private:
  int value = 1;
};

void Node::Print(AnotherNode* node) {
  std::cout << "node->value: " << node->value << std::endl;
}

int main() {
  Node node;
  BinaryTree tree;
  tree.Set(&node);
  tree.Print();

  Node node1(2);
  tree.Print(&node1);

  AnotherNode another_node;
  node.Print(&another_node);

  Print(&node);
  return 0;
}