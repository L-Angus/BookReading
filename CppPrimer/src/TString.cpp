#include "../include/TString.h"
#include <cstring>
TString::TString() : elements(nullptr), first_free(nullptr), cap(nullptr) {
  std::cout << "--- default constructor ---" << std::endl;
}
TString::TString(const char *s) : TString() {
  auto new_elements = alloc_n_copy(s, s + strlen(s));
  elements = new_elements.first;
  first_free = cap = new_elements.second;
}

TString::TString(const TString &s) : TString() {
  std::cout << "copy constructor" << std::endl;
  auto new_elements = alloc_n_copy(s.begin(), s.end());
  elements = new_elements.first;
  first_free = cap = new_elements.second;
}

TString &TString::operator=(const TString &rhs) {
  std::cout << "copy assignment" << std::endl;
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}
TString::TString(TString &&s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap) {
  std::cout << "move constructor" << std::endl;
  s.elements = s.first_free = s.cap = nullptr;
}

TString &TString::operator=(TString &&rhs) noexcept {
  std::cout << "move assignment" << std::endl;
  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

TString::~TString() { free(); }
void TString::free() {
  if (elements) {
    // 使用std::destroy替代allocator::destroy
    std::destroy(elements, first_free);
    alloc.deallocate(elements, cap - elements);
  }
}
void TString::reallocate() {
  auto new_capacity = size() ? 2 * size() : 1;
  reallocate_n(new_capacity);
}
void TString::reallocate_n(size_t n) {
  auto new_elements = alloc.allocate(n);
  auto dest = std::uninitialized_move(elements, first_free, new_elements);
  free();
  elements = new_elements;
  first_free = dest;
  cap = elements + n;
}
void TString::chk_n_alloc() {
  if (size() == capacity())
    reallocate();
}
std::pair<char *, char *> TString::alloc_n_copy(const char *b, const char *e) {
  auto new_elements = alloc.allocate(e - b);
  return {new_elements, std::uninitialized_copy(b, e, new_elements)};
}

void TString::print() const {
  for (auto p = elements; p != first_free; ++p)
    std::cout << *p << " ";
  std::cout << std::endl;
}