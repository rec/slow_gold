#ifndef __REC_UTIL_MAKERANGE__
#define __REC_UTIL_MAKERANGE__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Container, typename Type>
Range<Type> doMakeRange(const Container& c) {
  return Range<Type>(c.empty() ? Type(0) : c.begin()->begin_,
                     c.empty() ? Type(0) : c.rbegin()->end_);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Set& x,
                      const typename Range<Type>::Set& y) {
  return doMakeRange<Range<Type>::Set, Type>(x, y);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Vector& x,
                      const typename Range<Type>::Vector& y) {
  return doMakeRange<Range<Type>::Vector, Type>(x, y);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MAKERANGE__
