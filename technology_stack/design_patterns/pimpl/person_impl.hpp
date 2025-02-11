#pragma once

#include <iostream>
#include <cstring>

// PersonImpl.cpp source code file includes the nested class
// Nested class definition supports implementation
class PersonImpl
{
private:
  char *firstName, *lastName, *title;
  char middleInitial;
public:
  PersonImpl();// default constructor
  PersonImpl(const char *, const char *, char, const char *);
  PersonImpl(const PersonImpl &);
  PersonImpl& operator=(const PersonImpl &);
  virtual ~PersonImpl();
  
  const char *GetFirstName() const { return firstName; }
  const char *GetLastName() const { return lastName; }
  const char *GetTitle() const { return title; }
  char GetMiddleInitial() const { return middleInitial; }
  void ModifyTitle(const char *);
  virtual void Print() const;
  virtual void IsA() { std::cout << "Person" << std::endl; }
  virtual void Greeting(const char *msg) { std::cout << msg << std::endl; } 
};