#ifndef __REC_PROTO_COPY__
#define __REC_PROTO_COPY__

#include "rec/base/basictypes.h"

namespace google {
namespace protobuf {

class Message;
class FieldDescriptor;

}  // namespace protobuf
}  // namespace google


namespace rec {
namespace proto {

class Value;

bool copyFrom(const Value& value,
              const google::protobuf::FieldDescriptor* field,
              google::protobuf::Message* message);

bool copyFrom(uint32 index,
              const Value& value,
              const google::protobuf::FieldDescriptor* field,
              google::protobuf::Message* message);

bool copyTo(Value* value,
            const google::protobuf::FieldDescriptor* field,
            google::protobuf::Message* message);

bool copyTo(uint32 index,
            Value* value,
            const google::protobuf::FieldDescriptor* field,
            google::protobuf::Message* message);

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_COPY__
