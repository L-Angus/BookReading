#include "../include/Foo.h"
#include "../include/HasPtr.hpp"
#include "../include/SmartPointer.hpp"
#include "../include/StrBlob.h"
#include "../include/StrVec.h"
#include "../include/TString.h"
#include "../include/Test.hpp"
#include "../include/shared_ptr.hpp"
#include "../include/weak_ptr.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
  // Test_Shared_Ptr();
  // Test_Shared_Ptr_Deleter();
  Test_Weak_Ptr();
  return 0;
}