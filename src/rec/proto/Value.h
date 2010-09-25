#ifndef __REC_PROTO_VALUE__
#define __REC_PROTO_VALUE__

#include "rec/base/basictypes.h"
#include "rec/proto/Value.pb.h"
#include "rec/proto/Types.h"

namespace rec {
namespace proto {
namespace arg {

class Value : public proto::Value {
 public:
  Value() {}
  Value(double x) { set_double_f(x); }
  Value(float x) { set_float_f(x); }
  Value(int64 x) { set_int64_f(x); }
  Value(uint64 x) { set_uint64_f(x); }
  Value(int32 x) { set_int32_f(x); }
  Value(uint32 x) { set_uint32_f(x); }
  Value(bool x) { set_bool_f(x); }
  Value(string x) { set_string_f(x); }
  Value(bytes x) { set_bytes_f(x); }
  Value(fixed32 x) { set_fixed32_f(x); }
  Value(fixed64 x) { set_fixed64_f(x); }
  Value(sfixed32 x) { set_sfixed32_f(x); }
  Value(sfixed64 x) { set_sfixed64_f(x); }
  Value(sint32 x) { set_sint32_f(x); }
  Value(sint64 x) { set_sint64_f(x); }
  Value(pmessage x) { set_pmessage_f(x); }
  Value(penum x) { set_penum_f(x); }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Value);
};

}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_VALUE__
