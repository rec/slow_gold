#include "rec/proto/Copy.h"

#include "rec/base/scoped_ptr.h"
#include "google/protobuf/descriptor.h"
#include "rec/proto/Proto.h"

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

namespace rec {
namespace proto {

bool copyFrom(const Value& value, const FieldDescriptor* field, Message* msg) {
  const Reflection& reflect = *msg->GetReflection();

#define COPY_CASE(TYPE, CAP, UPPER)                         \
   case FieldDescriptor::TYPE_ ## UPPER:                    \
     reflect.Set ## CAP(msg, field, value.TYPE ## _f());    \
     return true;

  switch (field->type()) {
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
    return reflect.MutableMessage(msg, field)->
      ParseFromString(value.message_f());

   default:
    LOG(ERROR) << "Can't understand field type " << field->ty();
    return false;
  }
}

bool copyFrom(uint32 index, const Value& value,
              const FieldDescriptor* field, Message* msg) {
  const Reflection& reflect = *msg->GetReflection();

#define COPY_CASE(TYPE, CAP, UPPER)         \
    case FieldDescriptor::TYPE_ ## UPPER:   \
     reflect.SetRepeated ## CAP(msg, field, index, value.TYPE ## _f());  \
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
    return r->MutableRepeatedMessage(msg, field, index)->
      ParseFromString(v.message_f());

   default:
    LOG(ERROR) << "Can't understand field type " << field->ty();
    return false;
  }
}

bool copyTo(Value* value,
            const google::protobuf::FieldDescriptor* field,
            google::protobuf::Message* message) {
  const Reflection& reflect = *msg->GetReflection();

#define COPY_CASE(TYPE, CAP, UPPER)                          \
    case FieldDescriptor::TYPE_ ## UPPER:                    \
      v.set_ ## TYPE ## _f(reflect.Get ## CAP(msg, field));  \
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
    return r->GetMessage(msg, field)->SerializeToString(v.mutable_message_f());

   default:
    LOG(ERROR) << "Can't understand field type " << field->ty();
    return false;
  }
}



bool copyTo(uint32 index,
            Value* value,
            const google::protobuf::FieldDescriptor* field,
            google::protobuf::Message* message) {
  const Reflection& reflect = *msg->GetReflection();

#define COPY_CASE(TYPE, CAP, UPPER)                          \
    case FieldDescriptor::TYPE_ ## UPPER:                    \
      v.set_ ## TYPE ## _f(reflect.GetRepeated ## CAP(msg, field, index)); \
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
    return r->GetRepeatedMessage(msg, field, index)->
       SerializeToString(v.mutable_message_f());

   default:
    LOG(ERROR) << "Can't understand field type " << field->ty();
    return false;
  }
}

}  // namespace proto
}  // namespace rec
