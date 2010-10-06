#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include "rec/base/base.h"

namespace rec {
namespace proto {

class Operation;

Operation* applyOperation(const Operation& operation, Message* msg);

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_PROTO
