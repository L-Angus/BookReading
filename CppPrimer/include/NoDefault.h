#ifndef NO_DEFAULT_H_
#define NO_DEFAULT_H_

#include <string>

// class NoDefault {
// public:
//   NoDefault(int i) : m_i(i) {}
//   NoDefault() = delete;
//   int get() const { return m_i; }

// private:
//   int m_i;
// };

// class C {
// public:
//   //   C() = default;
//   //   ~C() = default;

// private:
//   NoDefault m_nd;
// };

// class Test {
// public:
//   Test(int i) : m_i(i) {}

// private:
//   static std::string initRate() { return "test"; }

// private:
//   //   std::string m_s;
//   int m_i;
//   static std::string state;
// };

// std::string Test::state = initRate();
#include <iostream>

class Friend {
public:
  //   Friend() = default;
  Friend(int a = 0, const std::string &b = "") : m_i(a), m_s(b) {}
  void Print(const Friend &fr) {
    std::cout << fr.m_i << "--" << fr.m_s << std::endl;
  }

private:
  int m_i;
  std::string m_s;
};

#endif