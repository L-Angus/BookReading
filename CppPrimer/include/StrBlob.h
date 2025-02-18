#ifndef __STRBLOB_HPP__
#define __STRBLOB_HPP__

#include <memory>

#include <iostream>
#include <string>
#include <vector>

template <typename T> class StrBlob {
public:
  typedef typename std::vector<T>::size_type size_type;

  StrBlob() : m_data(std::make_shared<std::vector<T>>()) {}
  explicit StrBlob(std::initializer_list<T> il)
      : m_data(std::make_shared<std::vector<T>>(il)) {}
  size_type size() const { return m_data->size(); }
  bool empty() const { return m_data->empty(); }
  void push_back(const T &t) { m_data->push_back(t); }
  void pop_back() {
    check(0, "pop_back on empty StrBlob");
    m_data->pop_back();
  }
  T &front() {
    std::cout << "front" << std::endl;
    check(0, "front on empty StrBlob");
    return m_data->front();
  }
  const T &front() const {
    std::cout << "front const" << std::endl;
    check(0, "front on empty StrBlob");
    return m_data->front();
  }

  T &back() {
    check(0, "back on empty StrBlob");
    return m_data->back();
  }
  const T &back() const {
    check(0, "back on empty StrBlob");
    return m_data->back();
  }

  std::shared_ptr<std::vector<T>> data() const { return m_data; }

private:
  std::shared_ptr<std::vector<T>> m_data;
  void check(size_type i, const std::string &msg) const {
    if (i >= m_data->size()) {
      throw std::out_of_range(msg);
    }
  }
};

#endif