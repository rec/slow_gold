#ifndef __REC_UTIL_MATH
#define __REC_UTIL_MATH

#include "rec/base/base.h"
#if !_MSC_VER
	#include <cmath>
#else
	#include <math.h>
#endif

namespace rec {
namespace util {

template <typename Number>
struct Math {
  static Number abs(Number x) { return (x < 0) ? -x : x; }

  // A arithmetic modulus function that's always non-negative.
  // See http://en.wikipedia.org/wiki/Modulo_operation#cite_note-0
  //
  static Number mod(Number dividend, Number divisor) {
    Number modulo = dividend % divisor;
    if (modulo < 0)
      modulo += abs(divisor);
    return modulo;
  }

  static Number absoluteDifference(Number x, Number y) {
    return (x > y) ? (x - y) : (y - x);
  }
  static bool near(Number x, Number y, Number diff) {
    return absoluteDifference(x, y) <= diff;
  }
};

template <typename Number>
Number abs(Number x) { return Math<Number>::abs(x); }

template <typename Number, typename N1>
Number mod(Number p, N1 q) { return Math<Number>::mod(p, Number(q)); }

template <typename Number, typename N2, typename N3>
Number near(Number x, N2 y, N3 diff) {
  return Math<Number>::near(x, y, diff);
}



inline int isinf( float arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return (!_finite(arg));
#endif
}

inline int isinf( double arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return (!_finite(arg));
#endif
}

inline int isnan( float arg ) {
#if !_MSC_VER
	return std::isnan(arg);
#else
	return _isnan(arg);
#endif
}

inline int isnan( double arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return _isnan(arg);
#endif
}


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MATH
