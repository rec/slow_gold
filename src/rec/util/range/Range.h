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

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
