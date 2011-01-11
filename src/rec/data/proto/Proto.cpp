#include "rec/data/proto/Field.h"
#include "rec/data/proto/Value.h"

namespace rec {
namespace proto {

Operation* applyOperation(const Operation& op, Message* msg) {
  ptr<Field> field(Field::makeField(op.address(), *msg));
  return field ? field->apply(op) : NULL;
}

Value getValue(const Address& address, const Message& msg) {
  Value value;
  ptr<Field> field(Field::makeField(address, msg));
  if (field)
    field->copyTo(&value);

  return value;
}

bool hasValue(const Address& address, const Message& msg) {
  ptr<Field> field(Field::makeField(address, msg));
  return field && field->hasValue();
}

int getSize(const Address& address, const Message& msg) {
  ptr<Field> field(Field::makeField(address, msg));
  return field ? field->getSize() : 0;

}

}  // namespace proto
}  // namespace rec
