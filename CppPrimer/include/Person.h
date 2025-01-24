#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

#include "Charpter7.hpp"

class Person {
  friend std::istream &read(std::istream &is, Person &person);
  friend std::ostream &print(std::ostream &os, const Person &person);

public:
  Person(const std::string &name, const std::string &address)
      : Name(name), Address(address) {}
  std::string GetName() const { return Name; }
  std::string GetAddress() const { return Address; }

private:
  std::string Name{};
  std::string Address{};
  Sales_data sd;
};

std::istream &read(std::istream &is, Person &person) {
  is >> person.Name >> person.Address;
  return is;
}

std::ostream &print(std::ostream &os, const Person &person) {
  os << person.Name << " " << person.Address << "\n";
  return os;
}

#endif // PERSON_H