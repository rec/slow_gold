#include "rec/data/proto/Field.h"
#include "rec/data/proto/Value.h"
#include "rec/data/proto/Proto.h"

namespace rec {
namespace proto {

namespace {

struct ProtoAddress {
  ptr<Field> field_;
  ProtoAddress(Message* p, const Address& a) : field_(Field::makeField(a, *p)) {}
  ProtoAddress(const Message& p, const Address& a)
      : field_(Field::makeField(a, p)) {
  }

  arg::Value getValue() const {
    arg::Value value;
    if (field_)
      field_->copyTo(&value);

    return value;
  }

  bool hasValue() const {
    return field_ && field_->hasValue();
  }

  int getSize() const {
    return field_ ? field_->getSize() : 0;
  }

  Operation* applyOperation(const Operation& op) {
    return field_ ? field_->apply(op) : NULL;
  }
};

}  // namespace

arg::Value getValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getValue();
}

bool hasValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).hasValue();
}

int getSize(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getSize();
}

Operation* applyOperation(const Operation& op, Message* m) {
  return ProtoAddress(m, op.address()).applyOperation(op);
}

}  // namespace proto
}  // namespace rec
