#include <glog/logging.h>

#include "rec/util/Utf8.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace util {

#define FAIL_IF(COND, STR)                             \
  if (COND) {                                          \
    if (error)                                         \
      *error = STR;                                    \
    return -1;                                         \
  }

inline int pop(StringPiece* s) { return s->pop() & 0xFF; }

int popUtf8Codepoint(StringPiece* s, const char** error) {
  static const int bits[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04};

  FAIL_IF(s->empty(), "Empty string");

  int cp = pop(s);   // Our codepoint!
  if (cp < bits[0])  // The most common case.
    return cp;

  int len = 1;
  for (; len != arraysize(bits) && (cp & bits[len]); cp &= ~bits[len++]);

  FAIL_IF(len == 1, "Bad UTF-8 prefix 10xxxxxx");
  FAIL_IF(len == 2 && cp <= 1, "Overlong sequence (2)");
  FAIL_IF(len == arraysize(bits), "Bad UTF-8 prefix 1111111x");

  for (int i = 1; i < len; ++i) {
    int ch = pop(s);
    FAIL_IF(!(ch & bits[0]), "Expected continuation");
    FAIL_IF(ch & bits[1], "Bad continuation");

    FAIL_IF(!cp && ch < (bits[0] + bits[i]), "Overlong sequence (n)");
    (cp <<= 6) += (ch & ~bits[0]);
  }

  FAIL_IF(cp >= 0xD800 && cp <= 0xDFFF, "UTF-16 surrogates");
  FAIL_IF(cp >= 0xFFFE && cp <= 0xFFFF, "Forbidden codepoints");

  return cp;
}

}  // namespace util
}  // namespace rec
