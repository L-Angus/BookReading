#ifndef __HASPTR_HPP__
#define __HASPTR_HPP__

#include <iostream>
#include <string>

class HasPtr {
  friend void swap(HasPtr &, HasPtr &);

public:
  HasPtr(const std::string &s = std::string())
      : ps(new std::string(s)), i(0), use(new size_t(1)) {}
  HasPtr(const HasPtr &rhs) : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++*use; }
  // HasPtr &operator=(const HasPtr &rhs) {
  //   ++*rhs.use;
  //   if (--*use == 0) {
  //     delete ps;
  //     delete use;
  //   }
  //   ps = rhs.ps;
  //   i = rhs.i;
  //   use = rhs.use;
  //   return *this;
  // }
  HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i), use(rhs.use) {
    rhs.ps = nullptr;
    rhs.use = nullptr;
  }
  HasPtr &operator=(HasPtr rhs) {
    std::cout << "copy and swap" << std::endl;
    swap(*this, rhs);
    return *this;
  }

  bool operator<(const HasPtr &rhs) const { return *ps < *rhs.ps; }
  ~HasPtr() {
    if (--*use == 0) {
      delete ps;
      delete use;
    }
  }

  size_t use_count() const { return *use; }

private:
  std::string *ps;
  int i;
  size_t *use;
};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
  swap(lhs.use, rhs.use);
  std::cout << "swap" << std::endl;
}

#endif