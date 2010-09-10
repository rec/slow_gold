#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/basictypes.h"

namespace rec {
namespace thread {

template <typename Type>
class Callback : public Runnable {
 public:
  typedef void (Type::*Method)();
  Callback(Type* object, Method method) : object_(object), method_(method) {}

  virtual void run(Thread*) { (object_->*method_)(); }

 private:
  Type* object_;
  Method method_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Callback);
};

template <typename Type, typename Method>
Runnable* makeCallback(Type* object, Method method) {
  return new Callback<Type>(object, method);
}

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
