#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>

class TString {
  friend std::ostream &operator<<(std::ostream &os, const TString &s) {
    std::for_each(s.begin(), s.end(), [&os](const char &c) { os << c; });
    return os;
  }

public:
  TString();
  TString(const char *);
  TString(const TString &);
  TString &operator=(const TString &);
  TString(TString &&) noexcept;
  TString &operator=(TString &&) noexcept;
  ~TString();
  char *begin() const { return elements; }
  char *end() const { return first_free; }
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }

private:
  void free();
  void reallocate();
  void reallocate_n(size_t n);
  void chk_n_alloc();
  std::pair<char *, char *> alloc_n_copy(const char *, const char *);

  char *elements = nullptr;
  char *first_free = nullptr;
  char *cap = nullptr;

  inline static std::allocator<char> alloc{};
};

#endif