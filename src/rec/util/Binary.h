#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
Type* createBinary(const char* data, size_t len, const string& filename = "");

template <typename Type>
Type* juceBinary(const char* resourceName);
string binaryString(const char* resourceName);

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
