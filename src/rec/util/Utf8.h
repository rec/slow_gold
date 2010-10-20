#ifndef __REC_UTIL_UTF8__
#define __REC_UTIL_UTF8__

#include "rec/base/string_piece.h"

namespace rec {
namespace util {
namespace utf8 {

int decode(StringPiece* s, const char** error = NULL);
int encodedLength(int codepoint);
int encode(int codepoint, char* out, int length = 0);

}  // namespace utf8
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UTF8__
