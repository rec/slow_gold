#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include <set>

#include "rec/util/block/Block.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
  Type begin_;
  Type end_;

  Range() { clear(); }
  Range(Type b) : begin_(b), end_(b + 1) {}
  Range(Type b, Type e) : begin_(b), end_(e) {}

  typedef std::set<Range> Set;
  typedef std::vector<Range> Vector;

  Range(const Set& s) : begin_(s.empty() ? Type(0) : s.begin()->begin_),
                        end_(s.empty() ? Type(0) : s.rbegin()->end_) {
  }

  Range(const Vector& s) : begin_(s.empty() ? Type(0) : s.front()->begin_),
                           end_(s.empty() ? Type(0) : s.back()->end_) {
  }


  void clear() { begin_ = end_ = Type(0); }
  Type size() const { return end_ - begin_; }
  bool empty() const { return !size(); }

  Type restrict(Type x) const {
    return (x < begin_) ? begin_ : (x > end_) ? end_ : x;
  }

  Type toY(Type x, Type ySize) const { return ySize * (x - begin_) / size(); }
  Type toX(Type y, Type ySize) const { return begin_ + (y * size()) / ySize; }

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

  Range<Type> reversed() const { return Range<Type>(end_, begin_); }

  Range<Type> inverse(Type capacity) const {
    Range<Type> r((end_ < capacity) ? end_ : end_ - capacity, begin_);
    if (r.begin_ >= capacity)
      r.begin_ -= capacity;

    if (r.begin_ > r.end_)
      r.end_ += capacity;

    return r;
  }

  vector<Range<Type> > split(Type capacity) {
    vector<Range<Type> > ranges;
    if (end_ <= capacity) {
      ranges.push_back(*this);
    } else {
      ranges.push_back(Range<Type>(begin_, capacity));
      ranges.push_back(Range<Type>(capacity, end_));
    }
    return ranges;
  }

  Type compare(const Range<Type>& that) {
    if (Type d = this->begin_ - that->begin_)
      return d;
    else
      return this->end_ - that->end_;
  }

  const String toString() const {
    return String(begin_) + "-" + String(end_);
  }

 private:
  JUCE_LEAK_DETECTOR(Range);
};

template <typename Type>
bool contains(const Range<Type>& r, Type t) {
  // TODO: wait - do ranges wrap around...??
  return (r.begin_ != r.end_) && (r.begin_ < r.end_ ?
                                  (r.begin_ <= t) && (r.t < r.end_) :
                                  (r.begin_ <= t) || (r.t < r.end_));
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

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
