#include <vector>

#include <google/protobuf/descriptor.h>

#include "rec/data/proto/Types.h"
#include "rec/data/proto/TypedOperations.h"
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
  STyper(const_cast<Message*>(&m), f)->copyTo(v);
  return true;
}

bool copyTo(const Message& m, const FieldDescriptor* f, uint32 i, Value* v) {
  STyper(const_cast<Message*>(&m), f)->copyTo(i, v);
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

bool equals(const Message& m1, const Message& m2, const FieldDescriptor* f,
            int i, const Comparer& cmp) {
  return STyper(const_cast<Message*>(&m1), f)->equals(m2, i, cmp);
}

bool equals(const Message& x, const Message& y, const FieldDescriptor* field,
            const Comparer& cmp) {
  DLOG(INFO) << "! " << field->full_name();
  if (!field->is_repeated())
    return STyper(const_cast<Message*>(&x), field)->equals(y, cmp);

  int len = x.GetReflection()->FieldSize(x, field);
  if (len != y.GetReflection()->FieldSize(y, field))
    return false;

  for (int i = 0; i < len; ++i)
    if (!equals(x, y, field, i, cmp))
      return false;
  return true;
}

bool equals(const Message& x, const Message& y, const Comparer& cmp) {
  const google::protobuf::Descriptor* desc = x.GetDescriptor();
  if (desc != y.GetDescriptor())
    return false;

  for (int i = 0; i < desc->field_count(); ++i) {
    if (!equals(x, y, desc->field(i), cmp))
      return false;
  }

  return true;
}


}  // namespace typer
}  // namespace proto
}  // namespace rec
