#ifndef __REC_UTIL_UTF8__
#define __REC_UTIL_UTF8__

#include "rec/base/string_piece.h"

namespace rec {
namespace util {
namespace utf8 {

int decode(StringPiece* s, const char** error = NULL);
int encodedLength(int letter);
int encode(int letter, char* out, int length = 0);

// ASCII only right now.
int toLower(int letter);
int toUpper(int letter);

typedef int (*Filter)(int);
int cmp(StringPiece* s1, StringPiece *s2);
int cmp(StringPiece* s1, StringPiece *s2, Filter f);

}  // namespace utf8
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UTF8__
