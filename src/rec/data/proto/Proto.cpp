#include "rec/data/proto/Field.h"
#include "rec/data/proto/Value.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace proto {

arg::Value ProtoAddress::getValue() const {
  arg::Value value;
  ptr<Field> field(Field::makeField(address_, *proto_));
  if (field)
    field->copyTo(&value);

  return value;
}

bool ProtoAddress::hasValue() const {
  ptr<Field> field(Field::makeField(address_, *proto_));
  return field && field->hasValue();
}

int ProtoAddress::getSize() const {
  ptr<Field> field(Field::makeField(address_, *proto_));
  return field ? field->getSize() : 0;
}

arg::Value getValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getValue();
}

bool hasValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).hasValue();
}

int getSize(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getSize();
}

Operation* applyOperation(const Operation& op, Message* msg) {
  ptr<Field> field(Field::makeField(op.address(), *msg));
  return field ? field->apply(op) : NULL;
}


}  // namespace proto
}  // namespace rec
