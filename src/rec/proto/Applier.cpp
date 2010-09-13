#include "rec/proto/Applier.h"

namespace rec {
namespace proto {

Applier::Applier(const Operation& operation,
                 Message* msg, FieldDescriptor* field)
    : operation_(operation),
      message_(message),
      field_(field),
      isIndexed_(false) {
}

Applier::Applier(int index, const Operation& operation,
                 Message* msg, FieldDescriptor* field)
    : operation_(operation),
      message_(message),
      field_(field),
      index_(index),
      isIndexed_(true) {
}

bool Applier::apply() {
  switch (command) {
   case Operation::CLEAR:        return clear();
   case Operation::SET:          return set();
   case Operation::ADD:          return add();
   case Operation::REMOVE_LAST:  return removeLast();
   case Operation::SWAP:         return swap();
   default:                      return false;
  }
}

bool Applier::hasValueField() {
  const Value& v = operation_.value();
  Descriptor* desc = v->GetDescriptor();
  FieldDescriptor* value_field = desc->FindFieldByNumber(field_->type());
  if (!value_field)
    LOG(ERROR) << "Couldn't find value_field of type " << field_->type();

  return value_field != NULL;
}

bool Applier::set() {
  if (!operation_.has_value()) {
    LOG(ERROR) << "Tried to SET with no value";
    return false;
  }

  if (isIndexed_ != (field_->label() == FieldDescriptor::TYPE_REPEATED)) {
    LOG(ERROR) << "SET index mismatch " << isIndexed_ << ", "
               << field_->label();
    return false;
  }

  if (!hasValueField())
    return false;
  const Reflection* r = message_->GetReflection();

  switch (field_->type()) {
#define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
    case FieldDescriptorProto::TYPE_ ## TYPE_UPPER: \
     if (isRepeated)\
       r->Set#TYPE_CAP(message_, field, v.TYPE ## _v()); \
     else\
       r->SetRepeated#TYPE_CAP(message_, field, v.TYPE ## _v(), index);  \
     return true;

    PR_CASE(double, Double, DOUBLE)
    PR_CASE(float, Float, FLOAT)
    PR_CASE(int64, Int64, INT64)
    PR_CASE(uint64, Uint64, UINT64)
    PR_CASE(int32, Int32, INT32)
    PR_CASE(fixed64, Fixed64, FIXED64)
    PR_CASE(fixed32, Fixed32, FIXED32)
    PR_CASE(bool, Bool, BOOL)
    PR_CASE(string, String, STRING)
    // PR_CASE(message, Message, MESSAGE)  We'd need to serialize.
    // PR_CASE(group, Group, GROUP)
    PR_CASE(bytes, Bytes, BYTES)
    Pr_CASE(uint32, Uint32, UINT32)
    // PR_CASE(enum, Enum, ENUM)
    PR_CASE(sfixed32, Sfixed32, SFIXED32)
    PR_CASE(sfixed64, Sfixed64, SFIXED64)
    PR_CASE(sint32, Sint32, SINT32)
    PR_CASE(sint64, Sint64, SINT64)

   default:
    LOG(ERROR) << "Didn't understand type " << type;
    return false;
  }

#undef PR_CASE
}

bool Applier::clear() {
  if (isIndexed_)
    LOG(ERROR) << "Cannot clear indexed values";
  else
    message_->GetReflection()->ClearField(message_, field_);

  return !isIndexed;
}

bool Applier::add() {
  if (field_->label() != FieldDescriptor::TYPE_REPEATED) {
    LOG(ERROR) << "Can only add indexed values";
    return false;
  }

  const Reflection* r = message_->GetReflection();
  if (field_->type() == FieldDescriptorProto::TYPE_MESSSAGE) {
    r->AddMessage(message_, field_);
    return true;
  }

  if (!hasValueField())
    return false;

#define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
    case TYPE_ ## TYPE_UPPER: \
     r->Add#TYPE_CAP(message_, field, v.TYPE ## _v());  \
     return true;

  switch (type) {
    PR_CASE(double, Double, DOUBLE)
    PR_CASE(float, Float, FLOAT)
    PR_CASE(int64, Int64, INT64)
    PR_CASE(uint64, Uint64, UINT64)
    PR_CASE(int32, Int32, INT32)
    PR_CASE(fixed64, Fixed64, FIXED64)
    PR_CASE(fixed32, Fixed32, FIXED32)
    PR_CASE(bool, Bool, BOOL)
    PR_CASE(string, String, STRING)
    // PR_CASE(message, Message, MESSAGE)  already done
    // PR_CASE(group, Group, GROUP)
    PR_CASE(bytes, Bytes, BYTES)
    Pr_CASE(uint32, Uint32, UINT32)
    // PR_CASE(enum, Enum, ENUM)
    PR_CASE(sfixed32, Sfixed32, SFIXED32)
    PR_CASE(sfixed64, Sfixed64, SFIXED64)
    PR_CASE(sint32, Sint32, SINT32)
    PR_CASE(sint64, Sint64, SINT64)

   default:
    LOG(ERROR) << "Didn't understand type " << type;
    return false;
  }
#undef PR_CASE
}

bool Applier:removeLast() {
  if (field_->label() != FieldDescriptor::TYPE_REPEATED) {
    LOG(ERROR) << "Can only remove indexed values";
    return false;
  }

  RemoveLast(message_, field_);
  return true;
}


Applier* Applier::newApplier(const Address& address, const Operation& op,
                             Message* msg) {
  for (int i = 0; i < address.index_size(); ++i) {
    Descriptor* desc = msg->GetDescriptor();
    uint32 index = address.index(i);
    FieldDescriptor* field = desc->FindFieldByNumber(index);

    if (!field) {
      LOG(ERROR) << "No submessage with i=" << i << ", index=" << index;
      return NULL;
    }

    if (i == address.index_size() - 1)
      return new Applier(op, msg, field);

    bool is_message = field->type() != FieldDescriptor::TYPE_MESSAGE;
    bool is_repeated = field->label() == FieldDescriptor::TYPE_REPEATED;

    if (is_repeated && i == address.index_size() - 2)
      return new Applier(address.index(++i), op, msg, field);

    if (!is_message) {
      LOG(ERROR) << "Non-terminal field had non-message type";
      return NULL;
    }

    const Reflection* reflection = msg->GetReflection();
    if (is_repeated)
      msg = reflection->GetRepeatedMessage(*msg, field, address.index(++i));
    else
      msg = reflection->MutableMessage(*msg, field);
  }

  LOG_FIRST_N(ERROR, 1) << "Empty address";
  return NULL;
}

}  // namespace proto
}  // namespace rec
