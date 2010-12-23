#include <vector>

#include <google/protobuf/descriptor.h>

#include "rec/data/proto/Types.h"
#include "rec/data/proto/Typer.h"
#include "rec/data/proto/TypedTyper.h"

namespace rec {
namespace proto {
namespace typer {

namespace {

const Typer* const TYPE_LIST[FieldDescriptor::MAX_TYPE] = {
  NULL,
  new TypedTyper<double>(NULL, NULL),
  new TypedTyper<float>(NULL, NULL),
  new TypedTyper<int64>(NULL, NULL),
  new TypedTyper<uint64>(NULL, NULL),
  new TypedTyper<int32>(NULL, NULL),
  new TypedTyper<fixed64>(NULL, NULL),
  new TypedTyper<fixed32>(NULL, NULL),
  new TypedTyper<bool>(NULL, NULL),
  new TypedTyper<string>(NULL, NULL),
  NULL,  // new TypedTyper<group>(NULL, NULL),
  new TypedTyper<pmessage>(NULL, NULL),
  new TypedTyper<bytes>(NULL, NULL),
  new TypedTyper<uint32>(NULL, NULL),
  new TypedTyper<penum>(NULL, NULL),
  new TypedTyper<sfixed32>(NULL, NULL),
  new TypedTyper<sfixed64>(NULL, NULL),
  new TypedTyper<sint32>(NULL, NULL),
};

class STyper : public ptr<Typer> {
 public:
  STyper(Message* m, const FieldDescriptor* f) {
    FieldDescriptor::Type t = f ? f->type() : FieldDescriptor::TYPE_MESSAGE;
    this->reset(TYPE_LIST[t]->clone(m, f));
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(STyper);
};

} // namespace

bool copyTo(const Message& m, const FieldDescriptor* f, Value* v) {
  STyper((Message*) &m, f)->copyTo(v);
  return true;
}

bool copyTo(const Message& m, const FieldDescriptor* f, uint32 i, Value* v) {
  STyper((Message*) &m, f)->copyTo(i, v);
  return true;
}

bool copyFrom(Message* m, const FieldDescriptor* f, const Value& v) {
  STyper(m, f)->copyFrom(v);
  return true;
}

bool copyFrom(Message* m, const FieldDescriptor* f, uint32 i, const Value& v) {
  STyper(m, f)->copyFrom(i, v);
  return true;
}

bool add(Message* m, const FieldDescriptor* f, const Value& v) {
  STyper(m, f)->add(v);
  return true;
}

}  // namespace typer
}  // namespace proto
}  // namespace rec
