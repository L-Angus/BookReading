#include "../include/Foo.h"
#include "../include/HasPtr.hpp"
#include "../include/SmartPointer.hpp"
#include "../include/StrBlob.h"
#include "../include/StrVec.h"
#include "../include/TString.h"

#include <iostream>
#include <memory>
#include <vector>

int main() {
  // CppPrimer::shared_ptr<int> p1(new int(42));
  // std::cout << *p1 << std::endl;
  // CppPrimer::shared_ptr<TString> p2(new TString("hello"));
  // CppPrimer::shared_ptr<TString> p3(new TString("hello"));
  // p2 = p3;
  // std::cout << p2.use_count() << std::endl;
  // std::cout << p3.use_count() << std::endl;

  // CppPrimer::shared_ptr<TString> p4(new TString("hello1"));
  // p2 = p4;
  // std::cout << p2.use_count() << std::endl;
  // std::cout << p3.use_count() << std::endl;
  // std::cout << p4.use_count() << std::endl;

  // p3.swap(p4);
  // std::cout << *p3 << std::endl;

  // auto p5(p4);
  // std::cout << p5.use_count() << std::endl;

  // std::cout << "------------------ compare --------------------" <<
  // std::endl;

  // std::shared_ptr<int> sp1(new int(42));
  // std::cout << *sp1 << std::endl;
  // std::shared_ptr<TString> sp2(new TString("hello"));
  // std::shared_ptr<TString> sp3(new TString("world"));
  // sp2 = sp3;
  // std::cout << sp2.use_count() << std::endl;
  // std::cout << sp3.use_count() << std::endl;

  // std::shared_ptr<TString> sp4(new TString("hello1"));
  // sp2 = sp4;
  // std::cout << sp2.use_count() << std::endl;
  // std::cout << sp3.use_count() << std::endl;
  // std::cout << sp4.use_count() << std::endl;
  StrBlob<std::string> b1;
  {
    StrBlob<std::string> b2{"a", "an", "the"};
    b1 = b2;
    b2.push_back("about");
    std::cout << "b1 size: " << b1.size() << std::endl;
    std::cout << "b2 size: " << b2.size() << std::endl;
  }

  b1.front() = "another string";
  std::cout << b1.front() << std::endl;

  const StrBlob<std::string> cb1 = b1;
  std::cout << cb1.front() << std::endl;

  return 0;
}