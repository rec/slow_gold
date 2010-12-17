#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/base.h"
#include "rec/util/thread/Runnable.h"

namespace rec {
namespace thread {

template <typename Type>
class Callback : public Runnable {
 public:
  typedef void (Type::*Method)();
  Callback(Type* obj, Method m, bool owns = false)
      : object_(obj), method_(m), owns_(owns) {
  }
  virtual ~Callback() { if (owns_) delete object_; }

  virtual bool run(Thread*) {
    return (object_->*method_)();
  }

 private:
  Type* object_;
  Method method_;
  const bool owns_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Callback);
};

template <typename Type, typename Method>
Runnable* makeCallback(Type* object, Method method, bool owns = false) {
  return new Callback<Type>(object, method, owns);
}

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
