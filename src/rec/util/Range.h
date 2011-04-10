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
  Range(const Set& s) : begin_(s.empty() ? 0 : s.begin()->begin_),
                        end_(s.empty() ? 0 : s.rbegin()->end_) {
  }

  void clear() { begin_ = end_ = 0; }
  Type size() const { return end_ - begin_; }

  bool contains(Type t) const {
    return (begin_ != end_) && (begin_ < end_ ?
                                (begin_ <= t) && (t < end_) :
                                (begin_ <= t) || (t < end_));
  }

  Type toY(Type x, Type ySize) const { return ySize * (x - begin_) / size(); }
  Type toX(Type y, Type ySize) const { return begin_ + (y * size()) / ySize; }

  bool operator==(const Range& x) const {
    return begin_ == x.begin_ && end_ == x.end_;
  }

  bool operator<(const Range& x) const {
    return begin_ < x.begin_ || (begin_ == x.begin_ && end_ < x.end_);
  }

  void boundedIncrement(Type count, Type capacity) {
    begin_ += count;
    if (begin_ > capacity) {
      begin_ -= capacity;
      if (end_ > capacity) {
        end_ -= capacity;
      } else {
        LOG(ERROR) << begin_ << "," << end_ << "," << capacity;
      }
    }
  }

  bool operator<=(const Range& x) const { return !(x < *this); }
  bool operator>(const Range& x) const { return x < *this; }
  bool operator>=(const Range& x) const { return x <= *this; }
  bool operator!=(const Range& x) const { return !(x == *this); }
};

typedef int64 SampleTime;

typedef Range<double> TimeRange;
typedef Range<SampleTime> SampleRange;
typedef TimeRange::Set SelectionRange;

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
