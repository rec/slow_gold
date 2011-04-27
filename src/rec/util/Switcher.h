#ifndef __REC_UTIL_SWITCHER__
#define __REC_UTIL_SWITCHER__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
class Switcher {
 public:
  Switcher() {}

  Type* current() { return current_.get(); }
  Type* next() { return next_.get(); }

  void setNext(Type* n) {
    if (next_) {
      LOG(ERROR) << "Tried to set next before switch";
      delete n;
    } else {
      next_.reset(n);
    }
  }

  void switchIfNext() {
    if (next_) {
      current_.swap(next_);
      next_.reset();
    }
  }

 private:
  ptr<Type> current_, next_;

  DISALLOW_COPY_AND_ASSIGN(Switcher);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_SWITCHER__
