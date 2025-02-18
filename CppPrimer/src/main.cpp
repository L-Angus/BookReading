#include "../include/Foo.h"
#include "../include/HasPtr.hpp"
#include "../include/LinkedList.hpp"
#include "../include/SmartPointer.hpp"
#include "../include/StrBlob.h"
#include "../include/StrVec.h"
#include "../include/TString.h"
#include "../include/Test.hpp"
#include "../include/allocator.hpp"
#include "../include/shared_ptr.hpp"
#include "../include/weak_ptr.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
  // Test_Shared_Ptr();
  // Test_Shared_Ptr_Deleter();
  // Test_Weak_Ptr();
  // Test_12_33();
  LinkedList<int> *list = new LinkedList<int>();
  list->print();
  list->add(1);
  list->add(2);
  list->add(3);
  list->print();

  // 释放内存
  delete list;
  return 0;
}