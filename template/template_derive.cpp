#include <iostream>

template <typename T>
class Base {
 public:
  Base() {
    std::cout << "Base" << std::endl;
  }
  virtual ~Base() {
    std::cout << "~Base" << std::endl;
  }

 public:
  virtual void Print() {
    std::cout << "Base::Print" << std::endl;
  }

  virtual void Print(T t) {
    std::cout << "Base::Print : " << t << std::endl;
  }
};

class Derived : public Base<int> {
 public:
  Derived() {
    std::cout << "Derived" << std::endl;
  }
  virtual ~Derived() {
    std::cout << "~Derived" << std::endl;
  }

 public:
  void Print() override {
    std::cout << "Derived::Print" << std::endl;
  }

  void Print(int t) override {
    std::cout << "Derived::Print : " << t << std::endl;
  }
};

int main() {
  Base<int>* base = new Derived();
  base->Print();
  base->Print(1);
  delete base;
  return 0;
}