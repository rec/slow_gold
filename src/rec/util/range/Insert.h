#ifndef __REC_UTIL_RANGE_INSERT__
#define __REC_UTIL_RANGE_INSERT__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
void insertRange(typename Range<Type>::Vector* c, const Range<Type>& range) {
  DCHECK_GT(range.size(), 0);
  c->push_back(range);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE_INSERT__
