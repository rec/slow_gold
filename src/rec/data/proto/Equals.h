#ifndef __REC_DATA_PROTO_EQUAL__
#define __REC_DATA_PROTO_EQUAL__

#include "rec/data/proto/Types.h"
#include "rec/data/proto/Comparer.h"

namespace rec {
namespace data {

bool equals(const Message& x, const Message& y, const Comparer& c = Comparer());

}  // namespace data

inline bool operator==(const Message& x, const Message& y) {
  return data::equals(x, y);
}

inline bool operator!=(const Message& x, const Message& y) { return !(x == y); }

}  // namespace rec

#endif  // __REC_DATA_PROTO_EQUAL__
