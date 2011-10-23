#ifndef __REC_PROTO_TYPES__
#define __REC_PROTO_TYPES__

#include <string>

#include "rec/base/BaseNoJuce.h"
#include "rec/data/Operation.pb.h"

namespace rec {
namespace data {

typedef Operation::Command Command;

typedef uint32 Tag;

// Make fictitious types to correspond to the Google proto types that aren't
// primitive C++ types.
#define PROTO_MAKE_TYPE(OUT, IN)                       \
  struct OUT {                                         \
    OUT() {}                                           \
    OUT(IN value) : value_(value) {}                   \
    operator IN() const { return value_; }             \
                                                       \
    IN value_;                                         \
  };

PROTO_MAKE_TYPE(fixed32,  uint32);
PROTO_MAKE_TYPE(fixed64,  uint64);
PROTO_MAKE_TYPE(sfixed32, uint32);
PROTO_MAKE_TYPE(sfixed64, uint64);
PROTO_MAKE_TYPE(sint32,   uint32);
PROTO_MAKE_TYPE(sint64,   uint64);
PROTO_MAKE_TYPE(bytes,    string);
PROTO_MAKE_TYPE(penum,    int32);

inline bool operator==(const bytes& b1, const bytes& b2) {
  return b1.value_ == b2.value_;
}

#undef PROTO_MAKE_TYPE

struct pmessage {
  pmessage() {}
  pmessage(const Message& m) { m.SerializeToString(&value_); }
  pmessage(const string& s) : value_(s) {}
  operator string() const { return value_; }

  bool Parse(Message* m) { return m->ParseFromString(value_); }

  bool operator==(const pmessage& that) const {
    return value_ == that.value_;  // Hack but works.
  }

  string value_;
};

}  // namespace data

namespace proto {

typedef data::ValueProto ValueProto;

}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPES__
