#ifndef __REC_BASE_STL__
#define __REC_BASE_STL__

#include <memory>

#include "rec/base/disallow.h"
#include "rec/base/make_unique.h"

using std::unique_ptr;

#ifdef _MAKE_UNSIGNED
template <class T>
typename make_signed<T>::type as_signed(T t)
    { return make_signed<T>::type(t); }

template <class T>
typename make_unsigned<T>::type as_unsigned(T t)
    { return make_unsigned<T>::type(t); }
#endif

// ptr, a clone of scoped_ptr, mimics a built-in pointer except that it
// guarantees deletion of the object pointed to, either on destruction of the
// scoped_ptr or via an explicit reset().
//
// DEPRECATED: use unique_ptr for new code.

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

#endif // __REC_BASE_STL__
