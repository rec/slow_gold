#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include <cstdarg>

#include <algorithm>
#include "rec/base/basictypes.h"
#include "rec/proto/Operation.pb.h"
#include "rec/proto/Types.h"
#include "rec/proto/Address.h"
#include "rec/proto/TypedTyper.h"

// useful functions to deal with protocol buffers.

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation, Message* msg);

#if 0
Operation* createOperation(Operation::Command command, ...);

Operation* append(const Address& address);
Operation* clear(const Address& address);
Operation* remove(const Address& address, int count);
Operation* set(const Address& address);
Operation* swap(const Address& address, Tag s1, Tag s2);

template <typename Type>
Operation* addValue(Type t, Operation *op) {
  typer::TypedTyper<Type>::copy(t, op->add_value());
  return op;
}

#endif

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_PROTO
