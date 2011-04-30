#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

// A generic callback.
class Callback {
 public:
  virtual bool operator()() = 0;
  virtual ~Callback() {}
};

#if 0
// Wrap any C++ callable into a Callback.
template <typename Operator>
class PointerBool : public Callback {
 public:
  PointerBool(Operator op) : operator_(op) {}
  virtual ~PointerBool() {}
  virtual bool operator()() { return operator_(); }

 protected:
  Operator const operator_;
};

// A Pointer that owns its underlying callable.
template <typename Operator>
class BoolOwnedPointer : public Pointer<Operator*>,
                         public ptr<Operator> {
 public:
  explicit BoolOwnedPointer(Operator* r = NULL) : Pointer<Operator*>(r), ptr<Operator>(r) {}
  virtual ~BoolOwnedPointer() {}
  virtual bool operator()() { return (*(this->get()))(); }
};

#endif

}  // namespace callback
}  // namespace thread
}  // namespace util
}  // namespace rec

#include "Pointer.h"

#endif  // __REC_THREAD_CALLBACK__
