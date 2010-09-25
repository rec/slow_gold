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

#if 0
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
#endif

}  // namespace proto
}  // namespace rec
