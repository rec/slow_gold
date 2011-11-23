#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include <set>

#include "rec/base/base.h"

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
  Range(const Set& s) : begin_(s.empty() ? Type(0) : s.begin()->begin_),
                        end_(s.empty() ? Type(0) : s.rbegin()->end_) {
  }

  void clear() { begin_ = end_ = Type(0); }
  Type size() const { return end_ - begin_; }
  bool empty() const { return !size(); }

  bool contains(Type t) const {
    return (begin_ != end_) && (begin_ < end_ ?
                                (begin_ <= t) && (t < end_) :
                                (begin_ <= t) || (t < end_));
  }

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

  const String toString() const {
    return String(begin_) + "-" + String(end_);
  }

 private:
  JUCE_LEAK_DETECTOR(Range);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
