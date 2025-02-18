#ifndef __STRBLOBPTR_HPP__
#define __STRBLOBPTR_HPP__

#include "StrBlob.h"
#include <cstddef> // 为了使用 size_t 类型
#include <memory>
#include <string>
#include <vector>

class StrBlobPtr {
public:
  StrBlobPtr() : curr(0) {}
  StrBlobPtr(StrBlob<std::string> &a, std::size_t sz = 0)
      : wptr(a.data()), curr(sz) {}
  std::string &deref() const;
  StrBlobPtr &incr();

private:
  std::shared_ptr<std::vector<std::string>> check(std::size_t i,
                                                  const std::string &msg) const;
  std::weak_ptr<std::vector<std::string>> wptr;
  std::size_t curr;
};

#endif