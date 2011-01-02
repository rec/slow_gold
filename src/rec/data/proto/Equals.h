#ifndef __REC_DATA_PROTO_EQUAL__
#define __REC_DATA_PROTO_EQUAL__

#include "rec/data/proto/Types.h"
#include "rec/data/proto/Comparer.h"

namespace rec {
namespace proto {

bool equals(const Message& x, const Message& y, const Comparer& c = Comparer());

}  // namespace proto

inline bool operator==(const Message& x, const Message& y) {
  return proto::equals(x, y);
}

inline bool operator!=(const Message& x, const Message& y) { return !(x == y); }

}  // namespace rec

#endif  // __REC_DATA_PROTO_EQUAL__
