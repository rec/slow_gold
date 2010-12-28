#ifndef __REC_UTIL_METHOD__
#define __REC_UTIL_METHOD__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type, typename M>
class Method0 {
 public:
  Method0(M m) : method_(m) {}

  bool operator()(Type* x) const { return (x->*method_)(); }

 private:
  M method_;
};

template <typename Type, typename M, typename A>
class Method1 {
 public:
  Method1(M m, A a) : method_(m), a_(a) {}

  bool operator()(Type* x) const { return (x->*method_)(a_); }

 private:
  M method_;
  A a_;
};

template <typename Type, typename M, typename A, typename B>
class Method2 {
 public:
  Method2(M m, A a, B b) : method_(m), a_(a), b_(b) {}

  bool operator()(Type* x) const { return (x->*method_)(a_, b_); }

 private:
  M method_;
  A a_;
  B b_;
};

template <typename Type, typename M, typename A, typename B, typename C>
class Method3 {
 public:
  Method3(M m, A a, B b, C c) : method_(m), a_(a), b_(b), c_(c) {}

  bool operator()(Type* x) const { return (x->*method_)(a_, b_, c_); }

 private:
  M method_;
  A a_;
  B b_;
  C c_;
};

template <typename Type>
struct Method {
  template <typename M>
  static Method0<Type, M> get(M m) {
    return Method0<Type, M>(m);
  }

  template <typename M, typename A>
  static Method1<Type, M, A> get(M m, A a) {
    return Method1<Type, M, A>(m, a);
  }

  template <typename M, typename A, typename B>
  static Method2<Type, M, A, B> get(M m, A a, B b) {
    return Method2<Type, M, A, B>(m, a, b);
  }

  template <typename M, typename A, typename B, typename C>
  static Method3<Type, M, A, B, C> get(M m, A a, B b, C c) {
    return Method3<Type, M, A, B, C>(m, a, b, c);
  }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_METHOD__
