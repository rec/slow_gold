#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "BinaryData.h"

#include "rec/util/Copy.h"

namespace rec {
namespace util {

template <typename Type>
Type* createBinary(const char* data, size_t len, const string& filename = "");

template <typename Type>
Type* construct(const string&);

template <typename Proto>
Proto binaryProto(const string& s) {
  Proto p;
  copy::copy(s, &p);
  return p;
}

template <typename Type>
Type* constructName(const string& name) {
  int dataSizeInBytes;
  const char* resource = BinaryData::getNamedResource(name.c_str(), dataSizeInBytes);
  return construct<Type>(string(resource, dataSizeInBytes));
}

#define BINARY_STRING(NAME) \
  string(BinaryData::NAME, BinaryData::NAME ## Size)

#define BINARY_DATA(NAME, TYPE) \
  construct<TYPE>(BINARY_STRING(NAME))

#define FILL_BINARY_PROTO(NAME, PROTO) \
  copy::copy(BINARY_STRING(NAME), PROTO)

#define BINARY_PROTO(NAME, PROTO) \
  binaryProto<PROTO>(BINARY_STRING(NAME ## _def))

#define BINARY_FILL(NAME, PROTO) \
  copy:copy(BINARY_STRING(NAME), PROTO)

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
