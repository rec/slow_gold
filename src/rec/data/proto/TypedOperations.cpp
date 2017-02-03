#include <google/protobuf/descriptor.h>

#include "rec/base/arraysize.h"
#include "rec/data/proto/Types.h"
#include "rec/data/proto/TypedOperations.h"
#include "rec/data/proto/TypedTyper.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {
namespace typer {

using namespace rec::data;

namespace {

const Typer* const TYPE_LIST[FieldDescriptor::MAX_TYPE] = {
    nullptr,
    new TypedTyper<double>(nullptr, nullptr),
    new TypedTyper<float>(nullptr, nullptr),
    new TypedTyper<int64>(nullptr, nullptr),
    new TypedTyper<uint64>(nullptr, nullptr),
    new TypedTyper<int32>(nullptr, nullptr),
    new TypedTyper<fixed64>(nullptr, nullptr),
    new TypedTyper<fixed32>(nullptr, nullptr),
    new TypedTyper<bool>(nullptr, nullptr),
    new TypedTyper<string>(nullptr, nullptr),
    nullptr,  // new TypedTyper<group>(nullptr, nullptr),
    new TypedTyper<pmessage>(nullptr, nullptr),
    new TypedTyper<bytes>(nullptr, nullptr),
    new TypedTyper<uint32>(nullptr, nullptr),
    new TypedTyper<penum>(nullptr, nullptr),
    new TypedTyper<sfixed32>(nullptr, nullptr),
    new TypedTyper<sfixed64>(nullptr, nullptr),
    new TypedTyper<sint32>(nullptr, nullptr),
};

struct TypeListDeleter {
    ~TypeListDeleter() {
        stl::deletePointers(TYPE_LIST, TYPE_LIST + arraysize(TYPE_LIST));
    }
};

static TypeListDeleter deleter;

class STyper : public std::unique_ptr<Typer> {
  public:
    STyper(Message* m, const FieldDescriptor* f) {
        FieldDescriptor::Type t = f ? f->type() : FieldDescriptor::TYPE_MESSAGE;
        reset(TYPE_LIST[t]->clone(m, f));
    }

  private:
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(STyper);
};

} // namespace

bool copyTo(const Message& m, const FieldDescriptor* f, ValueProto* v) {
    STyper(const_cast<Message*>(&m), f)->copyTo(v);
    return true;
}

bool copyTo(const Message& m, const FieldDescriptor* f, uint32 i, ValueProto* v) {
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

bool equals(const Message& x, const Message& y, const FieldDescriptor* f,
                        int i, const Comparer& cmp) {
    return STyper(const_cast<Message*>(&x), f)->Equals(y, i, cmp);
}

bool equals(const Message& x, const Message& y, const FieldDescriptor* field,
                        const Comparer& cmp) {
    if (!field->is_repeated())
        return STyper(const_cast<Message*>(&x), field)->Equals(y, cmp);

    int len = x.GetReflection()->FieldSize(x, field);
    if (len != y.GetReflection()->FieldSize(y, field))
        return false;

    for (int i = 0; i < len; ++i) {
        if (!equals(x, y, field, i, cmp))
            return false;
    }

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
}  // namespace data
}  // namespace rec
