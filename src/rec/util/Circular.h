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

  void consume(Type count) { fillOrConsume(count, capacity_, false); }
  void fill(Type count) { fillOrConsume(count, capacity_, true); }

  Type toFill() const { return (capacity_ - this->size()); }
  bool isFull() const { return !toFill(); }

#if 1
  Type wrap() const { 
    return  (this->end_ < capacity_) ? this->end_ - capacity_ : 0; 
  }

  Range<Type> fillable() const {
    return Range<Type>(wrap() ? (this->end_ - capacity_) : this->end_,
                       wrap() ? this->begin_ : capacity_);
  }

  Range<Type> consumable() const {
    return Range<Type>(this->begin_, std::min(this->end_, capacity_));
  }

#endif
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
