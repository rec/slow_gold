#pragma once

#include "rec/util/range/Merge.h"
#include "rec/util/range/Range.h"
#include "rec/util/range/Merge.h"

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
        mergeAtEnd(&diff, SampleRange(b.begin_, i->begin_));
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
    mergeAtEnd(&diff, b);

  return diff;
}

template <typename Type, typename Container>
SampleRange firstEmptyRangeAfter(const Container& s, int64 pos, int64 length) {
  Container diff = difference(Range<Type>(pos, length), s);
  if (diff.empty())
    diff = difference(Range<Type>(0, pos), s);

  for (typename Container::const_iterator i = diff.begin(); ; ++i) {
    if (i == diff.end())
      return Range<Type>(pos, pos);
    if (i->size())
      return *i;
    else {
      LOG_FIRST_N(ERROR, 4) << "Found an empty diff";
    }
  }
}

template <typename Type, typename Container>
Container difference(const Container& x, const Container& y) {
  Container result;
  typename Container::const_iterator i, j;
  for (i = x.begin(), j = y.begin(); i != x.end(); ++i) {
    for (; j != y.end() && j->end_ <= i->begin_; ++j);
    Range<Type> b = *i;
    for (; j != y.end() && j->begin_ < i->end_; ++j) {
      if (i->begin_ < j->begin_)
        mergeAtEnd(&result, SampleRange(b.begin_, j->begin_));
      b.begin_ = j->end_;
    }
    if (b.size() > 0)
      mergeAtEnd(&result, b);
  }

  return result;
}

template <typename Type, typename Container>
Container symmetricDifference(const Container& x, const Container& y) {
  return merge<Type>(difference<Type>(x, y), difference<Type>(y, x));
}

}  // namespace util
}  // namespace rec

