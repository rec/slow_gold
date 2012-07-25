#ifndef __REC_UTIL_MERGE__
#define __REC_UTIL_MERGE__

#include "rec/util/range/Contains.h"
#include "rec/util/range/Insert.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type, typename Container>
Container merge(const Container& x, const Container& y) {
  Range<Type>* prev = NULL;
  Container result;
  typename Container::const_iterator i = x.begin(), j = y.begin();

  while (i != x.end() || j != y.end()) {
    bool useX = (j == y.end()) || (i != x.end() && *i < *j);
    const Range<Type>& next = *((useX ? i : j)++);
    if (prev && intersects(*prev, next)) {
      prev->end_ = next.end_;
    } else {
      insertAtEndAndMerge(&result, next);
      prev = const_cast<Range<Type>*>(&*result.rbegin());
    }
  }

  return result;
}

template <typename Type, typename Container>
Container merge(const Container& x, const Range<Type>& y) {
  Container c;
  insertAtEndAndMerge(&c, y);
  return merge<Type, Container>(x, c);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MERGE__
