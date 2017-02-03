#pragma once

#include "BinaryData.h"
#include "rec/util/Binary.h"

namespace rec {
namespace util {

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
