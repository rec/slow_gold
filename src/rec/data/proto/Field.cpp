#include <google/protobuf/descriptor.h>

#include "rec/data/proto/Field.h"
#include "rec/data/Address.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/Value.h"
#include "rec/data/proto/TypedOperations.h"
#include "rec/data/proto/Types.h"
#include "rec/data/proto/Value.pb.h"

namespace rec {
namespace data {

using namespace rec::proto;
using namespace google::protobuf;

Field* Field::makeField(const Address& address, const Message& msg) {
  ptr<Field> field(new Field(const_cast<Message*>(&msg)));
  for (int i = 0; i < address.part_size(); ++i) {
    if (!field->dereference(address.part(i))) {
      LOG(ERROR) << "Couldn't get field from address:\n"
                 << address.DebugString()
                 << "\nMessage:\n" << msg.DebugString();
      return NULL;
    }
  }
  return field.transfer();
}

bool Field::dereference(const Address::Part& afield) {
  if (field_) {
    const Reflection& r = *message_->GetReflection();
    if (type_ == INDEXED) {
      if (field_->type() == FieldDescriptor::TYPE_MESSAGE) {
        if (index_ < 0 || index_ >= getSize()) {
          LOG(ERROR) << " Index " << index_ << " not in range " << getSize();
          return false;
        }
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

      int32 index = static_cast<int32>(afield.index());
      if (index >= repeatCount_) {
        LOG(ERROR) << "Index " << index << " out of bounds " << repeatCount_;
        return false;
      }

      type_ = INDEXED;
      index_ = index;
      return true;

    } else {
      message_ = r.MutableMessage(message_, field_);
      index_ = -1;
    }
  }

  if (!afield.has_name()) {
    LOG(ERROR) << "Expected a name at this point";
    return false;
  }

  if (!message_) {
    LOG(ERROR) << "Empty message";
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
  if (!field_) {
    if (value.has_message_f())
      return pmessage(value.message_f()).Parse(message_);

    LOG(ERROR) << "The Value contained no message field.";
    return false;
  }

  return (type_ == SINGLE) ? typer::copyFrom(message_, field_, value) :
    typer::copyFrom(message_, field_, index_, value);
}

bool Field::copyTo(ValueProto* value) const {
  if (!field_) {
    value->set_message_f(pmessage(*message_));
    return true;
  }

  if (type_ == SINGLE)
    return typer::copyTo(*message_, field_, value);

  if (index_ >= 0)
    return typer::copyTo(*message_, field_, index_, value);

  LOG(ERROR) << "copyTo failed with no index " << message_->GetTypeName();
  return false;
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

  LOG(ERROR) << "Unable to execute operation " << op.DebugString();
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

  Field f(message_);
  f.field_ = field_;
  f.type_ = type_;
  f.repeatCount_ = repeatCount_;
  f.dereference(Address::Part(0));
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
  if (!copyTo(undo_->add_value()))
    return false;

  message_->Clear();
  return true;
}

bool Field::removeRepeated() {
  return doRemove(operation_->remove());
}

bool Field::setSingle() {
  if (operation_->value_size() != 1) {
    LOG(ERROR) << "Can only set one value at a time";
    return false;
  }

  if (field_ && type_ != INDEXED && !hasValue())
    undo_->set_command(Operation::CLEAR);
  else if (!copyTo(undo_->add_value()))
    LOG(ERROR) << "Couldn't copy undo value, continuing";

  return copyFrom(operation_->value(0));
}


bool Field::swapRepeated() {
  if (!field_) {
    LOG(ERROR) << "Can't swap repeated on self";
    return false;
  }
  int s1 = operation_->swap1(), s2 = operation_->swap2();
  int size = getSize();

  bool inRange = (s1 >= 0 && s2 >= 0 && s1 < size && s2 < size);
  if (inRange)
    message_->GetReflection()->SwapElements(message_, field_, s1, s2);
  else
    LOG(ERROR) << "Can't swap positions " << s1 << "," << s2 << ": " << size;

  return inRange;
}

}  // namespace data
}  // namespace rec
