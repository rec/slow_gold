#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include <set>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
  typedef std::set<Range> Set;

  Range() {}
  Range(Type b) : begin_(b), end_(b + 1) {}
  Range(Type b, Type e) : begin_(b), end_(e) {}
  Range(const Set& s) : begin_(s.empty() ? 0 : s.begin()->begin_),
                        end_(s.empty() ? 0 : s.rbegin()->end_) {
  }

  Type size() const { return end_ - begin_; }

  Type toY(Type x, Type ySize) const { return ySize * (x - begin_) / size(); }
  Type toX(Type y, Type ySize) const { return begin_ + (y * size()) / ySize; }

  bool operator==(const Range& x) const {
    return begin_ == x.begin_ && end_ == x.end_;
  }

  bool operator<(const Range& x) const {
    return begin_ < x.begin_ || (begin_ == x.begin_ && end_ < x.end_);
  }

  bool operator<=(const Range& x) const { return !(x < *this); }
  bool operator>(const Range& x) const { return x < *this; }
  bool operator>=(const Range& x) const { return x <= *this; }
  bool operator!=(const Range& x) const { return !(x == *this); }

  Type begin_;
  Type end_;
};

typedef Range<double> TimeRange;
typedef Range<int64> SampleRange;
typedef TimeRange::Set SelectionRange;


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
