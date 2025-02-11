#pragma once

#include <iostream>

#include "person_impl.hpp"

// class PersonImpl; // forward declaration of nested class

class Person {
 private:
  PersonImpl *pImpl; // pointer to implementation of class
protected:
  void ModifyTitle(const char *);
public:
  Person(); // default constructor
  Person(const char *, const char *, char, const char *);
  Person(const Person &); // copy constructor
  virtual ~Person();  // virtual destructor
  const char *GetFirstName() const; // no longer inline
  const char *GetLastName() const; 
  const char *GetTitle() const; 
  char GetMiddleInitial() const; 
  virtual void Print() const;
  virtual void IsA();
  virtual void Greeting(const char *);
  Person &operator=(const Person &);  // overloaded =
};