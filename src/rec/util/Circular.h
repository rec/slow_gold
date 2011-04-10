#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/util/Range.h"

namespace rec {
namespace util {

template <typename Type>
struct Circular : public Range<Type> {
  Type capacity_;

  Circular() {}
  explicit Circular(Type c) : Range<Type>(0, 0), capacity_(c) {}
  Circular(Type b, Type e, Type c) : Range<Type>(b, e), capacity_(c) {}
  // Circular(const Range<Type>& r, Type c) : Range<Type>(r), capacity_(c) {}

  void consume(Type count) {
    DCHECK_GE(count, 0);

    Type available = this->size();
    if (count > available) {
      LOG(ERROR) << "count=" << count << " > available=" << available;
      count = available;
    }
    boundedIncrement(count, capacity_);
  }

  void fill(Type count) {
    DCHECK_GE(count, 0);

    Type available = capacity_ - this->size();
    if (count > available) {
      LOG(ERROR) << "count=" << count << " > available=" << available;
      count = available;
    }
    this->end_ += count;
  }

  bool isFull() const { return this->size() == capacity_; }

  Range<Type> fillable() const {
    bool crossesZero = (this->end_ >= capacity_);
    return Range<Type>(crossesZero ? (this->end_ - capacity_) : this->end_,
                       crossesZero ? this->begin_ : capacity_);
  }

  Range<Type> consumable() const {
    return Range<Type>(this->begin_, std::min(this->end_, capacity_));
  }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
