#ifndef __SMARTPOINTER_HPP__
#define __SMARTPOINTER_HPP__

#include <atomic>
#include <iostream>
#include <utility>

namespace CppPrimer {

template <typename T> class shared_ptr {
  friend void swap(shared_ptr &lhs, shared_ptr &rhs) { lhs.swap(rhs); }

public:
  shared_ptr(T *p = nullptr) : ptr(p), count(new std::atomic<size_t>{1}) {}
  shared_ptr(const shared_ptr &rhs) : ptr(rhs.ptr), count(rhs.count) {
    ++*count;
  }
  shared_ptr &operator=(const shared_ptr &rhs) {
    if (this != &rhs) {
      if (--*count == 0) {
        delete ptr;
        delete count;
      }
      ptr = rhs.ptr;
      count = rhs.count;
      ++*count;
    }
    return *this;
  }
  ~shared_ptr() {
    if (--*count == 0) {
      delete ptr;
      delete count;
    }
  }
  T *operator->() const { return get(); }
  T &operator*() const { return *ptr; }
  T *get() const { return ptr; };
  void swap(shared_ptr &rhs) {
    using std::swap;
    swap(ptr, rhs.ptr);
    swap(count, rhs.count);
  };
  bool unique() const { return count == 1; }
  size_t use_count() const { return *count; }

private:
  T *ptr{nullptr};
  std::atomic<size_t> *count;
};

template <typename T> class unique_ptr {};

template <typename T> class weak_ptr {};

template <typename T, typename Args> shared_ptr<T> make_shared(Args &&t) {
  return shared_ptr<T>(std::forward<T>(t));
}

}; // namespace CppPrimer

#endif