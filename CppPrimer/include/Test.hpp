#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <iostream>
#include <memory>
#include <vector>

#include "SmartPointer.hpp"
#include "shared_ptr.hpp"

namespace TEST {
std::vector<int> *getVector() {
  return new (std::nothrow) std::vector<int>{1, 2, 3, 4, 5};
}
std::shared_ptr<std::vector<int>> getVector2() {
  std::shared_ptr<std::vector<int>> ptr = std::make_shared<std::vector<int>>();
  *ptr = {1, 2, 3, 4, 5};
  return ptr;
}

std::shared_ptr<std::vector<int>> readAndInsertVector() {
  auto v = getVector2();
  if (v) {
    int a;
    std::cin >> a;
    v->push_back(a);
  }
  return v;
}

void printVector() {
  auto v = readAndInsertVector();
  if (v) {
    for (auto i : *v) {
      std::cout << i << std::endl;
    }
  }
}

void process(CppPrimer::shared_ptr<int> p) {
  std::cout << p.use_count() << std::endl;
}

}; // namespace TEST

struct destination {};
struct connection {};

connection connect(destination *p) {
  std::cout << "-->> start connection <<--" << std::endl;
  return connection();
}
void disconnect(connection c) {
  std::cout << "-->> disconnect connection <<-- " << std::endl;
}
void f(destination &d) {
  connection c = connect(&d);
  std::cout << "-->> manage but not disconnect connection <<--" << std::endl;
}

void end_connection(connection *p) { disconnect(*p); }
void f1(destination &d) {
  connection c = connect(&d);
  shared_ptr<connection> p(&c, end_connection);
}

void Test_Shared_Ptr_Deleter() {
  destination d;
  f(d);
  f1(d);
}

#endif