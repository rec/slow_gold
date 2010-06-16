#ifndef __REC_UTIL_MATH
#define __REC_UTIL_MATH

namespace rec {
namespace util {

template <typename Number> Number abs(Number x) { return (x < 0) ? -x : x; }

// A arithmetic modulus function that's always non-negative.
// See http://en.wikipedia.org/wiki/Modulo_operation#cite_note-0
//
template <typename Number>
inline Number mod(Number dividend, Number divisor) {
  Number modulo = dividend % divisor;
  return (modulo < 0) ? (modulo + abs(divisor)) : modulo;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MATH
