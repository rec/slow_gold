#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/util/Range.h"

namespace rec {
namespace util {

template <typename Type>
struct Circular : public Range<Type> {
  Type capacity_;

  Circular() : capacity_(0) {}
  explicit Circular(Type c) : Range<Type>(0, 0), capacity_(c) {}
  Circular(Type b, Type e, Type c) : Range<Type>(b, e), capacity_(c) {}

  void consume(Type count) {
    Type available = this->size();
    if (count > available) {
      DLOG(ERROR) << "count: " << count << ", available: " << available;
      DCHECK_LE(count, available);
      count = available;
    }

    this->begin_ += count;
    if (this->begin_ >= capacity_) {
      this->begin_ -= capacity_;
      if (this->end_ >= capacity_)
        this->end_ -= capacity_;
      else
        DLOG(ERROR) << "!" << this->begin_ << ", " << this->end_;
    }

    if (!this->size())
      this->begin_ = this->end_ = 0;
  }

  void fill(Type count) { this->end_ += std::min(count, fillable()); }
  Type fillable() const { return capacity_ - this->size(); }

  Range<Type> fillableBlock() const {
    Type b = this->end_;
    if (b >= capacity_)
      b -= capacity_;
    Type e = std::min(b + fillable(), capacity_);
    return Range<Type>(b, e);
  }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
