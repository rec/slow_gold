#ifndef __REC_UTIL_THREAD_MODALCALLBACK__
#define __REC_UTIL_THREAD_MODALCALLBACK__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

typedef juce::ModalComponentManager::Callback ModalCallback;

template <typename Type, typename Method>
class ModalCallback0 : public ModalCallback {
 public:
  ModalCallback0(Type* o, Method m) : object_(o), method_(m) {}
  virtual ~ModalCallback0() {}

  virtual void modalStateFinished(int returnValue) {
    (object_->*method_)(returnValue);
  }

 private:
  Type* object_;
  Method method_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ModalCallback0);
};

template <typename Type, typename Method, typename Value>
class ModalCallback1 : public ModalCallback {
 public:
  ModalCallback1(Type* o, Method m, Value v) : object_(o), method_(m), value_(v) {}
  virtual ~ModalCallback1() {}

  virtual void modalStateFinished(int returnValue) {
    (object_->*method_)(returnValue, value_);
    return true;
  }

 private:
  Type* object_;
  Method method_;
  Value value_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ModalCallback1);
};

template <typename Operator>
class ModalPointer0 : public ModalCallback {
 public:
  ModalPointer0(Operator op) : operator_(op) {}
  virtual ~ModalPointer0() {}
  virtual void modalStateFinished(int returnValue) {
    (*operator_)(returnValue);
  }

 private:
  Operator operator_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ModalPointer0);
};

template <typename Operator, typename Type>
class ModalPointer1 : public ModalCallback {
 public:
  ModalPointer1(Operator op, Type value) : operator_(op), value_(value) {}
  virtual ~ModalPointer1() {}
  virtual void modalStateFinished(int returnValue) {
    (*operator_)(returnValue, value_);
  }

 private:
  Operator operator_;
  Type value_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ModalPointer1);
};

template <typename Type, typename Method>
ModalCallback* modalCallback(Type* o, Method m) {
  return new ModalCallback0<Type, Method>(o, m);
}

template <typename Type, typename Method, typename Value>
ModalCallback* modalCallback(Type* o, Method m, Value v) {
  return new ModalCallback1<Type, Method, Value>(o, m, v);
}

template <typename Operator>
ModalCallback* modalFunctionCallback(Operator op) {
  return new ModalPointer0<Operator>(op);
}

template <typename Operator, typename Value>
ModalCallback* modalFunctionCallback(Operator op, Value v) {
  return new ModalPointer1<Operator, Value>(op, v);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MODALCALLBACK__
