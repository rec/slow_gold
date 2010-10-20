#include <glog/logging.h>

#include "rec/util/Utf8.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace util {
namespace utf8 {
namespace {

inline int pop(StringPiece* s) { return s->pop() & 0xFF; }

const int BIT[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
int BOUNDS[] = {0x80, 0x800, 0x10000, 0x200000, 0x4000000};

inline const char* checkCodepoint(int cp) {
  if (cp >= 0xD800 && cp <= 0xDFFF)
    return "UTF-16 surrogate";

  if (cp >= 0xFFFE && cp <= 0xFFFF)
    return "Forbidden codepoint";

  if (cp < 0 || cp & 0x80000000)  // same condition?
    return "Negative codepoint";

  return NULL;
}

}  // namespace


#define FAIL_IF(COND, STR)                             \
  if (COND) {                                          \
    if (error)                                         \
      *error = STR;                                    \
    return -1;                                         \
  }

int decode(StringPiece* s, const char** error) {
  FAIL_IF(s->empty(), "Empty string");

  int cp = pop(s);   // Our codepoint!
  if (cp < BIT[0])  // The most common case.
    return cp;

  int len = 0;
  for (; len != arraysize(BIT) && (cp & BIT[len]); cp -= BIT[len++]);

  FAIL_IF(len == 1, "Bad UTF-8 prefix 10xxxxxx");
  FAIL_IF(len == 2 && cp <= 1, "Overlong sequence (2)");
  FAIL_IF(len > 6, "Bad UTF-8 prefix 1111111x");

  for (int i = 1; i < len; ++i) {
    int ch = pop(s);
    FAIL_IF(!(ch & BIT[0]), "Expected continuation");
    FAIL_IF(ch & BIT[1], "Bad continuation");

    FAIL_IF(!cp && ch < (BIT[0] + BIT[i]), "Overlong sequence (n)");
    (cp <<= 6) += (ch - BIT[0]);
  }

  FAIL_IF(const char* e = checkCodepoint(cp), e);
  return cp;
}

int encodedLength(int cp) {
  for (int i = 0; ; ++i)
    if (i >= arraysize(BOUNDS) || cp < BOUNDS[i])
      return i + 1;
}

int encode(int cp, char* out, int length) {
  if (checkCodepoint(cp))
    return 0;

  if (cp < BIT[0]) {
    *out = cp;
    return 1;
  }

  if (!length)
    length = encodedLength(cp);

  out[0] = BIT[0];
  for (int i = length - 1; i > 0;  --i) {
    out[0] += BIT[i];
    out[i] = BIT[0] + (cp & 0x3F);
    cp >>= 6;
  }
  DCHECK_LT(cp, BIT[length]);
  out[0] += cp;
  return length;
}

}  // namespace utf8
}  // namespace util
}  // namespace rec
