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
  }

  void fill(Type count) {
    Type available = capacity_ - this->size();
    if (count > available) {
      DLOG(ERROR) << "count: " << count << ", available: " << available;
      count = available;
    }
    this->end_ += count;
  }

  Range<Type> fillable() const {
    return Range<Type>(this->begin_, std::min(this->end_, capacity_));
  }

#if 0
  void consume(Type count) { fillOrConsume(count, false); }
  void fill(Type count) { fillOrConsume(count, true); }

  Type toFill() const { return (capacity_ - this->size()); }
  bool isFull() const { return !toFill(); }

  Type wrap(Type index) const {
    return  (index > capacity_) ? index - capacity_ : Type();
  }

  Type wrap() const { return wrap(this->end_); }

  Range<Type> fillable() const {
    Type w = wrap();
    return Range<Type>(w ? Type(this->end_ - capacity_) : this->end_,
                       w ? this->begin_ : Type(capacity_));
  }

  Range<Type> consumable() const {
    return Range<Type>(this->begin_, std::min(this->end_, capacity_));
  }

  void fillOrConsume(Type count, bool isFill) {
    DCHECK_GE(count, 0);

    Type available = isFill ? (capacity_ - this->size()) : this->size();
    if (count > available) {
      if (!isFill)
        DCHECK_LE(count, available);
      count = available;
    }

    if (isFill) {
      this->end_ += count;
    } else {
      if (this->end_ >= capacity_)
        this->end_ -= capacity_;
      this->begin_ += count;
      if (this->begin_ >= capacity_) {
        this->begin_ -= capacity_;
        if (this->end_ >= capacity_)
          this->end_ -= capacity_;
        else
          LOG(ERROR) << this->begin_ << "," << this->end_ << "," << capacity_;
      }
    }
  }
#endif
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
