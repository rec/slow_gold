#ifndef __REC_UTIL_COMPARERANGE__
#define __REC_UTIL_COMPARERANGE__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
Type compare(const Range<Type>& x, const Range<Type>& y) {
  if (Type d = x.begin_ - y.begin_)
    return d;
  else
    return x.end_ - y.end_;
}

template <typename Container, typename Type>
Type doCompareOrdered(const Container& x, const Container& y) {
  typename Container::const_iterator i = x.begin();
  typename Container::const_iterator j = y.begin();

  for (;;) {
    if (i == x.end())
      return (j == y.end()) ? 0 : -1;

    if (j == y.end())
      return 1;

    if (Size c = compare(*i++, *j++))
      return c;
  }
}

template <typename Type>
Type compareOrdered(const typename Range<Type>::Set& x,
                    const typename Range<Type>::Set& y) {
  return doCompareOrdered<Range<Type>::Set, Type>(x, y);
}

template <typename Type>
Type compareOrdered(const typename Range<Type>::Vector& x,
                    const typename Range<Type>::Vector& y) {
  return doCompareOrdered<Range<Type>::Vector, Type>(x, y);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_COMPARERANGE__
