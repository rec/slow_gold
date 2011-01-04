#include "rec/data/proto/Field.h"
#include "rec/data/proto/Value.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& operation, Message* msg) {
  return Field::apply(operation, msg);
}

Value getValue(const Address& address, const Message& msg) {
  return Field::getValue(address, msg);
}

bool hasValue(const Address& address, const Message& msg) {
  return Field::hasValue(address, msg);
}

}  // namespace proto
}  // namespace rec
