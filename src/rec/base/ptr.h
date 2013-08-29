#ifndef __REC_UTIL_PTR
#define __REC_UTIL_PTR

#include <memory>

#include "rec/base/disallow.h"

using std::unique_ptr;

// scoped_ptr mimics a built-in pointer except that it guarantees deletion
// of the object pointed to, either on destruction of the scoped_ptr or via
// an explicit reset().

template <typename Type>
class ptr {
 public:
  explicit ptr(Type* p = 0) : p_(p) { }

  ~ptr() { delete p_; }

  void reset(Type* p = nullptr) {
    if (p != p_) {
      delete p_;
      p_ = p;
    }
  }

  Type& operator*() const { return *p_; }
  Type* operator->() const { return p_; }

  Type* get() const { return p_; }

  Type* release() {
    Type* p = p_;
    p_ = nullptr;
    return p;
  }

  void swap(ptr& that) {
    Type* tmp = that.p_;
    that.p_ = this->p_;
    this->p_ = tmp;
  }

  operator bool() const { return p_ != nullptr; }
  bool operator!() const { return !p_; }

 private:
  Type* p_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ptr);
};

#endif // __REC_UTIL_PTR
