#ifndef __REC_PROTO_TYPES__
#define __REC_PROTO_TYPES__

#include <string>

#include "rec/base/base.h"
#include "rec/data/proto/Operation.pb.h"

namespace rec {
namespace proto {

typedef Operation::Command Command;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;

typedef uint32 Tag;

#define PROTO_MAKE_TYPE(OUT, IN)                       \
  struct OUT {                                         \
    OUT();                                             \
    OUT(IN value) : value_(value) {}                   \
    operator IN() const { return value_; }             \
                                                       \
    IN value_;                                         \
  }

PROTO_MAKE_TYPE(fixed32,  uint32);
PROTO_MAKE_TYPE(fixed64,  uint64);

PROTO_MAKE_TYPE(sfixed32, uint32);
PROTO_MAKE_TYPE(sfixed64, uint64);

PROTO_MAKE_TYPE(sint32,   uint32);
PROTO_MAKE_TYPE(sint64,   uint64);

PROTO_MAKE_TYPE(bytes,    string);
PROTO_MAKE_TYPE(penum,    int);

#undef PROTO_MAKE_TYPE

struct pmessage {
  pmessage() {}
  pmessage(const Message& m) { m.SerializeToString(&value_); }
  pmessage(const string& s) : value_(s) {}
  operator string() const { return value_; }

  bool Parse(Message* m) { return m->ParseFromString(value_); }

  string value_;
};

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPES__
