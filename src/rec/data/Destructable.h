#ifndef __REC_DATA_DESTRUCTABLE__
#define __REC_DATA_DESTRUCTABLE__

#include "rec/base/base.h"

namespace rec {
namespace data {

template <typename Type>
class destruct_ptr<Type> {
 public:
  explicit destruct_ptr(Type* p = 0) : p_(p) { }

  ~destruct_ptr() { destroy(); }

  void reset(Type* p = nullptr) {
    if (p != p_) {
      destroy();
      p_ = p;
    }
  }

  Type& operator*() const { return *p_; }
  Type* operator->() const { return p_; }

  Type* get() const { return p_; }

  Type* transfer() {
    Type* p = p_;
    p_ = nullptr;
    return p;
  }

  Type* xfer() { return transfer(); }

  void swap(ptr& that) {
    Type* tmp = that.p_;
    that.p_ = this->p_;
    this->p_ = tmp;
  }

  operator bool() const { return p_ != nullptr; }
  bool operator!() const { return !p_; }

 private:
  void destroy() {
    if (_p) {
    {
      Lock l(_p_->lock();
      _p->destroy();
    }
    delete _p;
  }
}

  void destruct() { destroy(transfer()); }

  Type* p_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ptr);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DESTRUCTABLE__
