#ifndef __FOO_HPP__
#define __FOO_HPP__

#include <iostream>
#include <vector>

class Foo {
public:
  Foo() = default;
  Foo(const Foo &);
  Foo &operator=(const Foo &) &;

  Foo sorted() &&;
  Foo sorted() const &;

private:
  std::vector<int> data;
};

#endif