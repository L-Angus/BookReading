#ifndef __STRVEC_HPP__
#define __STRVEC_HPP__

#include <initializer_list>
#include <string>

class StrVec {
public:
  StrVec();
  StrVec(const StrVec &);
  StrVec &operator=(const StrVec &);
  StrVec(std::initializer_list<std::string>);
  StrVec(StrVec &&) noexcept;
  StrVec &operator=(StrVec &&) noexcept;
  ~StrVec();
  void push_back(const std::string &);
  void push_back(std::string &&);
  void reserve(size_t n);
  void resize(size_t n);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }
  StrVec getVec(std::istream &);

private:
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();
  void chk_n_alloc();
  void reallocate();
  void reallocate_n(size_t);
  void resize(size_t, const std::string &);

  std::string *elements;   // 指向数组首元素的指针
  std::string *first_free; // 指向数组第一个空闲元素的指针
  std::string *cap;        // 指向数组尾后位置的指针
  inline static std::allocator<std::string> alloc{};
};

#endif