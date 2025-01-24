#ifndef __EMPLOYEE_HPP__
#define __EMPLOYEE_HPP__

#include <iostream>
#include <string>

class Employee {
  std::string mName;
  inline static int mNo;
  int m_mysn;

public:
  Employee() : mName(""), m_mysn(++mNo) {}
  Employee(const std::string &name) : mName(name), m_mysn(++mNo) {}
  Employee(const Employee &rhs) : mName(rhs.mName), m_mysn(++mNo) {
    std::cout << "Employee::copy constructor" << std::endl;
  }
  Employee &operator=(const Employee &rhs) {
    mName = rhs.mName;
    m_mysn = ++mNo;
    std::cout << "Employee::operator=" << std::endl;
    return *this;
  }

  std::string GetName() const { return mName; }
  int GetSn() const { return m_mysn; }
};

#endif