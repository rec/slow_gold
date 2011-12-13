#include "rec/data/Grouper.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"

namespace rec {
namespace data {

static const uint64 MAX_GROUP_TIME = 10000;
static const bool GROUP_BY_TIME = true;

bool actionGrouper(const Action& f, Action* t, const Editable* e) {
  if (GROUP_BY_TIME && !near(t->timestamp(), f.timestamp(), MAX_GROUP_TIME))
    return false;

  if (!equals(t->file(), f.file()) || t->type_name() != f.type_name())
    return false;

  t->set_timestamp(f.timestamp());
  t->mutable_operations()->Clear();
  Operation* op = t->mutable_operations()->add_operation();
  op->set_command(Operation::SET);
  ptr<Message> m(e->clone());
  op->add_value()->CopyFrom(Value(*m));

  return true;
}

}  // namespace data
}  // namespace rec
