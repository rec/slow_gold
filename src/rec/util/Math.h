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
    return (modulo < 0) ? (modulo + abs(divisor)) : modulo;
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

template <typename Number>
Number mod(Number p, Number q) { return Math<Number>::mod(p, q); }

template <typename Number>
Number near(Number x, Number y, Number diff) {
  return Math<Number>::near(x, y, diff);
}



int isinf( float arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return (!_finite(arg));
#endif
}

int isinf( double arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return (!_finite(arg));
#endif
}

int isnan( float arg ) {
#if !_MSC_VER
	return std::isnan(arg);
#else
	return _isnan(arg);
#endif
}

int isnan( double arg ) {
#if !_MSC_VER
	return std::isinf(arg);
#else
	return _isnan(arg);
#endif
}


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MATH
