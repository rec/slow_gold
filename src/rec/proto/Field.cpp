#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include "rec/proto/Field.h"
#include "rec/base/scoped_ptr.h"
#include "rec/proto/Proto.h"
#include "rec/proto/Field.h"

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

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
  const Reflection& r = *(message_->GetReflection());

#define COPY_CASE(TYPE, CAP, UPPER)                                       \
   case FieldDescriptor::TYPE_ ## UPPER:                                  \
    if (type_)                                                       \
      r.Set ## CAP(message_, field_, value.TYPE ## _f()); \
    else                                                                  \
      r.SetRepeated ## CAP(message_, field_, index_, value.TYPE ## _f());           \
    return true;

  switch (field_->type()) {
    COPY_CASE(double, Double, DOUBLE)
    COPY_CASE(float, Float, FLOAT)
    COPY_CASE(int64, Int64, INT64)
    COPY_CASE(uint64, UInt64, UINT64)
    COPY_CASE(int32, Int32, INT32)
    COPY_CASE(fixed64, UInt64, FIXED64)
    COPY_CASE(fixed32, UInt32, FIXED32)
    COPY_CASE(bool, Bool, BOOL)
    COPY_CASE(string, String, STRING)
    // COPY_CASE(group, Group, GROUP)
    COPY_CASE(bytes, String, BYTES)
    COPY_CASE(uint32, UInt32, UINT32)
    // COPY_CASE(enum, Enum, ENUM)
    COPY_CASE(sfixed32, UInt32, SFIXED32)
    COPY_CASE(sfixed64, UInt64, SFIXED64)
    COPY_CASE(sint32, Int32, SINT32)
    COPY_CASE(sint64, Int64, SINT64)

    case FieldDescriptor::TYPE_MESSAGE: {
     Message* m = type_ ?
       r.MutableMessage(message_, field_) :
       r.MutableRepeatedMessage(message_, field_, index_);
     return m->ParseFromString(value.message_f());
    }

   default:
    LOG(ERROR) << "Can't understand field type " << field_->type();
    return false;
  }

#undef COPY_CASE
}

bool Field::addFrom(const Value& value) {
  const Reflection& r = *(message_->GetReflection());

#define COPY_CASE(TYPE, CAP, UPPER)                                       \
   case FieldDescriptor::TYPE_ ## UPPER:                                  \
      r.Add ## CAP(message_, field_, value.TYPE ## _f()); \
    return true;

  switch (field_->type()) {
    COPY_CASE(double, Double, DOUBLE)
    COPY_CASE(float, Float, FLOAT)
    COPY_CASE(int64, Int64, INT64)
    COPY_CASE(uint64, UInt64, UINT64)
    COPY_CASE(int32, Int32, INT32)
    COPY_CASE(fixed64, UInt64, FIXED64)
    COPY_CASE(fixed32, UInt32, FIXED32)
    COPY_CASE(bool, Bool, BOOL)
    COPY_CASE(string, String, STRING)
    // COPY_CASE(group, Group, GROUP)
    COPY_CASE(bytes, String, BYTES)
    COPY_CASE(uint32, UInt32, UINT32)
    // COPY_CASE(enum, Enum, ENUM)
    COPY_CASE(sfixed32, UInt32, SFIXED32)
    COPY_CASE(sfixed64, UInt64, SFIXED64)
    COPY_CASE(sint32, Int32, SINT32)
    COPY_CASE(sint64, Int64, SINT64)

    case FieldDescriptor::TYPE_MESSAGE:
     return r.AddMessage(message_, field_)->ParseFromString(value.message_f());

   default:
    LOG(ERROR) << "Can't understand field type " << field_->type();
    return false;
  }

#undef COPY_CASE
}

bool Field::copyTo(Value* v) const {
  const Reflection& r = *(message_->GetReflection());

#define COPY_CASE(TYPE, CAP, UPPER)                                       \
   case FieldDescriptor::TYPE_ ## UPPER:                                  \
    v->set_ ## TYPE ## _f(type_ ? r.Get ## CAP(*message_, field_) :         \
                          r.GetRepeated ## CAP(*message_, field_, index_)); \
    return true;

  switch (field_->type()) {
    COPY_CASE(double, Double, DOUBLE)
    COPY_CASE(float, Float, FLOAT)
    COPY_CASE(int64, Int64, INT64)
    COPY_CASE(uint64, UInt64, UINT64)
    COPY_CASE(int32, Int32, INT32)
    COPY_CASE(fixed64, UInt64, FIXED64)
    COPY_CASE(fixed32, UInt32, FIXED32)
    COPY_CASE(bool, Bool, BOOL)
    COPY_CASE(string, String, STRING)
    // COPY_CASE(group, Group, GROUP)
    COPY_CASE(bytes, String, BYTES)
    COPY_CASE(uint32, UInt32, UINT32)
    // COPY_CASE(enum, Enum, ENUM)
    COPY_CASE(sfixed32, UInt32, SFIXED32)
    COPY_CASE(sfixed64, UInt64, SFIXED64)
    COPY_CASE(sint32, Int32, SINT32)
    COPY_CASE(sint64, Int64, SINT64)

    case FieldDescriptor::TYPE_MESSAGE: {
     const Message& m = type_ ?
       r.GetMessage(*message_, field_) :
       r.GetRepeatedMessage(*message_, field_, index_);
     return m.SerializeToString(v->mutable_message_f());
    }

   default:
    LOG(ERROR) << "Can't understand field type " << field_->type();
    return false;
  }

#undef COPY_CASE
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
  if (operation_->value_size() != 0) {
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
