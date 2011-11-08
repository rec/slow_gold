#include "rec/data/Grouper.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"

namespace rec {
namespace data {

static const uint64 MAX_GROUP_TIME = 1000;

bool groupCloseActions(Action* t, const Action* f, const Editable* e) {
  uint64 ts = f ? f->timestamp() : juce::Time::currentTimeMillis();

  if (!near(t->timestamp(), ts, MAX_GROUP_TIME))
    return false;

  if (!f)
    return true;

  if (!equals(t->file(), f->file()) || t->type_name() != f->type_name())
    return false;

  t->set_timestamp(f->timestamp());
  t->mutable_operations()->Clear();
  Operation* op = t->mutable_operations()->add_operation();
  op->set_command(Operation::SET);
  ptr<Message> m(e->clone());
  op->add_value()->CopyFrom(Value(*m));

  return true;
}

}  // namespace data
}  // namespace rec
