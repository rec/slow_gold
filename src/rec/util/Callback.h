#ifndef __REC_UTIL_CALLBACK
#define __REC_UTIL_CALLBACK

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Class, typename Method, typename Value>
class Callback {
 public:
  Callback(Class *c, Method m, Value v) : class_(cl), method_(m), value_(v) {}

  void operator()() const { (class_->*method_)(value_); }

 private:
  Class *class_;
  Method method_;
  Value value_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CALLBACK
