#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__

#include <atomic>
#include <functional>
#include <iostream>

#include "TString.h"

template <typename T> class weak_ptr;

template <typename T> class shared_ptr {
  friend class weak_ptr<T>;
  struct ControlBlock {
    std::atomic<size_t> strong_ref_count{1};
    std::atomic<size_t> weak_ref_count{0};
    T *ptr{nullptr};
    std::function<void(T *)> deleter;
    ControlBlock(T *p) : ptr(p) {}
    ~ControlBlock() {
      if (ptr && !deleter) {
        delete ptr;
      } else if (ptr && deleter) {
        deleter(ptr);
      }
    }
  };

public:
  explicit shared_ptr(T *p = nullptr)
      : m_control_block(p ? new ControlBlock(p) : nullptr) {}
  shared_ptr(const shared_ptr &other) : m_control_block(other.m_control_block) {
    if (m_control_block) {
      ++m_control_block->strong_ref_count;
    }
  }
  shared_ptr &operator=(const shared_ptr &other) {
    if (this != &other) {
      release();
      m_control_block = other.m_control_block;
      if (m_control_block) {
        ++m_control_block->strong_ref_count;
      }
    }
  }
  shared_ptr(shared_ptr &&other) noexcept
      : m_control_block(other.m_control_block) {
    other.m_control_block = nullptr;
  }
  shared_ptr &operator=(shared_ptr &&other) noexcept {
    if (this != &other) {
      release();
      m_control_block = other.m_control_block;
      other.m_control_block = nullptr;
    }
    return *this;
  }

  template <typename D>
  shared_ptr(T *p, D d) : m_control_block(p ? new ControlBlock(p) : nullptr) {
    if (m_control_block) {
      m_control_block->deleter = d;
    }
  }

  shared_ptr(ControlBlock *cb) : m_control_block(cb) {}

  shared_ptr(T *ptr, ControlBlock *cb) : m_control_block(cb) {
    if (m_control_block) {
      m_control_block->ptr = ptr;
    }
  }
  ~shared_ptr() { release(); }

  size_t use_count() const {
    return m_control_block ? m_control_block->strong_ref_count.load() : 0;
  }
  T *get() const { return m_control_block ? m_control_block->ptr : nullptr; }
  T &operator*() const { return *get(); }
  T *operator->() const { return get(); }
  bool unique() const { return use_count() == 1; }
  operator bool() const {
    if (m_control_block) {
      return m_control_block->ptr != nullptr;
    }
    return false;
  }

private:
  ControlBlock *m_control_block;
  void release() noexcept {
    if (m_control_block) {
      if (--m_control_block->strong_ref_count == 0) {
        delete m_control_block;
        m_control_block = nullptr;
      }
    }
  }
};

void Test_Shared_Ptr() {
  std::cout << "Test_Shared_Ptr" << std::endl;
  shared_ptr<int> p1;
  std::cout << "p1.use_count() = " << p1.use_count() << std::endl;
  shared_ptr<TString> m_ts(new TString("Hello World"));
  m_ts->print();
  std::cout << "m_ts.unique() = " << m_ts.unique() << std::endl;
  shared_ptr<TString> m_ts2(m_ts);
  m_ts2->print();
  std::cout << "m_ts2.use_count() = " << m_ts2.use_count() << std::endl;
  auto m_ts3 = m_ts2;
  m_ts3->print();
  std::cout << "m_ts3.use_count() = " << m_ts3.use_count() << std::endl;
  auto m_ts4 = std::move(m_ts3);
  m_ts4->print();
  std::cout << "m_ts4.use_count() = " << m_ts4.use_count() << std::endl;

  std::cout << std::endl;
  std::cout << "*************** COMPARE ****************" << std::endl;
  std::cout << std::endl;

  std::cout << "Test_std::shared_ptr" << std::endl;
  std::shared_ptr<int> sp1{};
  std::cout << "sp1.use_count() = " << sp1.use_count() << std::endl;
  std::shared_ptr<TString> sp_ts(new TString("Hello World"));
  sp_ts->print();
  std::cout << "sp_ts.unique() = " << sp_ts.unique() << std::endl;
  std::shared_ptr<TString> sp_ts2(sp_ts);
  sp_ts2->print();
  std::cout << "sp_ts2.use_count() = " << sp_ts2.use_count() << std::endl;
  auto sp_ts3 = sp_ts2;
  sp_ts3->print();
  std::cout << "sp_ts3.use_count() = " << sp_ts3.use_count() << std::endl;
  auto sp_ts4 = std::move(sp_ts3);
  sp_ts4->print();
  std::cout << "sp_ts4.use_count() = " << sp_ts4.use_count() << std::endl;
}

#endif