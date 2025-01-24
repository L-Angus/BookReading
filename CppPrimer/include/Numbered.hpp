#ifndef __NUMBERED_HPP__
#define __NUMBERED_HPP__

#include <iostream>

class Numbered {
  friend void f(const Numbered &s);

public:
  Numbered() : m_mysn(++unique) {}
  Numbered(const Numbered &rhs) : m_mysn(++unique) {}

private:
  inline static int unique = 0;
  int m_mysn;
};

void f(const Numbered &s) { std::cout << s.m_mysn << std::endl; }

#endif