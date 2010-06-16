#ifndef __REC_UTIL_CALLBACK
#define __REC_UTIL_CALLBACK

namespace rec {
namespace util {

// A simple callback interface.
class Callback {
 public:
  virtual void operator()() = 0;
};

// A templated class that calls a method on an object.
template <typename Class, typename Method, typename Value>
class MethodCallback {
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
