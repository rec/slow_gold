#ifndef __REC_UTIL_THREAD_POINTER__
#define __REC_UTIL_THREAD_POINTER__

#include "rec/util/thread/Callback.h"
#include "rec/util/thread/Callback1.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

// Wrap any C++ callable into a Callback.
template <typename Operator>
class Pointer : public Callback {
 public:
  Pointer(Operator op) : operator_(op) {}
  virtual ~Pointer() {}
  virtual bool operator()() { (*operator_)(); return true; }

 protected:
  Operator const operator_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Pointer);
};

// A Pointer that owns its underlying callable.
template <typename Operator>
class OwnedPointer : public Pointer<Operator*>,
                     public ptr<Operator> {
 public:
  explicit OwnedPointer(Operator* r) : Pointer<Operator*>(r), ptr<Operator>(r) {}
  virtual ~OwnedPointer() {}
  virtual bool operator()() { (*(this->get()))(); return true; }
};

}  // namespace callback
}  // namespace thread

typedef thread::callback::Callback Callback;

template <typename Operator>
Callback* makePointer(Operator op) {
  return new thread::callback::Pointer<Operator>(op);
}

template <typename Operator, typename Value>
Callback* makePointer(Operator op, Value v) {
  return new thread::callback::CallbackFunc1<Operator, Value>(op, v);
}

}  // namespace util
}  // namespce rec

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

#endif  // __REC_UTIL_THREAD_POINTER__
