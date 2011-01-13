#ifndef __REC_PROTO_TYPEDTYPER__
#define __REC_PROTO_TYPEDTYPER__

#include "rec/data/proto/Typer.h"
#include "rec/data/proto/TypedOperations.h"
#include "rec/data/proto/Types.h"
#include "rec/data/proto/Comparer.h"

namespace rec {
namespace proto {
namespace typer {

template <typename Type>
class TypedTyper : public Typer {
 public:
  static const FieldDescriptor::Type TYPE_INDEX;
  TypedTyper(Message* m, const FieldDescriptor* f) : Typer(m, f) {}

  static Type copy(const Value& v);
  static void copy(Type t, Value* v);

  // These functions have the same name as the corresponding roots of the
  // google::protobuf methods.
  Type GetRepeated(uint32 i) const;
  Type Get() const;

  void Set(Type t);
  void SetRepeated(uint32 i, Type t);

  void Add(Type t);
  void Clear();

  bool Equals(const Message& m, const Comparer& c) const;
  bool Equals(const Message& m, uint32 i, const Comparer& c) const;

  virtual void copyFrom(const Value& v)            { Set(copy(v));  }
  virtual void copyFrom(uint32 i, const Value& v)  { SetRepeated(i, copy(v)); }
  virtual void copyTo(Value* v) const              { copy(Get(), v); }
  virtual void copyTo(uint32 i, Value* v) const    { copy(GetRepeated(i), v); }
  virtual void add(const Value& v)                 { Add(copy(v)); }
  virtual void clear()                             { Clear(); }

  virtual Typer* clone(google::protobuf::Message* m,
                       const FieldDescriptor* f) const {
    return new TypedTyper<Type>(m, f);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(TypedTyper);
};

template <>
inline bool TypedTyper<pmessage>::Equals(const rec::Message& m,
                                         const Comparer& cmp) const {
  return typer::equals(*msg_, m, field_, cmp);
}

template <>
inline bool TypedTyper<pmessage>::Equals(const rec::Message& m, uint32 i,
                                         const Comparer& cmp) const {
  return typer::equals(*msg_, m, field_, i, cmp);
}

template <typename Type>
bool TypedTyper<Type>::Equals(const Message& m, const Comparer& c) const {
  TypedTyper<Type> that(const_cast<Message*>(&m), field_);
  return c(Get(), that.Get());
}

template <typename Type>
bool TypedTyper<Type>::Equals(const Message& m, uint32 i,
                              const Comparer& c) const {
  TypedTyper<Type> that(const_cast<Message*>(&m), field_);
  return c(GetRepeated(i), that.GetRepeated(i));
}


}  // namespace typer
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPEDTYPER__
