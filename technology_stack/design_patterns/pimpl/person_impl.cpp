#include "person_impl.hpp"

PersonImpl::PersonImpl()
{
    firstName = lastName = title = 0;  // NULL pointer
    middleInitial = '\0';
}
PersonImpl::PersonImpl(const char *fn, const char *ln, char mi, const char *t)
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    // Continue memory allocation, init. for data members
}
PersonImpl::PersonImpl(const PersonImpl &pers)
{
    firstName = new char [strlen(pers.firstName) + 1];
    strcpy(firstName, pers.firstName);
    // Continue memory allocation and deep copy for all
}   // pointer data members and copy for non-ptr data members
PersonImpl &PersonImpl::operator=(const PersonImpl &p)
{  // check for self-assignment, then delete destination
   // object data members. Then reallocate and copy from 
   // source object. 
   return *this;  // allow for cascaded assignments
}
PersonImpl::~PersonImpl()
{   // Delete all dynamically allocated data members
}
void PersonImpl::ModifyTitle(const char *newTitle)
{   // Delete old title, reallocate space for and copy new one
}
void PersonImpl::Print() const
{   // Print each data member as usual
  std::cout << "first name: " << firstName << std::endl;
  std::cout << "last name: " << lastName << std::endl;
  std::cout << "title: " << title << std::endl;
}