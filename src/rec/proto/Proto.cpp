#include <glog/logging.h>

#include "rec/base/scoped_ptr.h"
#include "google/protobuf/descriptor.h"
#include "rec/proto/Proto.h"
#include "rec/proto/Field.h"
#include "rec/proto/TypedTyper.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation,
                          google::protobuf::Message* msg) {
  return Field::apply(operation, msg);
}

Operation* createOperation(Operation::Command command, ...) {
  Operation *op = new Operation();
  op->set_command(command);

  va_list ap;
  va_start(ap, command);

  for (uint32 addr = va_arg(ap, uint32); addr; addr = va_arg(ap, uint32))
    op->add_address(addr);

  return op;
}

Operation* operation(Operation::Command command, const Address& address) {
  Operation *op = new Operation();
  op->set_command(command);
  return address.addToOperation(op);
}

Operation* append(const Address& address) {
  return operation(Operation::APPEND, address);
}

Operation* clear(const Address& address) {
  return operation(Operation::CLEAR, address);
}

Operation* remove(const Address& address, int removeCount) {
  Operation* op = operation(Operation::CLEAR, address);
  op->set_remove(removeCount);
  return op;
}

Operation* set(const Address& address) {
  return operation(Operation::SET, address);
}

Operation* swap(const Address& address, Tag s1, Tag s2) {
  Operation* op = operation(Operation::SWAP, address);
  op->set_swap1(s1);
  op->set_swap2(s2);
  return op;
}

#if 0
// TODO: consolidate this with TypedTyper and make it vanish...
template <> Operation* addValue<double>(double t, Operation* op);
template <> Operation* addValue<float>(float t, Operation* op);
template <> Operation* addValue<int64>(int64 t, Operation* op);
template <> Operation* addValue<uint64>(uint64 t, Operation* op);
template <> Operation* addValue<int32>(int32 t, Operation* op);
template <> Operation* addValue<uint32>(uint32 t, Operation* op);
template <> Operation* addValue<bool>(bool t, Operation* op);
template <> Operation* addValue<string>(string t, Operation* op);
template <> Operation* addValue<bytes>(bytes t, Operation* op);
template <> Operation* addValue<fixed32>(fixed32 t, Operation* op);
template <> Operation* addValue<fixed64>(fixed64 t, Operation* op);
template <> Operation* addValue<sfixed32>(sfixed32 t, Operation* op);
template <> Operation* addValue<sfixed64>(sfixed64 t, Operation* op);
template <> Operation* addValue<sint32>(sint32 t, Operation* op);
template <> Operation* addValue<sint64>(sint64 t, Operation* op);
template <> Operation* addValue<pmessage>(pmessage t, Operation* op);
template <> Operation* addValue<penum>(penum t, Operation* op);
#endif
}  // namespace proto
}  // namespace rec
