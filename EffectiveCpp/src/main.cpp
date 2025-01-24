#include <iostream>

#include "NamedObject.hpp"
int main() {
  std::cout << "Hello World!" << std::endl;
  NamedObject no;
  NamedObject no2;
  no2 = no;
  return 0;
}