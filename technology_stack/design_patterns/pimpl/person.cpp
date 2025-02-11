#include "person.hpp"

Person::Person()
  :pImpl(new PersonImpl())
{  // This is the complete member function definition
}
Person::Person(const char *fn, const char *ln, char mi, const char *t)
  :pImpl(new PersonImpl(fn, ln, mi, t))
{  // This is the complete member function definition
}  
Person::Person(const Person &pers):pImpl(new PersonImpl(*(pers.pImpl)))
{  // This is the complete member function definition
}  // No Person data members to copy from pers except deep
   // copy of *(pers.pImpl) to data member pImpl
Person &Person::operator=(const Person &p)
{  // delegate op= to implementation portion
   pImpl->operator=(*(p.pImpl));   // call op= on impl. piece
   return *this;  // allow for cascaded assignments
}
Person::~Person()
{
    delete pImpl;   // delete associated implementation
}
void Person::ModifyTitle(const char *newTitle)
{   // delegate request to the implementation 
    pImpl->ModifyTitle(newTitle);  
}
const char *Person::GetFirstName() const
{   // no longer inline in Person;further hides implementation
    return pImpl->GetFirstName();
}
// Note: methods GetLastName(), GetTitle(), GetMiddleInitial()
// are implemented similar to GetFirstName(). See online code.
void Person::Print() const
{
    pImpl->Print();   // delegate to implementation
}                     // (same named member function)
void Person::IsA()
{
    pImpl->IsA();   // delegate to implementation
}

void Person::Greeting(const char *msg)
{
    pImpl->Greeting(msg);   // delegate to implementation
}
