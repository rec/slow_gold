#include "rec/data/proto/FieldOps.h"

#include "rec/data/Value.h"
#include "rec/data/proto/MessageField.h"
#include "rec/data/proto/TypedOperations.h"

namespace rec {
namespace data {

namespace {

bool copyFrom(MessageField* f, const Value& value) {
  if (!f->field_) {
    if (value.has_message_f())
      return pmessage(value.message_f()).Parse(f->message_);

    LOG(ERROR) << "The Value contained no message field.";
    return false;
  }

  return (f->type_ == MessageField::SINGLE) ?
    typer::copyFrom(f->message_, f->field_, value) :
    typer::copyFrom(f->message_, f->field_, f->index_, value);
}

bool addFrom(MessageField* f, const Value& value) {
  if (f->field_)
    return typer::add(f->message_, f->field_, value);

  LOG(DFATAL) << "Can't add to self";
  return false;
}

bool removeLast(MessageField* f) {
  if (f->field_ && f->type_ == MessageField::REPEATED) {
    f->message_->GetReflection()->RemoveLast(f->message_, f->field_);
    return true;
  }

  LOG(DFATAL) << "Can't remove last of self";
  return false;
}

bool setSingle(MessageField* field, const Operation& op) {
  if (op.value_size() != 1) {
    LOG(DFATAL) << "Can only set one value at a time";
    return false;
  }
  return copyFrom(field, op.value(0));
}

bool clearSingle(MessageField* field, const Operation&) {
  field->message_->Clear();
  return true;
}

bool addRepeated(MessageField* field, const Operation& op) {
  for (int i = 0; i < op.value_size(); ++i) {
    if (!addFrom(field, op.value(i)))
      return false;
  }
  return true;
}

bool swapRepeated(MessageField* field, const Operation& op) {
  if (!field) {
    LOG(DFATAL) << "Can't swap repeated on self";
    return false;
  }
  int s1 = op.swap1(), s2 = op.swap2();
  int size = getSize(*field);

  if (s1 < 0 || s2 < 0 || s1 >= size || s2 >= size) {
    LOG(DFATAL) << "Can't swap positions " << s1 << "," << s2 << ": " << size;
    return false;
  } else {
    Message* m = field->message_;
    m->GetReflection()->SwapElements(m, field->field_, s1, s2);
    return true;
  }
}

bool removeRepeated(MessageField* field, const Operation& op) {
  int toRemove = (op.command() == Operation::CLEAR) ? field->repeatCount_ :
    op.remove();
  Message* msg = field->message_;
  for (int i = 0; i < toRemove; ++i)
    msg->GetReflection()->RemoveLast(msg, field->field_);
  return true;
}

typedef bool (*Applier)(MessageField*, const Operation&);

static Applier appliers[Operation::COMMAND_COUNT][MessageField::TYPE_COUNT] = {
  {NULL,       &addRepeated,     NULL},
  {NULL,       &removeRepeated,   &clearSingle},
  {NULL,       &removeRepeated,  NULL},
  {&setSingle,  NULL,            &setSingle},
  {NULL,       &swapRepeated,    NULL},
};

bool valid(const Operation::Command c, const MessageField::Type t) {
  return c >= Operation::APPEND && c <= Operation::SWAP
    && t >= MessageField::INDEXED && t <= MessageField::SINGLE;
}

}  // namespace

bool copyTo(const MessageField& f, ValueProto* value) {
  if (!f.field_) {
    value->set_message_f(pmessage(*f.message_));
    return true;
  }

  if (f.type_ == MessageField::SINGLE)
    return typer::copyTo(*f.message_, f.field_, value);

  if (f.index_ >= 0)
    return typer::copyTo(*f.message_, f.field_, f.index_, value);

  LOG(DFATAL) << "copyTo failed with no index " << f.message_->GetTypeName();
  return false;
}


bool apply(MessageField* field, const Operation& op) {
  const Operation::Command c = op.command();
  const MessageField::Type t = field->type_;
  return valid(c, t) && appliers[c][t](field, op);
}

}  // namespace data
}  // namespace rec
