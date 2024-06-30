#include <iostream>

class person{
private:
    int age;
public:
    person(int a)
    {
       this->age=a;
    }
   inline bool operator == (const person &ps) const;
};

inline bool person::operator==(const person &ps) const
{
 
     if (this->age==ps.age)
        return true;
     return false;
}


int main()
{
    person p1(10);
    person p2(20);
    if(p1==p2) {
        std::cout << "the age is equal!" << std::endl;
    }

}
