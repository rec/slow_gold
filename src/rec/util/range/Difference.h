#ifndef __REC_UTIL_DIFFERENCE__
#define __REC_UTIL_DIFFERENCE__

#include "rec/util/range/Insert.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type, typename Container>
Container difference(const Range<Type>& block, const Container& s) {
  Container diff;
  SampleRange b = block;
  typename Container::const_iterator i;
  for (i = s.begin(); i != s.end() && b.size() && b.end_ > i->begin_; ++i) {
    if (b.begin_ < i->end_) {
      if (b.begin_ < i->begin_) {
        insert(&diff, SampleRange(b.begin_, i->begin_));
        b.begin_ = i->begin_;
      }

      if (b.end_ > i->begin_) {
        if (b.end_ <= i->end_)
          b.end_ = i->end_;
      }
      b.begin_ = i->end_;
    }
  }

  if (b.size() > 0)
    insert(&diff, b);

  return diff;
}

template <typename Type, typename Container>
SampleRange firstEmptyRangeAfter(const Container& s, int64 pos, int64 length) {
  Container diff = difference(SampleRange(pos, length), s);
  if (diff.empty())
    diff = difference(SampleRange(0, pos), s);

  return diff.empty() ? SampleRange(pos, pos) : *diff.begin();
}

#if 0
template <typename Container, typename Type>
Container difference(const Container& x, const Container& y) {
  Container result;
  for (iterator i = x.begin(), j = y.begin(); i != x.end(); ++i) {
    for (; j != y.end() && j->end_ <= i->begin_; ++j);
    SampleRange b = *i;
    for (; j != y.end() && j->begin_ < i->end_; ++j) {
      if (i->begin_ < j->begin_)
        result.insert(SampleRange(b.begin_, j->begin_));
      b.begin_ = j->end_;
    }
    if (b.size()) > 0)
      result.insert(b);
  }

  return result;
}


template <typename Container, typename Type>
Container symmetricDifference(const Container& x, const Container& y) {
  return merge(difference(x, y), difference(y, x));
}

#endif

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DIFFERENCE__
