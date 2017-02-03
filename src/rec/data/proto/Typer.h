#pragma once

#include "rec/data/proto/Types.h"
#include "rec/data/proto/Comparer.h"

namespace google { namespace protobuf { class FieldDescriptor; }}

namespace rec {
namespace data {
namespace typer {

class Typer {
  public:
    Typer(Message* m, const google::protobuf::FieldDescriptor* f) : field_(f), msg_(m) {}
    virtual ~Typer() {}
    virtual Typer* clone(Message* m, const google::protobuf::FieldDescriptor* f) const = 0;

    virtual void copyTo(ValueProto* v) const = 0;
    virtual void copyTo(uint32 i, ValueProto* v) const = 0;

    virtual void copyFrom(const data::Value& v) = 0;
    virtual void copyFrom(uint32 i, const data::Value& v) = 0;

    virtual void add(const data::Value& v) = 0;
    virtual void clear() = 0;

    virtual bool Equals(const Message& m, const Comparer& cmp) const = 0;
    virtual bool Equals(const Message& m, uint32 i, const Comparer& cmp) const = 0;

  protected:
    const google::protobuf::Reflection& ref() const {
        return *msg_->GetReflection();
    }

    const google::protobuf::FieldDescriptor* field_;
    Message* msg_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Typer);
};

}  // namespace typer
}  // namespace data
}  // namespace rec
