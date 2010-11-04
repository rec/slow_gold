#ifndef __REC_UTIL_BEGINEND__
#define __REC_UTIL_BEGINEND__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
struct BeginEnd {
  BeginEnd() {}
  BeginEnd(Type b, Type e) : begin_(b), end_(e) {}

  Type begin_;
  Type end_;

  int size() const { return end_ - begin_; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BEGINEND__
