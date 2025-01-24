#include "../include/StrVec.h"

StrVec::StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
StrVec::StrVec(const StrVec &rhs) : StrVec() {
  auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
  elements = newdata.first;
  first_free = newdata.second;
  cap = rhs.cap;
}
StrVec &StrVec::operator=(const StrVec &rhs) {
  auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = newdata.first;
  first_free = newdata.second;
  cap = rhs.cap;
  return *this;
}

StrVec::StrVec(std::initializer_list<std::string> il) : StrVec() {
  auto newdata = alloc_n_copy(il.begin(), il.end());
  elements = newdata.first;
  first_free = newdata.second;
  cap = newdata.second;
}

StrVec::~StrVec() { free(); }
void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
  std::allocator_traits<std::allocator<std::string>>::construct(
      alloc, first_free++, s);
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements) {
    // 销毁元素
    std::for_each(elements, first_free, [this](std::string &s) {
      std::allocator_traits<std::allocator<std::string>>::destroy(alloc, &s);
    });
    // 释放内存
    alloc.deallocate(elements, cap - elements);
  }
}
void StrVec::chk_n_alloc() {
  if (size() == capacity()) {
    reallocate();
  }
}
void StrVec::reallocate() {
  // 计算新容量，一般是当前大小的2倍
  // 如果为空，则分配空间容纳1个元素
  auto newcapacity = size() ? 2 * size() : 1;
  reallocate_n(newcapacity);
}

void StrVec::reserve(size_t n) {
  if (n > capacity()) {
    reallocate_n(n);
  }
}

void StrVec::resize(size_t n) {
  if (n > size()) {
    resize(n, std::string());
  } else if (n < size()) {
    while (first_free != elements + n) {
      std::allocator_traits<std::allocator<std::string>>::destroy(alloc,
                                                                  --first_free);
    }
  }
}

void StrVec::reallocate_n(size_t n) {
  auto newdata = alloc.allocate(n);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i != size(); ++i) {
    std::allocator_traits<std::allocator<std::string>>::construct(
        alloc, dest++, std::move(*elem++));
  }
  free();
  elements = newdata;
  first_free = dest;
  cap = elements + n;
}

void StrVec::resize(size_t n, const std::string &s) {
  if (n > size()) {
    // 先确保是否具备足够的空间
    if (n > capacity()) {
      reallocate_n(n);
    }
    while (size() < n) {
      std::allocator_traits<std::allocator<std::string>>::construct(
          alloc, first_free++, s);
    }
  }
}
