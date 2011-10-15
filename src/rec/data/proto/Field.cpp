#include <google/protobuf/descriptor.h>

#include "rec/data/proto/Field.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/data/Address.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/Value.h"

namespace rec {
namespace data {

using namespace rec::proto;
using namespace google::protobuf;

Field* Field::makeField(const Address& address, const Message& msg) {
  ptr<Field> field(new Field);
  field->message_ = const_cast<Message*>(&msg);
  field->index_ = -1;
  field->field_ = NULL;
  field->type_ = SINGLE;

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
        if (index_ < 0 || index_ >= getSize(*this)) {
          LOG(ERROR) << " Index " << index_ << " not in range " << getSize(*this);
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

}  // namespace data
}  // namespace rec
