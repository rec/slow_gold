#ifndef __REC_PROTO_PROTO
#define __REC_PROTO_PROTO

#include <cstdarg>

#include <algorithm>
#include "rec/base/basictypes.h"
#include "rec/proto/Proto.pb.h"
#include "rec/proto/Types.h"

// useful functions to deal with protocol buffers.

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation,
                          Message* msg);

Operation* createOperation(Operation::Command command, ...);

#if 0
Operation* make(Command c);
Operation* make(Command c, uint32 t1);
Operation* make(Command c, uint32 t1, uint32 t2);
Operation* make(Command c, uint32 t1, uint32 t2, uint32 t3);

template <typename Item>
Operation* addValue(Operation* op, Item item, FieldType type = GetType::TYPE);


template <typename Iter>
Operation* add(Iter begin, Iter end, FieldType type, Operation* op) {
  for (; begin != end; ++begin)
    op = add(op, *begin);

  return op;
}
Operation* newOperation(Operation::Command command, const IntList& list);

#endif

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_PROTO
