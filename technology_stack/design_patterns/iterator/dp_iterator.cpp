/**
 * Iterator Design Pattern
 *
 * Intent: Lets you traverse elements of a collection without exposing its
 * underlying representation (list, stack, tree, etc.).
 */

#include <iostream>
#include <string>
#include <vector>

template <typename T, typename std::size_t N>
class MyContainer {
private:
  T data[N];
  std::size_t capacity = N;
  std::size_t size = 0;

public:
  void Inset(const T& item, std::size_t index) {
    if (index < capacity) {
      data[index] = item;
    } else {
      std::cout << "Container is full!" << std::endl;
    }
  }

  class Iterator {
    MyContainer* container = nullptr;
    size_t index = 0;

   public:
    Iterator(MyContainer* c) : container(c) {}

    T& operator*() { return container->data[index]; }

    Iterator& operator++() {
      ++index;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++index;
      return temp;
    }

    Iterator& operator--() {
      --index;
      return *this;
    }

  };

  Iterator begin() { return Iterator(this); }
  Iterator end() {
    Iterator it = Iterator(this);
    it.index = size;
    return it;
  }
};
 
int main() {

  MyContainer<std::string, 5> container;
  container.Inset("Hello", 0);
  container.Inset("World", 1);
  container.Inset("!", 2);
  container.Inset("This", 3);
  container.Inset("is", 4);

  MyContainer<std::string, 5>::Iterator it = container.begin();
  std::string ret = *it;
  std::cout << ret << std::endl;
  it++;
  ret = *it;
  std::cout << ret << std::endl;
  --it;
  ret = *it;
  std::cout << ret << std::endl;
  

  return 0;
}