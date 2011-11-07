#include "rec/data/Value.h"
#include "rec/data/proto/MessageField.h"
#include "rec/data/proto/TypedOperations.h"

namespace rec {
namespace data {

bool copyTo(const MessageField& f, ValueProto* value) {
  if (!f.field_) {
    value->set_message_f(pmessage(*f.message_));
    return true;
  }

  if (f.type_ == MessageField::SINGLE)
    return typer::copyTo(*f.message_, f.field_, value);

  if (f.index_ >= 0)
    return typer::copyTo(*f.message_, f.field_, f.index_, value);

  LOG(ERROR) << "copyTo failed with no index " << f.message_->GetTypeName();
  return false;
}


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

  LOG(ERROR) << "Can't add to self";
  return false;
}

bool removeLast(MessageField* f) {
  if (f->field_ && f->type_ == MessageField::REPEATED) {
    f->message_->GetReflection()->RemoveLast(f->message_, f->field_);
    return true;
  }

  LOG(ERROR) << "Can't remove last of self";
  return false;
}

namespace single {

namespace set {

bool apply(MessageField* field, const Operation& op) {
  if (op.value_size() != 1) {
    LOG(ERROR) << "Can only set one value at a time";
    return false;
  }
  return copyFrom(field, op.value(0));
}

bool undo(MessageField* f, const Operation& op, Operation* undo) {
  bool isSet = !f->field_ || f->type_ == MessageField::INDEXED || hasValue(*f);
  undo->set_command(isSet ? Operation::SET : Operation::CLEAR);

  return !isSet || copyTo(*f, undo->add_value());
}

}  // namespace set

namespace clear {

bool apply(MessageField* field, const Operation&) {
  field->message_->Clear();
  return true;
}

bool undo(MessageField* field, const Operation& operation, Operation* undo) {
  undo->set_command(Operation::SET);
  undo->clear_value();
  return copyTo(*field, undo->add_value());
}

}  // namespace clear

}  // namespace single

namespace repeated {

namespace add {

bool apply(MessageField* field, const Operation& op) {
  for (int i = 0; i < op.value_size(); ++i) {
    if (!addFrom(field, op.value(i)))
      return false;
  }
  return true;
}

bool undo(MessageField* f, const Operation& op, Operation* undo) {
  undo->set_command(Operation::REMOVE);
  undo->set_remove(op.value_size());
  return true;
}

}  // namespace add

namespace swap {

bool apply(MessageField* field, const Operation& op) {
  if (!field) {
    LOG(ERROR) << "Can't swap repeated on self";
    return false;
  }
  int s1 = op.swap1(), s2 = op.swap2();
  int size = getSize(*field);

  if (s1 < 0 || s2 < 0 || s1 >= size || s2 >= size) {
    LOG(ERROR) << "Can't swap positions " << s1 << "," << s2 << ": " << size;
    return false;
  } else {
    Message* m = field->message_;
    m->GetReflection()->SwapElements(m, field->field_, s1, s2);
    return true;
  }
}

bool undo(MessageField* field, const Operation& op, Operation* undo) {
  *undo = op;
  return true;
}

} // namespace swap

namespace remove {

int removeCount(MessageField* field, const Operation& op) {
  return (op.command() == Operation::CLEAR) ? field->repeatCount_ : op.remove();
}

bool apply(MessageField* field, const Operation& operation) {
  int toRemove = removeCount(field, operation);
  Message* msg = field->message_;
  for (int i = 0; i < toRemove; ++i)
    msg->GetReflection()->RemoveLast(msg, field->field_);
  return true;
}

bool undo(MessageField* field, const Operation& operation, Operation* undo) {
  int toRemove = removeCount(field, operation);
  undo->set_command(Operation::APPEND);

  MessageField f = *field;
  f.index_ = f.repeatCount_ - toRemove;
  for (; f.index_ < f.repeatCount_; ++f.index_) {
    if (!copyTo(f, undo->add_value())) {
      LOG(ERROR) << "Couldn't copy value to " << undo->ShortDebugString();
      return false;
    }
  }
  return true;
}

}  // namespace remove

}  // namespace repeated

typedef bool (*Applier)(MessageField*, const Operation&);
typedef bool (*Undoer)(MessageField*, const Operation&, Operation*);

static Applier appliers[Operation::COMMAND_COUNT][MessageField::TYPE_COUNT] = {
  {NULL,       &repeated::add::apply,     NULL},
  {NULL,       &repeated::remove::apply,   &single::clear::apply},
  {NULL,       &repeated::remove::apply,  NULL},
  {&single::set::apply,  NULL,            &single::set::apply},
  {NULL,       &repeated::swap::apply,    NULL},
};

static Undoer undoers[Operation::COMMAND_COUNT][MessageField::TYPE_COUNT] = {
  {NULL,       &repeated::add::undo,     NULL},
  {NULL,       &repeated::remove::undo,   &single::clear::undo},
  {NULL,       &repeated::remove::undo,  NULL},
  {&single::set::undo,  NULL,            &single::set::undo},
  {NULL,       &repeated::swap::undo,    NULL},
};


bool valid(const Operation::Command c, const MessageField::Type t) {
  return c >= Operation::APPEND && c <= Operation::SWAP
    && t >= MessageField::INDEXED && t <= MessageField::SINGLE;
}

}  // namespace

bool apply(MessageField* field, const Operation& op) {
  const Operation::Command c = op.command();
  const MessageField::Type t = field->type_;
  return valid(c, t) && appliers[c][t](field, op);
}

bool undo(MessageField* field, const Operation& op, Operation* undo) {
  const Operation::Command c = op.command();
  const MessageField::Type t = field->type_;
  return valid(c, t) && undoers[c][t](field, op, undo);
}

}  // namespace data
}  // namespace rec
