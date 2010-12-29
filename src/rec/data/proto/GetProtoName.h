#ifndef __REC_DATA_PROTO_GETPROTONAME__
#define __REC_DATA_PROTO_GETPROTONAME__

#include "rec/base/base.h"

namespace rec {
namespace data {
namespace proto {

const string& getName(const Message& m);

template <typename Proto>
const string& getName() {
  return getName(Proto::default_instance());
}

}  // namespace proto
}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PROTO_GETPROTONAME__
