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

}  // namespace data
}  // namespace rec

