#include <google/protobuf/descriptor.h>

#include "rec/data/proto/TypedTyper.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace proto {
namespace typer {

// TYPE is the actual type we are returning: a primitive type or one of the two
// wrapper types pmessage and penum.  We only need one other name, the name that
// the protocol buffer classes uses for that type, but unfortunately we need it
// lower case, upper case, and capitalized, thus LOWER, UPPER and CAP.
#define METHODS_COMMON_TO_ALL(TYPE, LOWER, UPPER)                       \
  template <> void TypedTyper<TYPE>::Clear() {                          \
    ref().ClearField(msg_, field_);                                     \
  }                                                                     \
                                                                        \
  template <> const FieldDescriptor::Type TypedTyper<TYPE>::TYPE_INDEX  \
    = FieldDescriptor::TYPE_ ## UPPER;                                  \
                                                                        \
  template <> TYPE TypedTyper<TYPE>::copy(const Value& v) {             \
    return v.LOWER ## _f();                                             \
  }                                                                     \
                                                                        \
  template <> void TypedTyper<TYPE>::copy(TYPE t, Value* v) {           \
    v->set_ ## LOWER ## _f(t);                                          \
  }                                                                     \
                                                                        \


#define METHODS_COMMON_TO_MOST(TYPE, CAP)                               \
  template <> void TypedTyper<TYPE>::Add(TYPE t) {                      \
    ref().Add ## CAP(msg_, field_, t);                                  \
  }                                                                     \
                                                                        \
  template <> TYPE TypedTyper<TYPE>::Get() const {                      \
    return ref().Get ## CAP(*msg_, field_);                             \
  }                                                                     \
                                                                        \
  template <> TYPE TypedTyper<TYPE>::GetRepeated(uint32 i) const {      \
    return ref().GetRepeated ## CAP(*msg_, field_, i);                  \
  }                                                                     \
                                                                        \
  template <> void TypedTyper<TYPE>::Set(TYPE t) {                      \
    ref().Set ## CAP(msg_, field_, t);                                  \
  }                                                                     \
                                                                        \
  template <> void TypedTyper<TYPE>::SetRepeated(uint32 i, TYPE t) {    \
    ref().SetRepeated ## CAP(msg_, field_, i, t);                       \
  }                                                                     \
                                                                        \

#define SIMPLE_INSTANTIATION(TYPE, CAP, UPPER) \
  METHODS_COMMON_TO_ALL(TYPE, TYPE, UPPER)     \
  METHODS_COMMON_TO_MOST(TYPE, CAP)            \


#undef STRING

SIMPLE_INSTANTIATION(double, Double, DOUBLE)
SIMPLE_INSTANTIATION(float, Float, FLOAT)
SIMPLE_INSTANTIATION(int64, Int64, INT64)
SIMPLE_INSTANTIATION(uint64, UInt64, UINT64)
SIMPLE_INSTANTIATION(int32, Int32, INT32)
SIMPLE_INSTANTIATION(uint32, UInt32, UINT32)
SIMPLE_INSTANTIATION(bool, Bool, BOOL)
SIMPLE_INSTANTIATION(string, String, STRING)
SIMPLE_INSTANTIATION(bytes, String, BYTES)
SIMPLE_INSTANTIATION(fixed32, UInt32, FIXED32)
SIMPLE_INSTANTIATION(fixed64, UInt64, FIXED64)
SIMPLE_INSTANTIATION(sfixed32, Int32, SFIXED32)
SIMPLE_INSTANTIATION(sfixed64, Int64, SFIXED64)
SIMPLE_INSTANTIATION(sint32, Int32, SINT32)
SIMPLE_INSTANTIATION(sint64, Int64, SINT64)

METHODS_COMMON_TO_ALL(pmessage, message, MESSAGE)
METHODS_COMMON_TO_ALL(penum, enum, ENUM)

template <>
pmessage TypedTyper<pmessage>::Get() const {
  pmessage p;
  (field_ ? ref().GetMessage(*msg_, field_) : *msg_).
    SerializeToString(&p.value_);
  return p;
}

template <>
pmessage TypedTyper<pmessage>::GetRepeated(uint32 i) const {
  pmessage p;
  (field_ ? ref().GetRepeatedMessage(*msg_, field_, i) : *msg_).
    SerializeToString(&p.value_);
  return p;
}

template <>
void TypedTyper<pmessage>::Set(pmessage t) {
  (field_ ? ref().MutableMessage(msg_, field_) : msg_)->
    ParseFromString(t);
}

template <>
void TypedTyper<pmessage>::SetRepeated(uint32 i, pmessage t) {
  (field_ ? ref().MutableRepeatedMessage(msg_, field_, i) : msg_)->
    ParseFromString(t);
}

template <>
void TypedTyper<pmessage>::Add(pmessage t) {
  ref().AddMessage(msg_, field_)->ParseFromString(t);
}

template <>
penum TypedTyper<penum>::Get() const {
  return ref().GetEnum(*msg_, field_)->number();
}

template <>
penum TypedTyper<penum>::GetRepeated(uint32 i) const {
  return ref().GetRepeatedEnum(*msg_, field_, i)->number();
}

template <>
void TypedTyper<penum>::Set(penum t) {
  ref().SetEnum(msg_, field_, field_->enum_type()->FindValueByNumber(t));
}

template <>
void TypedTyper<penum>::SetRepeated(uint32 i, penum t) {
  ref().SetRepeatedEnum(msg_, field_, i,
                               field_->enum_type()->FindValueByNumber(t));
}

template <>
void TypedTyper<penum>::Add(penum t) {
  ref().AddEnum(msg_, field_, field_->enum_type()->FindValueByNumber(t));
}

}  // namespace typer
}  // namespace proto
}  // namespace rec
