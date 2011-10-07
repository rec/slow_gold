#ifndef __REC_PROTO_TYPED_OPERATIONS__
#define __REC_PROTO_TYPED_OPERATIONS__

#include "rec/data/proto/Comparer.h"

namespace google { namespace protobuf {  class FieldDescriptor; }}


namespace rec {

namespace data { class Address; }
namespace data { class Value; }

namespace proto {
namespace typer {

typedef google::protobuf::FieldDescriptor FieldDescriptor;

bool copyTo(const Message& m, const FieldDescriptor* f, data::ValueProto* v);
bool copyTo(const Message& m, const FieldDescriptor* f, uint32 i,
            data::ValueProto* v);

bool copyFrom(Message* m, const FieldDescriptor* f, const data::Value& v);
bool copyFrom(Message* m, const FieldDescriptor* f, uint32 i,
              const data::Value& v);

bool add(Message* m, const FieldDescriptor* f, const data::Value& v);

bool equals(const Message& m1, const Message& m2, const FieldDescriptor* f,
            const Comparer& c = Comparer());
bool equals(const Message& m1, const Message& m2, const FieldDescriptor* f, int i,
            const Comparer& c = Comparer());

bool equals(const Message& x, const Message& y, const Comparer& cmp);

}  // namespace typer
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPED_OPERATIONS__
