#ifndef __REC_PROTO_VALUE__
#define __REC_PROTO_VALUE__

#include "rec/base/base.h"
#include "rec/data/proto/Value.pb.h"
#include "rec/data/proto/Types.h"
#include "rec/util/Copy.h"

namespace rec {
namespace data {

class Value : public ValueProto {
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
  Value(const Message& x) {
    string s;
    copy::copy(x, &s, STORAGE_STYLE);
    set_message_f(s);
  }
  Value(const ValueProto& x) : ValueProto(x) {}

#if 0
  template <typename T>
  T cast() const {
    if (has_uint32_f()) return static_cast<T>(uint32_f());
    if (has_double_f()) return static_cast<T>(double_f());
    if (has_float_f()) return static_cast<T>(float_f());
    if (has_int64_f()) return static_cast<T>(int64_f());
    if (has_uint64_f()) return static_cast<T>(uint64_f());
    if (has_int32_f()) return static_cast<T>(int32_f());
    if (has_bool_f()) return static_cast<T>(bool_f());
    if (has_fixed32_f()) return static_cast<T>(fixed32_f());
    if (has_fixed64_f()) return static_cast<T>(fixed64_f());
    if (has_sfixed32_f()) return static_cast<T>(sfixed32_f());
    if (has_sfixed64_f()) return static_cast<T>(sfixed64_f());
    if (has_sint32_f()) return static_cast<T>(sint32_f());
    if (has_sint64_f()) return static_cast<T>(sint64_f());
    if (has_enum_f()) return static_cast<T>(enum_f());
    return 0;
  }

  operator int() const { return cast<int>(); }
  operator double() const { return cast<double>(); }
  operator float() const { return cast<float>(); }
  operator int64() const { return cast<int64>(); }
  operator uint64() const { return cast<uint64>(); }
  // operator int32() const { return cast<int32>(); }
  operator uint32() const { return cast<uint32>(); }
  operator bool() const { return bool_f(); }
  operator penum() const { return enum_f(); }
  operator pmessage() const { return message_f(); }
#endif

  template <typename T> bool has() const;
  template <typename T> T get() const;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_PROTO_VALUE__
