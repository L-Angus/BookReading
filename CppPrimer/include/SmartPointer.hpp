#ifndef __SMARTPOINTER_HPP__
#define __SMARTPOINTER_HPP__

#include <atomic>
#include <functional>
#include <iostream>
#include <utility>

namespace CppPrimer {

template <typename T> class shared_ptr {
  friend void swap(shared_ptr &lhs, shared_ptr &rhs) { lhs.swap(rhs); }
  using Deleter = std::function<void(T *)>;

public:
  explicit shared_ptr(T *p = nullptr)
      : ptr(p), count(new std::atomic<size_t>{1}) {}
  shared_ptr(const shared_ptr &rhs) : ptr(rhs.ptr), count(rhs.count) {
    std::cout << "copy constructor" << std::endl;
    ++*count;
  }
  shared_ptr(shared_ptr &&rhs) noexcept : ptr(rhs.ptr), count(rhs.count) {
    std::cout << "move constructor" << std::endl;
    rhs.ptr = nullptr;
  }
  shared_ptr &operator=(shared_ptr &&rhs) noexcept {
    std::cout << "move assignment" << std::endl;
    if (this != &rhs) {
      ptr = rhs.ptr;
      count = rhs.count;
      rhs.ptr = nullptr;
    }
    return *this;
  }
  shared_ptr &operator=(const shared_ptr &rhs) {
    std::cout << "copy assignment" << std::endl;
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

  template <typename D>
  shared_ptr(T *p, D d)
      : ptr(p), count(new std::atomic<size_t>{1}), deleter(d) {}

  ~shared_ptr() {
    if (--*count == 0) {
      deleter ? deleter(ptr) : delete ptr;
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
    swap(deleter, rhs.deleter);
  };
  bool unique() const { return count == 1; }
  size_t use_count() const { return *count; }

  void reset(T *p = nullptr) {
    if (!p) {
      delete ptr;
      ptr = nullptr;
    } else {
      ptr = p;
      count = new std::atomic<size_t>{1};
      *count = 1;
    }
  }

  std::atomic<size_t> *get_count() const { return count; }

private:
  T *ptr{nullptr};
  std::atomic<size_t> *count;
  Deleter deleter;
};

template <typename T> class unique_ptr {};

template <typename T> class weak_ptr {
public:
  weak_ptr() : m_ptr(nullptr), m_count(new std::atomic<size_t>{0}) {}
  weak_ptr(const std::shared_ptr<T> &ptr)
      : m_ptr(ptr), m_count(new std::atomic<size_t>{0}) {
    m_count->fetch_add(1);
  }
  weak_ptr &operator=(const weak_ptr &rhs) {
    if (this != &rhs) {
      m_ptr = rhs.m_ptr;
      m_count = new std::atomic<size_t>{0};
    }
    return *this;
  }
  weak_ptr &operator=(std::shared_ptr<T> &rhs) {
    m_ptr = rhs;
    m_count = new std::atomic<size_t>{0};
    m_count->fetch_add(1);
    return *this;
  }
  void reset() {
    if (m_ptr) {
      m_ptr = nullptr;
      m_count = new std::atomic<size_t>{0};
    }
  }
  bool expired() const { return use_count() == 0; }
  size_t use_count() const { return ++*m_count; }
  std::shared_ptr<T> lock() {
    if (expired())
      return nullptr;
    m_count = new std::atomic<size_t>(m_ptr.use_count());
    return m_ptr;
  }

private:
  std::shared_ptr<T> m_ptr;
  std::atomic<size_t> *m_count;
};

template <typename T, typename Args> shared_ptr<T> make_shared(Args &&t) {
  return shared_ptr<T>(std::forward<T>(t));
}

}; // namespace CppPrimer

#endif