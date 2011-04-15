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
class OwnedPointer : public Pointer<Operator*>,
                     public ptr<Operator> {
 public:
  explicit OwnedPointer(Operator* r) : Pointer<Operator*>(r), ptr<Operator>(r) {}
  virtual ~OwnedPointer() {}
  virtual bool operator()() { (*(this->get()))(); return true; }
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

template <typename Value>
class FunctionValue {
 public:
  typedef void (*Function)(Value);
  FunctionValue(Function f,  Value v) : function_(f), value_(v) {}
  virtual ~FunctionValue() {}
  virtual bool operator()() { return function_(value_); }

 private:
  Function function_;
  Value value_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(FunctionValue);
};

}  // namespace callback
}  // namespace thread

typedef thread::callback::Callback Callback;

}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
