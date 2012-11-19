#ifndef __REC_UTIL_METHODLISTENER__
#define __REC_UTIL_METHODLISTENER__

#include "rec/util/Listener.h"

namespace rec {
namespace util {

template <typename Object, typename Type>
class MethodListener : public Listener<Type> {
 public:
  typedef void (Object::*Method)(Type);

  MethodListener(Object* o, Method m) : object_(o), method_(m) {}

  virtual void operator()(Type t) { object_->*method_(t); }

 private:
  Object* const object_;
  Method method_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(MethodListener);
};

template <typename Object, typename Type>
Listener<Type>* methodListener(
    Object* object,
    typename MethodListener<Object, Type>::Method method) {
  return new MethodListener<Object, Type>(object, method);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_METHODLISTENER__
