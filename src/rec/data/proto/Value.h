#ifndef __REC_PROTO_VALUE__
#define __REC_PROTO_VALUE__

#include "rec/base/base.h"
#include "rec/data/proto/Value.pb.h"
#include "rec/data/proto/Types.h"

namespace rec {
namespace proto {

String toString(const Value& value);

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
  Value(pmessage x) { set_message_f(x); }
  Value(penum x) { set_enum_f(x); }

  template <typename T>
  T cast() const {
    if (has_uint32_f()) return uint32_f();
    if (has_double_f()) return double_f();
    if (has_float_f()) return float_f();
    if (has_int64_f()) return int64_f();
    if (has_uint64_f()) return uint64_f();
    if (has_int32_f()) return int32_f();
    if (has_bool_f()) return bool_f();
    if (has_fixed32_f()) return fixed32_f();
    if (has_fixed64_f()) return fixed64_f();
    if (has_sfixed32_f()) return sfixed32_f();
    if (has_sfixed64_f()) return sfixed64_f();
    if (has_sint32_f()) return sint32_f();
    if (has_sint64_f()) return sint64_f();
    if (has_enum_f()) return enum_f();
    return 0;
  }

  operator int() const { return cast<double>(); }
  operator double() const { return cast<double>(); }
  operator float() const { return cast<float>(); }
  operator int64() const { return cast<int64>(); }
  operator uint64() const { return cast<uint64>(); }
  operator int32() const { return cast<int32>(); }
  operator uint32() const { return cast<uint32>(); }
  operator bool() const { return cast<bool>(); }

  Value(const proto::Value v) : proto::Value(v) {}

};

}  // namespace arg
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_VALUE__
