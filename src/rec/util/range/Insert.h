#ifndef __REC_UTIL_RANGE_INSERT__
#define __REC_UTIL_RANGE_INSERT__

#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
void insertAtEndAndMerge(typename Range<Type>::Vector* c, const Range<Type>& range) {
  if (c->empty() || c->back().end_ < range.begin_) {
    c->push_back(range);
  } else {
    DCHECK_LE(c->back().begin_, range.begin_);
    c->back().end_ = range.end_;
  }
}


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE_INSERT__
