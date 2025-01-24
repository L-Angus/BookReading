#include "../include/TString.h"

#include <iostream>
#include <vector>

int main() {
  TString s("Cpp Primer 5th");
  std::cout << s << std::endl;
  std::cout << s.capacity() << std::endl;
  std::cout << s.size() << std::endl;

  TString s2;
  s2 = s;
  std::cout << s2 << std::endl;
  std::cout << s2.capacity() << std::endl;
  std::cout << s2.size() << std::endl;

  TString s3(s);
  std::cout << s3 << std::endl;
  std::cout << s3.capacity() << std::endl;
  std::cout << s3.size() << std::endl;

  std::vector<TString> vec;
  vec.push_back(s);
  vec.push_back(s2);
  vec.push_back(s3);

  return 0;
}