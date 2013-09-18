#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

#include "BinaryData.h"
#include "rec/util/Binary.pb.h"
#include "rec/util/Copy.h"

namespace rec {
namespace util {

string getNamedResource(const string&);
void binaryProtoMerged(const string&, Message*);

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

template <typename Proto>
Proto binaryProtoMerged(const string& s) {
  Proto p;
  binaryProtoMerged(s, &p);
  return p;
}

template <typename Type>
Type* constructName(const string& name) {
  return construct<Type>(getNamedResource(name));
}

#define BINARY_STRING(NAME) \
  string(BinaryData::NAME, BinaryData::NAME ## Size)

#define BINARY_DATA(NAME, TYPE) \
  construct<TYPE>(BINARY_STRING(NAME))

#define BINARY_PROTO(NAME, PROTO) \
  binaryProto<PROTO>(BINARY_STRING(NAME ## _def))

#define BINARY_PROTO_MERGED(NAME, TYPE) \
  binaryProtoMerged<TYPE>(BINARY_STRING(NAME ## _def))

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
