#ifndef __REC_UTIL_UTF8__
#define __REC_UTIL_UTF8__

#include "rec/base/string_piece.h"

namespace rec {
namespace util {

int popUtf8Codepoint(StringPiece* s);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_UTF8__
