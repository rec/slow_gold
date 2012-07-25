#ifndef __REC_UTIL_RANGE_INSERT__
#define __REC_UTIL_RANGE_INSERT__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
void insert(typename Range<Type>::Set* container, const Range<Type>& range) {
  container->insert(range);
}

template <typename Type>
void insert(typename Range<Type>::Vector* container, const Range<Type>& range) {
  container->push_back(range);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE_INSERT__
