#include "rec/data/proto/Field.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/proto/NameToProto.h"

namespace rec {
namespace data {

namespace {

struct ProtoAddress {
  ptr<Field> field_;
  ProtoAddress(Message* p, const Address& a) : field_(Field::makeField(a, *p)) {}
  ProtoAddress(const Message& p, const Address& a)
      : field_(Field::makeField(a, p)) {
  }

  Value getValue() const {
    Value value;
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

Value getValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getValue();
}

bool hasValue(const Address& a, const Message& m) {
  return ProtoAddress(m, a).hasValue();
}

int getSize(const Address& a, const Message& m) {
  return ProtoAddress(m, a).getSize();
}

OperationList* applyOperations(const OperationList& list, Message* m) {
  ptr<OperationList> result (new OperationList());
  for (int i = 0; i < list.operation_size(); ++i) {
    const Operation& op = list.operation(i);
    ptr<Operation> undo(ProtoAddress(m, op.address()).applyOperation(op));
    if (undo)
      result->add_operation()->CopyFrom(*undo);
    else
      LOG(ERROR) << "Couldn't perform operation " << op.ShortDebugString();
  }
  return result.transfer();
}

}  // namespace data
}  // namespace rec
