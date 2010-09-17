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
      type_ = INDEXED;
      index_ = tag;
      return true;

    } else {
      message_ = r.MutableMessage(message_, field_);
    }
  }

  field_ = message_->GetDescriptor()->FindFieldByNumber(tag);
  type_ = (field_->label() == FieldDescriptor::LABEL_REPEATED) ? REPEATED :
    SINGLE;

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

typedef Operation* (Field::*Applier)(const Operation& op);

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
      {&Field::setIndexed,  &Field::setRepeated,     &Field::setSingle},
      {&Field::error,       &Field::swapRepeated,    &Field::error},
    };
    applier = appliers[command][type_];
  }

  return (this->*applier)(op);
}

Operation* Field::error(const Operation& op) {
  LOG(ERROR) << "This operation was impossible";
  return NULL;
}


Operation* Field::addRepeated(const Operation& op) {

}


Operation* Field::clearRepeated(const Operation& op) {

}

Operation* Field::clearSingle(const Operation& op) {

}


Operation* Field::removeRepeated(const Operation& op) {

}

Operation* Field::setIndexed(const Operation& op) {

}

Operation* Field::setRepeated(const Operation& op) {

}

Operation* Field::setSingle(const Operation& op) {

}


Operation* Field::swapRepeated(const Operation& op) {

}

}  // namespace proto
}  // namespace rec
