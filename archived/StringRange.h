#ifndef __BASE_STRING_RANGE_
#define __BASE_STRING_RANGE_

#include <string.h>

namespace rec {
namespace util {

class StringRange {
 public:
  StringRange(const char* begin, const char* end) : begin_(begin), end_(end) {}
  StringRange(const char* begin, long long s) : begin_(begin), end_(begin + s) {}
  StringRange(const char* s) : begin_(s), end_(s ? s + strlen(s) : 0) {}
  StringRange() : begin_((const char*) this), end_((const char*) this) {}

  bool empty() const { return (begin_ == end_); }
  char pop() { return empty() ? 0 : *(begin_++); }
  const char& top() const { return *begin_; }

  // top() and pop() are only defined if empty() is false.
  int cmp(const char* s) const { return strncmp(begin_, s, end_ - begin_); }

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
