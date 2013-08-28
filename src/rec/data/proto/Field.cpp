#include <google/protobuf/descriptor.h>

#include "rec/data/proto/MessageField.h"
#include "rec/data/proto/Field.h"
#include "rec/data/Address.h"
#include "rec/data/Operation.pb.h"
#include "rec/data/Value.h"

namespace rec {
namespace data {

namespace {

using namespace rec::proto;
using namespace google::protobuf;

string dereference(MessageField* f, const Address::Part& afield) {
  if (f->field_) {
    const Reflection& r = *f->message_->GetReflection();
    if (f->type_ == MessageField::INDEXED) {
      if (f->field_->type() == FieldDescriptor::TYPE_MESSAGE) {
        if (f->index_ < 0 || f->index_ >= getSize(*f)) {
          return " Index " + str(String(f->index_)) + " not in range "
            + str(String(getSize(*f))) + ": " + f->message_->ShortDebugString();
        }
        f->message_ = r.MutableRepeatedMessage(f->message_, f->field_, f->index_);
      } else {
        return "Non-terminal field had type " + str(String(f->field_->type()));
      }

    } else if (f->type_ == MessageField::REPEATED) {
      if (!afield.has_index())
        return "Repeated has no index ";

      int32 index = static_cast<int32>(afield.index());
      if (index >= f->repeatCount_) {
        return "Index " + str(String(index)) + " out of bounds "
          + str(String(f->repeatCount_)) + ": " +
          f->message_->ShortDebugString();
      }

      f->type_ = MessageField::INDEXED;
      f->index_ = index;
      return "";

    } else {
      f->message_ = r.MutableMessage(f->message_, f->field_);
      f->index_ = -1;
    }
  }

  if (!afield.has_name())
    return "Expected a name at this point";

  if (!f->message_)
    return "Empty message";

  f->field_ = f->message_->GetDescriptor()->FindFieldByName(afield.name());
  if (!f->field_) {
    return "Could not find field named " + afield.name() +
      " in class named " + f->message_->GetTypeName();
  }

  if (f->field_->label() == FieldDescriptor::LABEL_REPEATED) {
    f->type_ = MessageField::REPEATED;
    f->repeatCount_ = f->message_->GetReflection()->FieldSize(*f->message_, f->field_);

  } else {
    f->type_ = MessageField::SINGLE;
    f->repeatCount_ = 1;
  }

  return "";
}

}  // namespace

MessageField createMessageField(const Address& address, const Message& msg) {
  MessageField field;
  field.message_ = const_cast<Message*>(&msg);
  field.index_ = -1;
  field.field_ = nullptr;
  field.type_ = MessageField::SINGLE;

  for (int i = 0; field.message_ && i < address.part_size(); ++i) {
    string error = dereference(&field, address.part(i));
    if (!error.empty()) {
      field.error_ = error + ": " + address.ShortDebugString() +
        "\nMessage:\n" + msg.ShortDebugString();
      break;
    }
  }
  return field;
}

}  // namespace data
}  // namespace rec
