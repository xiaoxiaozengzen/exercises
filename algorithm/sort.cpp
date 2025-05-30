// template <class RandomAccessIterator>
// void sort (RandomAccessIterator first, RandomAccessIterator last);

// template <class RandomAccessIterator, class Compare>
// void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);

#include <iostream>
#include <algorithm>
#include <vector>

bool myfunction (int i,int j) { return (i>j); }

struct myclass {
  bool operator() (int i,int j) { return (i>j);}
} myobject;

int main() {
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

  // using default comparison (operator <):
  std::sort(myvector.begin(), myvector.end());
  std::cout << "myvector contains: ";
  for(auto i : myvector) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  // using object as comp
  std::sort(myvector.begin(), myvector.end(), myobject);
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;  
}
