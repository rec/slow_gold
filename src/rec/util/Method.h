#ifndef __REC_UTIL_METHOD__
#define __REC_UTIL_METHOD__

#include "rec/base/basictypes.h"

namespace rec {
namespace util {

template <typename Type, typename Method>
class Method0 {
 public:
  Method0(Method m) : method_(m) {}

  bool operator()(Type* x) const { return (x->*method_)(); }

 private:
  Method method_;
};

template <typename Type, typename Method, typename A>
class Method1 {
 public:
  Method1(Method m, A a) : method_(m), a_(a) {}

  bool operator()(Type* x) const { return (x->*method_)(a_); }

 private:
  Method method_;
  A a_;
};

template <typename Type, typename Method, typename A, typename B>
class Method2 {
 public:
  Method2(Method m, A a, B b) : method_(m), a_(a), b_(b) {}

  bool operator()(Type* x) const { return (x->*method_)(a_, b_); }

 private:
  Method method_;
  A a_;
  B b_;
};

template <typename Type, typename Method, typename A, typename B, typename C>
class Method3 {
 public:
  Method3(Method m, A a, B b, C c) : method_(m), a_(a), b_(b), c_(c) {}

  bool operator()(Type* x) const { return (x->*method_)(a_, b_, c_); }

 private:
  Method method_;
  A a_;
  B b_;
  C c_;
};

template <typename Type, typename Method>
Method0<Type, Method> getMethod(Method m) {
  return Method0<Type, Method>(m);
}

template <typename Type, typename Method, typename A>
Method1<Type, Method, A> getMethod(Method m, A a) {
  return Method1<Type, Method, A>(m, a);
}

template <typename Type, typename Method, typename A, typename B>
Method2<Type, Method, A, B> getMethod(Method m, A a, B b) {
  return Method2<Type, Method, A, B>(m, a, b);
}

template <typename Type, typename Method, typename A, typename B, typename C>
Method3<Type, Method, A, B, C> getMethod(Method m, A a, B b, C c) {
  return Method3<Type, Method, A, B, C>(m, a, b, c);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_METHOD__
