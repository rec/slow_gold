#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include "rec/proto/Field.h"
#include "rec/base/scoped_ptr.h"
#include "rec/proto/Proto.h"
#include "rec/proto/Typer.h"
#include "rec/proto/Types.h"

namespace rec {
namespace proto {

Operation* Field::apply(const Operation &op, Message* message) {
  Field field(message);
  for (const int32* i = op.address().begin(); i != op.address().end(); ++i) {
    if (!field.dereference(*i))
      return NULL;
  }

  return field.apply(op);
}

bool Field::dereference(int32 tag) {
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
      if (tag >= repeatCount_) {
        LOG(ERROR) << "Index " << tag << " out of bounds " << repeatCount_;
        return false;
      }
      type_ = INDEXED;
      index_ = tag;
      return true;

    } else {
      message_ = r.MutableMessage(message_, field_);
    }
  }

  field_ = message_->GetDescriptor()->FindFieldByNumber(tag);
  if (field_->label() == FieldDescriptor::LABEL_REPEATED) {
    type_ = REPEATED;
    repeatCount_ = message_->GetReflection()->FieldSize(*message_, field_);
  } else {
    type_ = SINGLE;
    repeatCount_ = 1;
  }

  if (!field_) {
    LOG(ERROR) << "No submessage with tag=" << tag << ", index=" << index;
    return false;
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
  return typer::add(message_, field_, value);
}

typedef bool (Field::*Applier)();

Operation* Field::apply(const Operation& op) {
  if (!field_) {
    LOG(ERROR) << "Bad field descriptor!";
    return NULL;
  }

  Applier applier = &Field::error;

  Operation::Command command = op.command();
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
  f.dereference(0);
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

  if (type_ == INDEXED || message_->GetReflection()->HasField(*message_, field_))
    copyTo(undo_->add_value());
  else
    undo_->set_command(Operation::CLEAR);

  return copyFrom(operation_->value(0));
}


bool Field::swapRepeated() {
  message_->GetReflection()->SwapElements(message_, field_,
                                          operation_->swap1(),
                                          operation_->swap2());

  return true;
}

}  // namespace proto
}  // namespace rec
