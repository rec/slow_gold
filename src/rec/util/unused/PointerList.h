#pragma once

#include "rec/base/base.h"
#include "rec/util/Method.h"

namespace rec {
namespace util {

// A list that allows you to lock and iterate over it.
template <typename Type>
class PointerList {
  public:
    PointerList() {}

    typedef vector<Type*> List;
    typedef util::Method<Type> Method;

    List* list() { return &list_; }
    const List& list() const { return list_; }

    CriticalSection* lock() { return &lock_; }

    template <typename M>
    bool forEach(M m, bool forward) {
        return forEachOp(Method::get(m), forward);
    }

    template <typename M, typename A>
    bool forEach(M m, A a, bool forward) {
        return forEachOp(Method::get(m, a), forward);
    }

    template <typename M, typename A, typename B>
    bool forEach(M m, A a, B b, bool forward) {
        return forEachOp(Method::get(m, a, b), forward);
    }

    template <typename M, typename A, typename B, typename C>
    bool forEach(M m, A a, B b, C c, bool forward) {
        return forEachOp(Method::get(m, a, b, c), forward);
    }

    template <typename Operation>
    bool forEachOp(Operation op, bool forward) {
        Lock l(lock_);

        Type** begin = &*list_.begin();
        Type** end = &*list_.end();

        for (Type** i = begin; i != end; ++i) {
            if (op(*(forward ? i : end - 1 - i + begin)))
                return true;
        }
        return false;
    }

  protected:
    List list_;
    CriticalSection lock_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(PointerList);
};

}  // namespace util
}  // namespace rec

