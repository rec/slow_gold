#include <google/protobuf/descriptor.h>

#include "rec/data/proto/MessageField.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/data/Address.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/Value.h"

namespace rec {
namespace data {

namespace {

using namespace rec::proto;
using namespace google::protobuf;

bool dereference(MessageField* f, const Address::Part& afield) {
  if (f->field_) {
    const Reflection& r = *f->message_->GetReflection();
    if (f->type_ == MessageField::INDEXED) {
      if (f->field_->type() == FieldDescriptor::TYPE_MESSAGE) {
        if (f->index_ < 0 || f->index_ >= getSize(*f)) {
          LOG(ERROR) << " Index " << f->index_ << " not in range " << getSize(*f);
          return false;
        }
        f->message_ = r.MutableRepeatedMessage(f->message_, f->field_, f->index_);
      } else {
        LOG(ERROR) << "Non-terminal field had type " << f->field_->type();
        return false;
      }

    } else if (f->type_ == MessageField::REPEATED) {
      if (!afield.has_index()) {
        LOG(ERROR) << "Repeated has no index ";
        return false;
      }

      int32 index = static_cast<int32>(afield.index());
      if (index >= f->repeatCount_) {
        LOG(ERROR) << "Index " << index << " out of bounds " << f->repeatCount_;
        return false;
      }

      f->type_ = MessageField::INDEXED;
      f->index_ = index;
      return true;

    } else {
      f->message_ = r.MutableMessage(f->message_, f->field_);
      f->index_ = -1;
    }
  }

  if (!afield.has_name()) {
    LOG(ERROR) << "Expected a name at this point";
    return false;
  }

  if (!f->message_) {
    LOG(ERROR) << "Empty message";
    return false;
  }

  f->field_ = f->message_->GetDescriptor()->FindFieldByName(afield.name());
  if (!f->field_) {
    LOG(ERROR) << "Could not find field named " << afield.name()
               << " in class named " << f->message_->GetTypeName();
    return false;
  }

  if (f->field_->label() == FieldDescriptor::LABEL_REPEATED) {
    f->type_ = MessageField::REPEATED;
    f->repeatCount_ = f->message_->GetReflection()->FieldSize(*f->message_, f->field_);

  } else {
    f->type_ = MessageField::SINGLE;
    f->repeatCount_ = 1;
  }

  return true;
}

}  // namespace

bool fillMessageField(MessageField* field,
                      const Address& address, const Message& msg) {
  field->message_ = const_cast<Message*>(&msg);
  field->index_ = -1;
  field->field_ = NULL;
  field->type_ = MessageField::SINGLE;

  for (int i = 0; i < address.part_size(); ++i) {
    if (!dereference(field, address.part(i))) {
      LOG(ERROR) << "Couldn't get field from address:\n"
                 << address.DebugString()
                 << "\nMessage:\n" << msg.DebugString();
      return false;
    }
  }
  return true;
}

}  // namespace data
}  // namespace rec
