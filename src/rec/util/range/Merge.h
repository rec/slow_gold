#pragma once

#include "rec/util/range/Contains.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace util {

template <typename Type>
void mergeAtEnd(typename Range<Type>::Vector* c, const Range<Type>& r) {
  if (c->empty() || c->back().end_ < r.begin_ || c->back().begin_ > r.begin_)
    c->push_back(r);
  else
    c->back().end_ = r.end_;
}

template <typename Type, typename Container>
Container merge(const Container& x, const Container& y) {
  Range<Type>* prev = nullptr;
  Container result;
  typename Container::const_iterator i = x.begin(), j = y.begin();

  while (i != x.end() || j != y.end()) {
    bool useX = (j == y.end()) || (i != x.end() && *i < *j);
    const Range<Type>& next = *((useX ? i : j)++);
    if (prev && intersects(*prev, next)) {
      prev->end_ = next.end_;
    } else {
      mergeAtEnd(&result, next);
      prev = const_cast<Range<Type>*>(&*result.rbegin());
    }
  }

  return result;
}

template <typename Type, typename Container>
Container merge(const Container& x, const Range<Type>& y) {
  Container c;
  mergeAtEnd(&c, y);
  return merge<Type, Container>(x, c);
}

}  // namespace util
}  // namespace rec

