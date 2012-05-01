#ifndef __REC_UTIL_DESTRUCT_PTR__
#define __REC_UTIL_DESTRUCT_PTR__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type> void destroy(Type* t) {
  if (t) {
    t->destroy();
    delete t;
  }
}

template <typename Type>
class destruct_ptr<Type> {
 public:
  explicit destruct_ptr(Type* p = 0) : p_(p) { }

  ~destruct_ptr() { destruct(); }

  void reset(Type* p = NULL) {
    if (p != p_) {
      destruct();
      p_ = p;
    }
  }


  Type& operator*() const { return *p_; }
  Type* operator->() const { return p_; }

  Type* get() const { return p_; }

  Type* transfer() {
    Type* p = p_;
    p_ = NULL;
    return p;
  }

  Type* xfer() { return transfer(); }

  void swap(ptr& that) {
    Type* tmp = that.p_;
    that.p_ = this->p_;
    this->p_ = tmp;
  }

  operator bool() const { return p_ != NULL; }
  bool operator!() const { return !p_; }

 private:
  void destruct() { destroy(transfer()); }

  Type* p_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ptr);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DESTRUCT_PTR__
