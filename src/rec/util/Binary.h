#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
Type* createBinary(const char* data, int len);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
