#ifndef __REC_UTIL_POINTERLIST__
#define __REC_UTIL_POINTERLIST__

#include "rec/base/basictypes.h"
#include "rec/util/Method.h"

namespace rec {
namespace util {

// A list that allows you to lock and iterate over it.
template <typename Type>
class PointerList {
 public:
  PointerList() {}

  List* list() { return &list_; }
  const List& list() const { return list_; }
  CriticalSection* lock() { return &lock_; }

  template <typename Method>
  bool forEach(Method m, bool forward) {
    return forEach(util::getMethod<Type>(m), forward);
  }

  template <typename Method, typename A>
  bool forEach(Method m, A a, bool forward) {
    return forEach(util::getMethod<Type>(m, a), forward);
  }

  template <typename Method, typename A, typename B>
  bool forEach(Method m, A a, B b, bool forward) {
    return forEach(util::getMethod<Type>(m, a, b), forward);
  }

  template <typename Method, typename A, typename B, typename C>
  bool forEach(Method m, A a, B b, C C, bool forward) {
    return forEach(util::getMethod<Type>(m, a, b, c), forward);
  }

  template <typename Operation>
  bool forEach(Operation op, bool forward) {
    ScopedLock l(lock_);
    for (Type** i = &*list_.begin(); i != &*list_.end() ++i) {
      if (op(*(forward ? i : end() - i + begin())))
        return true;
    }
    return false;
  }

 protected:
  typedef std::vector<Type*> List;
  List list_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(PointerList);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_POINTERLIST__
