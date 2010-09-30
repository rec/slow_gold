#ifndef __REC_PROTO_TYPEDTYPER__
#define __REC_PROTO_TYPEDTYPER__

#include "rec/base/base.h"
#include "rec/proto/Typer.h"
#include "rec/proto/Types.h"

namespace rec {
namespace proto {
namespace typer {

class Typer {
 public:
  Typer(Message* m, const FieldDescriptor* f);
  virtual ~Typer() {}

  virtual void copyTo(Value* v) const             { typer_->copyTo(v); }
  virtual void copyTo(uint32 i, Value* v) const   { typer_->copyTo(i, v); }

  virtual void copyFrom(const Value& v)           { typer_->copyFrom(v); }
  virtual void copyFrom(uint32 i, const Value& v) { typer_->copyFrom(i, v); }

  virtual void add(const Value& v)                { typer_->add(v); }

 protected:
  Typer() {}
  scoped_ptr<Typer> typer_;

  DISALLOW_COPY_AND_ASSIGN(Typer);
};

class TypedTyperBase : public Typer {
 public:
  TypedTyperBase(Message* m, const FieldDescriptor* f)
      : field_(f), msg_(m) {
  }
  virtual Typer* clone(google::protobuf::Message* f,
                       const FieldDescriptor* f) const = 0;

 protected:
  const Reflection& reflection() const { return *msg_->GetReflection(); }

  Message* msg_;
  const FieldDescriptor* field_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedTyperBase);
};

template <typename Type>
class TypedTyper : public TypedTyperBase {
 public:
  static const FieldDescriptor::Type TYPE_INDEX;
  TypedTyper(Message* m, const FieldDescriptor* f)
      : TypedTyperBase(m, f) {
  }

  static Type copy(const Value& v);
  static void copy(Type t, Value* v);

  // These functions have the same name as the corresponding roots of the
  // google::protobuf methods.
  Type GetRepeated(uint32 i) const;
  Type Get() const;

  void Set(Type t);
  void SetRepeated(uint32 i, Type t);

  void Add(Type t);

  virtual void copyFrom(const Value& v)            { Set(copy(v));  }
  virtual void copyFrom(uint32 i, const Value& v)  { SetRepeated(i, copy(v)); }
  virtual void copyTo(Value* v) const              { copy(Get(), v); }
  virtual void copyTo(uint32 i, Value* v) const    { copy(GetRepeated(i), v); }
  virtual void add(const Value& v)                 { Add(copy(v)); }

  virtual Typer* clone(google::protobuf::Message* m,
                       const FieldDescriptor* f) const {
    return new TypedTyper<Type>(m, f);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TypedTyper);
};

}  // namespace typer
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_TYPEDTYPER__
