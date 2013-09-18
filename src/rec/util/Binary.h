#ifndef __REC_UTIL_BINARY__
#define __REC_UTIL_BINARY__

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

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BINARY__
