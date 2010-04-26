#ifndef __BASE_STRING_RANGE_
#define __BASE_STRING_RANGE_

#include "rec/base/basictypes.h"

namespace rec {
namespace util {

class StringRange {
 public:
  StringRange(const char* begin, const char* end) : begin_(begin), end_(end) {}
  StringRange(const char* begin, int64 s) : begin_(begin), end_(begin + s) {}
  StringRange(const char* s) : begin_(s), end_(s ? s + strlen(s) : 0) {}
  StringRange() : begin_((const char*) this), end_((const char*) this) {}

  bool empty() const { return begin_ == end_; }
  char pop() { return empty() ? 0 : *(begin_++); }
  char top() const { return empty() ? 0 : *begin_; }

  // top() and pop() are only defined if empty() is false.

  template <typename Predicate>
  void skip(Predicate predicate) {
    for (; !empty() && predicate(top()); pop());
  }

 protected:
  const char* begin_;
  const char* end_;
};

}  // namespace util
}  // namespace rec

#endif  // __BASE_STRING_RANGE_
