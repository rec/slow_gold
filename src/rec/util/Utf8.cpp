#include <glog/logging.h>

#include "rec/util/Utf8.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace util {

int popUtf8Codepoint(StringPiece* s) {
  if (s->empty())
    return -1;

  int c = s->pop() & 0xFF;

  static const int PREFIXES[] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8};

  int len = 0;
  for (; len < arraysize(PREFIXES) && (PREFIXES[len] & c); ++len);

  if (len == 0)
    return c;  // Most common case!

  if (len == 1 || len >= arraysize(PREFIXES)) {
    DLOG(ERROR) << "Bad UTF-8 prefix";
    return -1;
  }

  c &= ~PREFIXES[len];

  for (int i = 1; i < len; ++i) {
    int ch = s->pop() & 0xFF;

    static const int CONTINUE = PREFIXES[1];
    if ((ch & CONTINUE) != 0x80) {
      DLOG(ERROR) << "Bad UTF-8 continuation";
      return -1;
    }
    (c <<= 6) += (~CONTINUE & ch);
  }

  return c;
}

}  // namespace util
}  // namespace rec
