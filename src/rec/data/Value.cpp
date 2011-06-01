#include "rec/data/Value.h"

namespace rec {
namespace data {

String toString(const ValueProto& value) {
  if (value.has_double_f()) return String(value.double_f());
  if (value.has_float_f()) return String(value.float_f());
  if (value.has_int64_f()) return String(value.int64_f());
  if (value.has_uint64_f()) return String(value.uint64_f());
  if (value.has_int32_f()) return String(value.int32_f());
  if (value.has_uint32_f()) return String(value.uint32_f());
  if (value.has_bool_f()) return String(value.bool_f());
  if (value.has_string_f()) return str(value.string_f());
  if (value.has_bytes_f()) return str(value.bytes_f());
  if (value.has_fixed32_f()) return String(value.fixed32_f());
  if (value.has_fixed64_f()) return String(value.fixed64_f());
  if (value.has_sfixed32_f()) return String(value.sfixed32_f());
  if (value.has_sfixed64_f()) return String(value.sfixed64_f());
  if (value.has_sint32_f()) return String(value.sint32_f());
  if (value.has_sint64_f()) return String(value.sint64_f());
  // if (value.has_message_f()) return String(value.message_f());
  if (value.has_enum_f()) return String(value.enum_f());

  return String::empty;
}

template <> bool Value::has<int32>() const { return has_int32_f(); }
template <> int32 Value::get<int32>() const { return int32_f(); }

template <> bool Value::has<double>() const { return has_double_f(); }
template <> double Value::get<double>() const { return double_f(); }

template <> bool Value::has<float>() const { return has_float_f(); }
template <> float Value::get<float>() const { return float_f(); }

template <> bool Value::has<bool>() const { return has_bool_f(); }
template <> bool Value::get<bool>() const { return bool_f(); }

template <> bool Value::has<string>() const { return has_string_f(); }
template <> string Value::get<string>() const { return string_f(); }


}  // namespace data
}  // namespace rec

