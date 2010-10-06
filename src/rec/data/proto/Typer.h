#ifndef __REC_PROTO_TYPER__
#define __REC_PROTO_TYPER__

#include "rec/base/base.h"

namespace google {
namespace protobuf {

class FieldDescriptor;

}  // namespace protobuf
}  // namespace google

namespace rec {
namespace proto {

class Value;

typedef google::protobuf::FieldDescriptor FieldDescriptor;

namespace typer {

bool copyTo(const Message& m, const FieldDescriptor* f, Value* v);
bool copyTo(const Message& m, const FieldDescriptor* f, uint32 i, Value* v);

bool copyFrom(Message* m, const FieldDescriptor* f, const Value& v);
bool copyFrom(Message* m, const FieldDescriptor* f, uint32 i, const Value& v);

bool add(Message* m, const FieldDescriptor* f, const Value& v);

}  // namespace typer
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPER__
