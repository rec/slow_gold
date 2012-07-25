#ifndef __REC_UTIL_DIFFERENCE__
#define __REC_UTIL_DIFFERENCE__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Container, typename Type>
Container difference(const Block& block, const Container& s) {
  Container diff;
  Block b = block;
  iterator i;
  for (i = s.begin(); i != s.end() && getSize(b) && b.second > i->first; ++i) {
    if (b.first < i->second) {
      if (b.first < i->first) {
        diff.insert(Block(b.first, i->first));
        b.first = i->first;
      }

      if (b.second > i->first) {
        if (b.second <= i->second)
          b.second = i->second;
      }
      b.first = i->second;
    }
  }

  if (getSize(b) > 0)
    diff.insert(b);

  return diff;
}

template <typename Container, typename Type>
Container difference(const Container& x, const Container& y) {
  Container result;
  for (iterator i = x.begin(), j = y.begin(); i != x.end(); ++i) {
    for (; j != y.end() && j->second <= i->first; ++j);
    Block b = *i;
    for (; j != y.end() && j->first < i->second; ++j) {
      if (i->first < j->first)
        result.insert(Block(b.first, j->first));
      b.first = j->second;
    }
    if (getSize(b) > 0)
      result.insert(b);
  }

  return result;
}

template <typename Container, typename Type>
Block firstEmptyBlockAfter(const Container& s, int64 pos, int64 length) {
  Container diff = difference(Block(pos, length), s);
  if (diff.empty())
    diff = difference(Block(0, pos), s);

  return diff.empty() ? Block(pos, pos) : *diff.begin();
}

template <typename Container, typename Type>
Container symmetricDifference(const Container& x, const Container& y) {
  return merge(difference(x, y), difference(y, x));
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DIFFERENCE__
