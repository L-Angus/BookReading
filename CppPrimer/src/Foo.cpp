#include "../include/Foo.h"

#include <iostream>

Foo::Foo(const Foo &rhs) { std::cout << "Copy Constructor" << std::endl; }

Foo &Foo::operator=(const Foo &rhs) & {
  std::cout << "Assignment Operator" << std::endl;
  return *this;
}

Foo Foo::sorted() && {
  std::cout << "Rvalue sorted" << std::endl;
  //   std::sort(data.begin(), data.end());
  Foo ret(*this);
  return ret.sorted();
}

Foo Foo::sorted() const & {
  std::cout << "Lvalue sorted" << std::endl;
  //   Foo ret(*this);
  //   std::sort(ret.data.begin(), ret.data.end());
  return Foo(*this).sorted();
}