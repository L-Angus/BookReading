#ifndef __WEAK_PTR_HPP__
#define __WEAK_PTR_HPP__

#include <atomic>
#include <iostream>
#include <memory>

#include "shared_ptr.hpp"

template <typename T> class weak_ptr {
public:
  weak_ptr() noexcept : m_control_block(nullptr) {}
  weak_ptr(const weak_ptr &other) noexcept
      : m_control_block(other.m_control_block) {
    if (m_control_block) {
      m_control_block->weak_ref_count->fetch_add(1);
    }
  }
  weak_ptr(const shared_ptr<T> &other) noexcept
      : m_control_block(other.m_control_block) {
    if (m_control_block) {
      m_control_block->weak_ref_count->fetch_add(1);
    }
  }
  weak_ptr &operator=(const shared_ptr<T> &other) noexcept {
    release();
    m_control_block = other.m_control_block;
    m_control_block->weak_ref_count.fetch_add(1, std::memory_order_relaxed);
    return *this;
  }
  weak_ptr &operator=(const weak_ptr &other) noexcept {
    if (this != &other) {
      release();
      m_control_block = other.m_control_block;
      if (m_control_block) {
        m_control_block->weak_ref_count->fetch_add(1,
                                                   std::memory_order_relaxed);
      }
    }
    return *this;
  }

  void reset() noexcept { release(); }
  size_t use_count() const noexcept {
    if (m_control_block) {
      return m_control_block->strong_ref_count.load();
    }
    return 0;
  }
  bool expired() const noexcept { return use_count() == 0; }

  shared_ptr<T> lock() const noexcept {
    if (expired()) {
      return shared_ptr<T>();
    }
    return shared_ptr<T>(m_control_block);
  }

private:
  typename shared_ptr<T>::ControlBlock *m_control_block;

  // release() 中的修正
  void release() noexcept {
    if (m_control_block) {
      // 原子递减弱引用计数
      if (m_control_block->weak_ref_count.fetch_sub(
              1, std::memory_order_acq_rel) == 1) {
        // 弱引用归零后，检查强引用
        if (m_control_block->strong_ref_count.load(std::memory_order_acquire) ==
            0) {
          delete m_control_block;
        }
      }
      m_control_block = nullptr;
    }
  }
};

void Test_Weak_Ptr() {
  std::cout << "Test_Weak_Ptr" << std::endl;
  weak_ptr<int> wp;
  auto wp_use_count = wp.use_count();
  std::cout << "wp_use_count: " << wp_use_count << std::endl;
  shared_ptr<int> sp(new int(42));
  wp = sp;
  auto wp_use_count2 = wp.use_count();
  std::cout << "wp_use_count2: " << wp_use_count2 << std::endl;
  auto sp_lock = wp.lock();
  if (sp_lock) {
    std::cout << *sp_lock << std::endl;
  }
  std::cout << "sp.use_count(): " << sp.use_count() << std::endl;

  std::cout << " --- Compare to std::weak_ptr --- " << std::endl;
  std::weak_ptr<int> swp1;
  auto swp1_use_count = swp1.use_count();
  std::cout << "swp1_use_count: " << swp1_use_count << std::endl;
  std::shared_ptr<int> sp1(new int(42));
  swp1 = sp1;
  auto swp1_use_count2 = swp1.use_count();
  std::cout << "swp1_use_count2: " << swp1_use_count2 << std::endl;
  if (auto sp_n = swp1.lock()) {
    std::cout << *sp_n << std::endl;
  }
  std::cout << "sp1.use_count(): " << sp1.use_count() << std::endl;

  std::cout << "Test_Weak_Ptr end" << std::endl;
}

#endif