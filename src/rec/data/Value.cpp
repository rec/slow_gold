#include "rec/data/Value.h"

namespace rec {
namespace data {

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

template <> bool Value::has<penum>() const { return has_enum_f(); }
template <> penum Value::get<penum>() const { return enum_f(); }

}  // namespace data
}  // namespace rec
