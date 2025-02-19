#include <iostream>
#include <fstream>

void Inherit_ostream() {
    std::ofstream ofs = std::ofstream("/mnt/workspace/cgz_workspace/Exercise/exercises/io/test4.txt", std::ios::out | std::ios::trunc);
    ofs << true;
    ofs << 2;
    ofs << 1.123456789;
    ofs << "hello";

    ofs.put('1');
    char arr[] = "world";
    ofs.write(arr, 5);

    ofs.flush();

}

int main() {
  std::cout << "========Inherit_ostream========" << std::endl;
  Inherit_ostream();
}