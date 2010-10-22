#ifndef __REC_UTIL_UTF8__
#define __REC_UTIL_UTF8__

#include "rec/base/string_piece.h"

namespace rec {
namespace util {
namespace utf8 {

int decode(StringPiece* s, const char** error = NULL);
int encodedLength(int letter);
int encode(int letter, char* out, int length = 0);

const char* skip(const char* s, int letters, const char** error = NULL);

typedef int (*Filter)(int);

// Returns 0 if the two string pieces compare the same as UTF-8.  Returns a
// negative value if s1 is less than s2, positive if s1 is greater than s2, and
// the magnitude is the UTF-8 position that the files differ at.
int cmp(const StringPiece& s, const StringPiece& t);
int cmpi(const StringPiece& s, const StringPiece& t);

int cmp(const String& s, const String& t);
int cmpi(const String& s, const String& t);

}  // namespace utf8
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UTF8__
