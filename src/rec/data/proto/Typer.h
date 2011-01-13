#ifndef __REC_DATA_PROTO_TYPER__
#define __REC_DATA_PROTO_TYPER__

#include "rec/data/proto/Types.h"
#include "rec/data/proto/Comparer.h"

namespace rec {
namespace proto {
namespace typer {

class Typer {
 public:
  Typer(Message* m, const FieldDescriptor* f)
      : field_(f), msg_(m) {
  }
  virtual ~Typer() {}
  virtual Typer* clone(Message* m, const FieldDescriptor* f) const = 0;

  virtual void copyTo(Value* v) const = 0;
  virtual void copyTo(uint32 i, Value* v) const = 0;

  virtual void copyFrom(const Value& v) = 0;
  virtual void copyFrom(uint32 i, const Value& v) = 0;

  virtual void add(const Value& v) = 0;
  virtual void clear() = 0;

  virtual bool equals(const Message& m, const Comparer& cmp) const = 0;
  virtual bool equals(const Message& m, uint32 i, const Comparer& cmp) const = 0;

 protected:
  const Reflection& ref() const { return *msg_->GetReflection(); }

  const FieldDescriptor* field_;
  Message* msg_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Typer);
};

}  // namespace typer
}  // namespace proto
}  // namespace rec

#endif  // __REC_DATA_PROTO_TYPER__
