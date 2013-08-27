#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
Type* createBinary(const char* data, size_t len, const string& filename = "");

template <typename Type>
Type* construct(const char*, int len);

template <typename Type>
Type* juceBinary(const char* resourceName) {
  int size;
  const char* resource = BinaryData::getNamedResource(resourceName, size);
  return construct<Type>(resource, size);
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
