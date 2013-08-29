#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
Type* createBinary(const char* data, size_t len, const string& filename = "");

template <typename Type>
Type* construct(const string&);

#define BINARY_STRING(NAME) \
  string(BinaryData::NAME, BinaryData::NAME ## Size)

#define BINARY_DATA(NAME, TYPE) \
  construct<TYPE>(BINARY_STRING(NAME))

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
