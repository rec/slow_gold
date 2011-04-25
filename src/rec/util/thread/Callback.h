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

template <typename Operator, typename Value>
class OperatorValue : public Callback {
 public:
  OperatorValue(Operator f,  Value v) : function_(f), value_(v) {}
  virtual ~OperatorValue() {}
  virtual bool operator()() { function_(value_); return true; }

 private:
  Operator function_;
  Value value_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(OperatorValue);
};

}  // namespace callback
}  // namespace thread

typedef thread::callback::Callback Callback;

template <typename Operator>
Callback* makePointer(Operator op) { return new thread::callback::Pointer<Operator>(op); }

template <typename Operator, typename Value>
Callback* makePointer(Operator op, Value v) {
  return new thread::callback::OperatorValue<Operator, Value>(op, v);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
