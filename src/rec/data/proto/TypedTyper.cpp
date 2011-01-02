#include <google/protobuf/descriptor.h>

#include "rec/data/proto/TypedTyper.h"
#include "rec/data/proto/TypedOperations.h"
#include "rec/data/proto/Equals.h"

namespace rec {
namespace proto {
namespace typer {

#define METHOD(CTYPE, TYPE, NAME, INARGS, RETVAL, CONST, RETURN, OUTARGS) \
  template <>                                                           \
  RETVAL TypedTyper<CTYPE>::NAME INARGS CONST {                         \
    RETURN (reflection().NAME ## TYPE OUTARGS);                         \
  }

#define GETTER(CTYPE, TYPE, NAME, INARGS, OUTARGS)                  \
  METHOD(CTYPE, TYPE, NAME, INARGS, CTYPE, const, return, OUTARGS)

#define GETTERS(CTYPE, TYPE)                                        \
  GETTER(CTYPE, TYPE, Get, (), (*msg_, field_))                     \
  GETTER(CTYPE, TYPE, GetRepeated, (uint32 i), (*msg_, field_, i))


#define SETTER(CTYPE, TYPE, NAME, INARGS, OUTARGS)                  \
  METHOD(CTYPE, TYPE, NAME, INARGS, void, , , OUTARGS)

#define SETTERS(CTYPE, TYPE)                                            \
  SETTER(CTYPE, TYPE, Set, (CTYPE v), (msg_, field_, v))                \
  SETTER(CTYPE, TYPE, SetRepeated, (uint32 i, CTYPE v), (msg_, field_, i, v))


#define ADD(CTYPE, TYPE)                                            \
  METHOD(CTYPE, TYPE, Add, (CTYPE v), void, , , (msg_, field_, v))

#define CLEAR(CTYPE)                                                 \
  METHOD(CTYPE, Field, Clear, (), void, , , (msg_, field_))

#define EQUALS(CTYPE)                                                   \
  template <> bool TypedTyper<CTYPE>::Equals(const Message& m,          \
                                             const Comparer& c) const { \
    TypedTyper<CTYPE> that(const_cast<Message*>(&m), field_);           \
    return c(Get(), that.Get());                                        \
  }                                                                     \
                                                                        \
  template <> bool TypedTyper<CTYPE>::Equals(const Message& m, uint32 i, \
                                             const Comparer& c) const { \
    TypedTyper<CTYPE> that(const_cast<Message*>(&m), field_);           \
    return c(GetRepeated(i), that.GetRepeated(i));                      \
  }


#define DEF_TYPE(CTYPE, UPPER)                                          \
  template <> const FieldDescriptor::Type TypedTyper<CTYPE>::TYPE_INDEX = \
    FieldDescriptor::TYPE_ ## UPPER;

#define COPY(CTYPE, FTYPE)                                              \
  template <> CTYPE TypedTyper<CTYPE>::copy(const Value& v) {           \
    return v.FTYPE ## _f();                                             \
  }                                                                     \
  template <> void TypedTyper<CTYPE>::copy(CTYPE t, Value* v) {         \
    v->set_ ## FTYPE ## _f(t);                                          \
  }

#define DEF_ALL(CTYPE, TYPE, UPPER)                                     \
  GETTERS(CTYPE, TYPE)                                                  \
  SETTERS(CTYPE, TYPE)                                                  \
  ADD(CTYPE, TYPE)                                                      \
  CLEAR(CTYPE)                                                          \
  DEF_TYPE(CTYPE, UPPER)                                                \
  COPY(CTYPE, CTYPE)                                                    \
  EQUALS(CTYPE)

#undef STRING

DEF_ALL(double, Double, DOUBLE)
DEF_ALL(float, Float, FLOAT)
DEF_ALL(int64, Int64, INT64)
DEF_ALL(uint64, UInt64, UINT64)
DEF_ALL(int32, Int32, INT32)
DEF_ALL(uint32, UInt32, UINT32)
DEF_ALL(bool, Bool, BOOL)
DEF_ALL(string, String, STRING)
DEF_ALL(bytes, String, BYTES)
DEF_ALL(fixed32, UInt32, FIXED32)
DEF_ALL(fixed64, UInt64, FIXED64)
DEF_ALL(sfixed32, Int32, SFIXED32)
DEF_ALL(sfixed64, Int64, SFIXED64)
DEF_ALL(sint32, Int32, SINT32)
DEF_ALL(sint64, Int64, SINT64)

DEF_TYPE(pmessage, MESSAGE)
COPY(pmessage, message)
CLEAR(pmessage)

template <>
pmessage TypedTyper<pmessage>::Get() const {
  pmessage p;
  (field_ ? reflection().GetMessage(*msg_, field_) : *msg_).
    SerializeToString(&p.value_);
  return p;
}

template <>
pmessage TypedTyper<pmessage>::GetRepeated(uint32 i) const {
  pmessage p;
  (field_ ? reflection().GetRepeatedMessage(*msg_, field_, i) : *msg_).
    SerializeToString(&p.value_);
  return p;
}

template <>
void TypedTyper<pmessage>::Set(pmessage t) {
  (field_ ? reflection().MutableMessage(msg_, field_) : msg_)->
    ParseFromString(t);
}

template <>
void TypedTyper<pmessage>::SetRepeated(uint32 i, pmessage t) {
  (field_ ? reflection().MutableRepeatedMessage(msg_, field_, i) : msg_)->
    ParseFromString(t);
}

template <>
void TypedTyper<pmessage>::Add(pmessage t) {
  reflection().AddMessage(msg_, field_)->ParseFromString(t);
}

template <>
bool TypedTyper<pmessage>::Equals(const rec::Message& m, const Comparer& cmp) const {
  return typer::equals(*msg_, m, field_, cmp);
}


template <>
bool TypedTyper<pmessage>::Equals(const rec::Message& m, uint32 i,
                                  const Comparer& cmp) const {
  return typer::equals(*msg_, m, field_, i, cmp);
}


template <>
penum TypedTyper<penum>::Get() const {
  return reflection().GetEnum(*msg_, field_)->number();
}

template <>
penum TypedTyper<penum>::GetRepeated(uint32 i) const {
  return reflection().GetRepeatedEnum(*msg_, field_, i)->number();
}

DEF_TYPE(penum, ENUM)
COPY(penum, enum)
CLEAR(penum)
EQUALS(penum)


template <>
void TypedTyper<penum>::Set(penum t) {
  reflection().SetEnum(msg_, field_, field_->enum_type()->FindValueByNumber(t));
}

template <>
void TypedTyper<penum>::SetRepeated(uint32 i, penum t) {
  reflection().SetRepeatedEnum(msg_, field_, i,
                               field_->enum_type()->FindValueByNumber(t));
}

template <>
void TypedTyper<penum>::Add(penum t) {
  reflection().AddEnum(msg_, field_, field_->enum_type()->FindValueByNumber(t));
}


}  // namespace typer
}  // namespace proto
}  // namespace rec
