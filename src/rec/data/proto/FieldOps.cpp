#include "rec/data/proto/FieldOps.h"

#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/MessageField.h"
#include "rec/data/proto/TypedOperations.h"

namespace rec {
namespace data {

static void logError(const string& error, const Address& a, const Message& m) {
    if (!error.empty()) {
        LOG(DFATAL) << error << ":" << a.ShortDebugString() << ", "
                                << m.ShortDebugString();
    }
}

string getMessageField(const Address& a, const Message& m, ValueProto* value) {
    MessageField f = createMessageField(a, m);
    if (!f.error_.empty())
        return f.error_;

    if (!f.field_) {
        value->set_message_f(pmessage(*f.message_));
        return "";
    }

    if (f.type_ == MessageField::SINGLE)
        return typer::copyTo(*f.message_, f.field_, value) ? "" : "type::copyTo";

    if (f.index_ >= 0)
        return typer::copyTo(*f.message_, f.field_, f.index_, value) ? "": "type::copyTo";

    return "copyTo failed with no index: " +
        (f.message_ ? f.message_->GetTypeName() : "NO MESSAGE");
}

string setMessageField(const Address& a, Message* m, const ValueProto& value) {
    MessageField f = createMessageField(a, *m);
    if (!f.field_) {
        if (value.has_message_f())
            return pmessage(value.message_f()).Parse(f.message_) ? "" :
                "Couldn't parse message";

        return "The Value contained no message field.";
    }

    bool success = (f.type_ == MessageField::SINGLE) ?
        typer::copyFrom(f.message_, f.field_, value) :
        typer::copyFrom(f.message_, f.field_, f.index_, value);
    return success ? "" : "Couldn't copyFrom";
}

Value getMessageFieldOrDie(const Address& a, const Message& m) {
    Value v;
    logError(getMessageField(a, m, &v), a, m);
    return v;
}

void setMessageFieldOrDie(const Address& a, Message* m, const ValueProto& v) {
    logError(setMessageField(a, m, v), a, *m);
}

}  // namespace data
}  // namespace rec
