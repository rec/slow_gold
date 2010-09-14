#include <glog/logging.h>

#include "google/protobuf/descriptor.h"
#include "google/protobuf/descriptor.pb.h"
#include "rec/proto/Applier.h"

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;

namespace rec {
namespace proto {

Applier::Applier(const Operation& operation,
                 Message* message, const FieldDescriptor* field)
    : operation_(operation),
      message_(message),
      field_(field),
      index_(-1),
      isIndexed_(false) {
}

Applier::Applier(int index, const Operation& operation,
                 Message* message, const FieldDescriptor* field)
    : operation_(operation),
      message_(message),
      field_(field),
      index_(index),
      isIndexed_(true) {
}

bool Applier::apply() {
  switch (operation_.command()) {
   case Operation::CLEAR:        return clear();
   case Operation::SET:          return set();
   case Operation::ADD:          return add();
   case Operation::REMOVE_LAST:  return removeLast();
   case Operation::SWAP:         return swap();
   default:                      return false;
  }
}

bool Applier::hasValueField() {
  const Descriptor* desc = operation_.value().GetDescriptor();
  const FieldDescriptor* value_field = desc->FindFieldByNumber(field_->type());
  if (!value_field)
    LOG(ERROR) << "Couldn't find value_field of type " << field_->type();

  return value_field != NULL;
}

bool Applier::set() {
  if (isIndexed_ != (field_->label() == FieldDescriptor::LABEL_REPEATED)) {
    LOG(ERROR) << "SET index mismatch " << isIndexed_ << ", "
               << field_->label();
    return false;
  }

  if (!hasValueField())
    return false;

  const Reflection* r = message_->GetReflection();

  switch (field_->type()) {
#define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
    case FieldDescriptor::TYPE_ ## TYPE_UPPER: \
     if (isIndexed_)\
       r->SetRepeated##TYPE_CAP(message_, field_, index_, operation_.value().TYPE ## _f());\
     else\
       r->Set ## TYPE_CAP(message_, field_, operation_.value().TYPE ## _f()); \
     return true;

    PR_CASE(double, Double, DOUBLE)
    PR_CASE(float, Float, FLOAT)
    PR_CASE(int64, Int64, INT64)
    PR_CASE(uint64, UInt64, UINT64)
    PR_CASE(int32, Int32, INT32)
    PR_CASE(fixed64, UInt64, FIXED64)
    PR_CASE(fixed32, UInt32, FIXED32)
    PR_CASE(bool, Bool, BOOL)
    PR_CASE(string, String, STRING)
    // PR_CASE(message, Message, MESSAGE)  We'd need to serialize.
    // PR_CASE(group, Group, GROUP)
    PR_CASE(bytes, String, BYTES)
    PR_CASE(uint32, UInt32, UINT32)
    // PR_CASE(enum, Enum, ENUM)
    PR_CASE(sfixed32, UInt32, SFIXED32)
    PR_CASE(sfixed64, UInt64, SFIXED64)
    PR_CASE(sint32, Int32, SINT32)
    PR_CASE(sint64, Int64, SINT64)

   default:
    LOG(ERROR) << "Didn't understand type " << field_->type();
    return false;
  }

#undef PR_CASE
}

bool Applier::clear() {
  if (isIndexed_)
    LOG(ERROR) << "Cannot clear indexed values";
  else
    message_->GetReflection()->ClearField(message_, field_);

  return !isIndexed_;
}

bool Applier::add() {
  if (field_->label() != FieldDescriptor::LABEL_REPEATED) {
    LOG(ERROR) << "Can only add indexed values "
               << field_->label();
    return false;
  }

  const Reflection* r = message_->GetReflection();
  if (field_->type() == FieldDescriptor::TYPE_MESSAGE) {
    r->AddMessage(message_, field_);
    return true;
  }

  if (!hasValueField())
    return false;

#define PR_CASE(TYPE, TYPE_CAP, TYPE_UPPER) \
  case FieldDescriptor::TYPE_ ## TYPE_UPPER:                     \
     r->Add ## TYPE_CAP(message_, field_, operation_.value().TYPE ## _f());  \
     return true;

  switch (field_->type()) {
    PR_CASE(double, Double, DOUBLE)
    PR_CASE(float, Float, FLOAT)
    PR_CASE(int64, Int64, INT64)
    PR_CASE(uint64, UInt64, UINT64)
    PR_CASE(int32, Int32, INT32)
    PR_CASE(fixed64, UInt64, FIXED64)
    PR_CASE(fixed32, UInt32, FIXED32)
    PR_CASE(bool, Bool, BOOL)
    PR_CASE(string, String, STRING)
    // PR_CASE(message, Message, MESSAGE)  already done
    // PR_CASE(group, Group, GROUP)
    PR_CASE(bytes, String, BYTES)
    PR_CASE(uint32, UInt32, UINT32)
    // PR_CASE(enum, Enum, ENUM)
    PR_CASE(sfixed32, UInt32, SFIXED32)
    PR_CASE(sfixed64, UInt64, SFIXED64)
    PR_CASE(sint32, Int32, SINT32)
    PR_CASE(sint64, Int64, SINT64)

   default:
    LOG(ERROR) << "Didn't understand type " << field_->type();
    return false;
  }
#undef PR_CASE
}

bool Applier::removeLast() {
  if (field_->label() != FieldDescriptor::LABEL_REPEATED) {
    LOG(ERROR) << "Can only remove indexed values";
    return false;
  }

  message_->GetReflection()->RemoveLast(message_, field_);
  return true;
}

bool Applier::swap() {
  if (field_->label() != FieldDescriptor::LABEL_REPEATED) {
    LOG(ERROR) << "Can only remove indexed values";
    return false;
  }

  message_->GetReflection()->SwapElements(message_, field_,
                                          operation_.swap1(),
                                          operation_.swap2());
  return true;
}

Applier* Applier::create(const Operation& op, Message* msg) {
  for (int i = 0; i < op.address_size(); ++i) {
    const Descriptor* desc = msg->GetDescriptor();
    uint32 index = op.address(i);
    const FieldDescriptor* field = desc->FindFieldByNumber(index);

    if (!field) {
      LOG(ERROR) << "No submessage with i=" << i << ", index=" << index;
      return NULL;
    }

    if (i == op.address_size() - 1)
      return new Applier(op, msg, field);

    bool is_message = field->type() == FieldDescriptor::TYPE_MESSAGE;
    bool is_repeated = field->label() == FieldDescriptor::LABEL_REPEATED;

    if (is_repeated && i == op.address_size() - 2)
      return new Applier(op.address(++i), op, msg, field);

    if (!is_message) {
      LOG(ERROR) << "Non-terminal field had non-message type "
                 << field->type();
      return NULL;
    }

    const Reflection* reflection = msg->GetReflection();
    if (is_repeated)
      msg = reflection->MutableRepeatedMessage(msg, field, op.address(++i));
    else
      msg = reflection->MutableMessage(msg, field);
  }

  LOG_FIRST_N(ERROR, 1) << "Empty address";
  return NULL;
}

}  // namespace proto
}  // namespace rec
