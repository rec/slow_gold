#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include <set>
#include <vector>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
  Type begin_;
  Type end_;

  Range() { clear(); }
  Range(Type b, Type e) : begin_(b), end_(e) { DCHECK_LE(b, e); }

  typedef std::set<Range> Set;
  typedef std::vector<Range> Vector;

  void clear() { begin_ = end_ = Type(0); }
  Type size() const { return end_ - begin_; }
  bool empty() const { return !size(); }

  bool operator<(const Range& x) const {
    return begin_ < x.begin_ || (begin_ == x.begin_ && end_ < x.end_);
  }

  bool operator<=(const Range& x) const { return !(x < *this); }
  bool operator>(const Range& x) const { return x < *this; }
  bool operator>=(const Range& x) const { return x <= *this; }
  bool operator!=(const Range& x) const { return !(x == *this); }

  bool operator==(const Range& x) const {
    return begin_ == x.begin_ && end_ == x.end_;
  }

  const String toString() const {
    return String(begin_) + "-" + String(end_);
  }

 private:
  JUCE_LEAK_DETECTOR(Range);
};

template <typename Type>
Type toY(const Range<Type>& r, Type x, Type ySize) {
  return ySize * (x - r.begin_) / r.size();
}

template <typename Type>
Type toX(const Range<Type>& r, Type y, Type ySize) {
  return r.begin_ + (y * r.size()) / ySize;
}

template <typename Type>
Type compare(const Range<Type>& x, const Range<Type>& y) {
  if (Type d = x.begin_ - y.begin_)
    return d;
  else
    return x.end_ - y.end_;
}

template <typename Type>
typename Range<Type>::Vector split(const Range<Type>& range,
                                   Type capacity) {
  typename Range<Type>::Vector ranges;
  if (range.end_ <= capacity) {
    ranges.push_back(range);
  } else {
    ranges.push_back(Range<Type>(range.begin_, capacity));
    ranges.push_back(Range<Type>(capacity, range.end_));
  }
  return ranges;
}

template <typename Type>
Type restrict(const Range<Type>& r, Type x) {
  return (x < r.begin_) ? r.begin_ : (x > r.end_) ? r.end_ : x;
}

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

template <typename Container, typename Type>
Range<Type> doMakeRange(const Container& c) {
  return Range<Type>(c.empty() ? Type(0) : c.begin()->begin_,
                     c.empty() ? Type(0) : c.rbegin()->end_);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Set& x,
                      const typename Range<Type>::Set& y) {
  return doMakeRange<Range<Type>::Set, Type>(x, y);
}

template <typename Type>
Range<Type> makeRange(const typename Range<Type>::Vector& x,
                      const typename Range<Type>::Vector& y) {
  return doMakeRange<Range<Type>::Vector, Type>(x, y);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
