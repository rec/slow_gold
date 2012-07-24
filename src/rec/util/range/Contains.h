#ifndef __REC_UTIL_CONTAINS__
#define __REC_UTIL_CONTAINS__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
bool contains(const Range<Type>& r, Type t) {
  return r.begin_ <= t && t < r.end_;
}

template <typename Container, typename Type>
bool contains(const Container& c, Type x) {
  for (typename Container::const_iterator i = c.begin(); i != c.end(); ++i) {
    if (contains(*i, x))
      return true;
  }

  return false;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CONTAINS__
