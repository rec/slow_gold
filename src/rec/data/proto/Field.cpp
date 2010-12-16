#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include "rec/data/proto/Field.h"
#include "rec/data/proto/Address.h"
#include "rec/data/proto/Operation.pb.h"
#include "rec/data/proto/Typer.h"
#include "rec/data/proto/Types.h"
#include "rec/data/proto/Value.pb.h"

namespace rec {
namespace proto {

Operation* Field::apply(const Operation &op, Message* message) {
  Field field(message);
  for (int i = 0; i < op.address().field_size(); ++i) {
    if (!field.dereference(op.address().field(i)))
      return NULL;
  }

  return field.apply(op);
}

Value Field::getValue(const Address& address, const Message& msg) {
  Field field(message);
  for (int i = 0; i < address.field_size(); ++i) {
    if (!field.dereference(address.field(i)))
      return Value();
  }

  Value value;
  field.copyTo(&value);
  return value;
}

bool Field::dereference(const proto::Address::Field& afield) {
  if (field_) {
    const Reflection& r = *message_->GetReflection();
    if (type_ == INDEXED) {
      if (field_->type() == FieldDescriptor::TYPE_MESSAGE) {
        message_ = r.MutableRepeatedMessage(message_, field_, index_);
      } else {
        LOG(ERROR) << "Non-terminal field had type " << field_->type();
        return false;
      }

    } else if (type_ == REPEATED) {
      if (!afield.has_index()) {
        LOG(ERROR) << "Repeated has no index ";
        return false;
      }
      int32 index = afield.index();
      if (index >= repeatCount_) {
        LOG(ERROR) << "Index " << index << " out of bounds " << repeatCount_;
        return false;
      }

      type_ = INDEXED;
      index_ = index;
      return true;

    } else {
      message_ = r.MutableMessage(message_, field_);
    }
  }

  if (!afield.has_name()) {
    LOG(ERROR) << "Expected a name at this point";
    return false;
  }

  field_ = message_->GetDescriptor()->FindFieldByName(afield.name());
  if (!field_) {
    LOG(ERROR) << "Could not find field named " << afield.name()
               << " in class named " << message_->GetTypeName();
    return false;
  }
  if (field_->label() == FieldDescriptor::LABEL_REPEATED) {
    type_ = REPEATED;
    repeatCount_ = message_->GetReflection()->FieldSize(*message_, field_);
  } else {
    type_ = SINGLE;
    repeatCount_ = 1;
  }

  return true;
}

bool Field::copyFrom(const Value& value) {
  return (type_ == SINGLE) ? typer::copyFrom(message_, field_, value) :
    typer::copyFrom(message_, field_, index_, value);
}

bool Field::copyTo(Value* value) const {
  return (type_ == SINGLE) ? typer::copyTo(*message_, field_, value) :
    typer::copyTo(*message_, field_, index_, value);
}

bool Field::addFrom(const Value& value) {
  if (field_)
    return typer::add(message_, field_, value);

  LOG(ERROR) << "Can't add to self";
  return false;
}

typedef bool (Field::*Applier)();

Operation* Field::apply(const Operation& op) {
  Operation::Command command = op.command();
  Applier applier = &Field::error;
  if (field_ == NULL)
    type_ = SINGLE;

  if (command >= 0 && command < Operation::COMMAND_COUNT) {
    static Applier appliers[Operation::COMMAND_COUNT][TYPE_COUNT] = {
      {&Field::error,       &Field::addRepeated,     &Field::error},
      {&Field::error,       &Field::clearRepeated,   &Field::clearSingle},
      {&Field::error,       &Field::removeRepeated,  &Field::error},
      {&Field::setIndexed,  &Field::error,           &Field::setSingle},
      {&Field::error,       &Field::swapRepeated,    &Field::error},
    };
    applier = appliers[command][type_];
  }

  operation_ = &op;
  undo_ = new Operation(op);
  undo_->clear_value();
  if ((this->*applier)())
    return undo_;

  delete undo_;
  return NULL;
}

bool Field::error() {
  LOG(ERROR) << "This operation was impossible";
  return false;
}

bool Field::addRepeated() {
  int size = operation_->value_size();
  for (int i = 0; i < size; ++i) {
    if (!addFrom(operation_->value(i)))
      return false;
  }

  undo_->set_command(Operation::REMOVE);
  undo_->set_remove(size);
  return true;
}

bool Field::doRemove(int toRemove) {
  undo_->set_command(Operation::APPEND);

  Field f = *this;
  f.dereference(arg::Address::Field(0));
  if (toRemove < 0)
    toRemove = f.repeatCount_;

  f.index_ = f.repeatCount_ - toRemove;
  for (; f.index_ < f.repeatCount_; ++f.index_) {
    if (!f.copyTo(undo_->add_value()))
      return false;
  }

  return true;
}

bool Field::clearRepeated() {
  return doRemove();
}

bool Field::clearSingle() {
  undo_->set_command(Operation::SET);
  undo_->clear_value();
  return copyTo(undo_->add_value());
}

bool Field::removeRepeated() {
  return doRemove(operation_->remove());
}

bool Field::setSingle() {
  if (operation_->value_size() != 1) {
    LOG(ERROR) << "Can only set one value at a time";
    return false;
  }

  if (!field_ || type_ == INDEXED ||
      message_->GetReflection()->HasField(*message_, field_))
    copyTo(undo_->add_value());
  else
    undo_->set_command(Operation::CLEAR);

  return copyFrom(operation_->value(0));
}


bool Field::swapRepeated() {
  if (!field_) {
    LOG(ERROR) << "Can't swap repeated on self";
    return false;
  }
  message_->GetReflection()->SwapElements(message_, field_,
                                          operation_->swap1(),
                                          operation_->swap2());

  return true;
}

}  // namespace proto
}  // namespace rec
