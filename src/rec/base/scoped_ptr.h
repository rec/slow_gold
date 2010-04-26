#ifndef __REC_UTIL_SCOPED_PTR
#define __REC_UTIL_SCOPED_PTR

#include <stddef.h>
#include "rec/base/basictypes.h"

//  scoped_ptr mimics a built-in pointer except that it guarantees deletion
//  of the object pointed to, either on destruction of the scoped_ptr or via
//  an explicit template().

template <typename Type>
class scoped_ptr {
 public:
  explicit scoped_ptr(Type* p = NULL) : p_(p) { }

  ~scoped_ptr() { delete p_; }

  void reset(Type* p = NULL) {
    if (p != p_) {
      delete p_;
      p_ = p;
    }
  }

  Type& operator*() const { return *p_; }
  Type*  operator->() const { return p_; }

  Type* get() const { return p_; }

  Type* transfer() {
    Type* p = p_;
    p_ = NULL;
    return p;
  }

  void swap(scoped_ptr & that) {
    Type* tmp = that.p_;
    that.p_ = this->p_;
    this->p_ = tmp;
  }

  operator bool() const { return p_; }
  bool operator!() const { return !p_; }

 private:
  Type* p_;

  DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

#if 0
template<typename Type> class scoped_array {
 public:
  explicit scoped_array(Type* p = 0) : p_(p) {}
  ~scoped_array() { delete [] p_; }

  void reset(Type *p = 0) {
    if (p != p_) {
      delete [] p_;
      p_ = p;
    }
  }

  Type & operator[](std::ptrdiff_t i) const { return p_[i]; }

  Type* get() const { return p_; }

  void swap(scoped_array & sp) {
    Type* tmp = sp.p_;
    sp.p_ = p_;
    p_ = tmp;
  }

 private:
  Type* p_;

  DISALLOW_COPY_AND_ASSIGN(scoped_array);
};

template<class Type>
void swap(scoped_ptr<Type>& a, scoped_ptr<Type>& b) { a.swap(b); }

template<class Type>
void swap(scoped_array<Type>& a, scoped_array<Type>& b) { a.swap(b); }

#endif

#endif // #ifndef __REC_UTIL_SCOPED_PTR
