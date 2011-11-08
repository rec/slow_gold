#include "rec/data/Grouper.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"

namespace rec {
namespace data {

bool groupCloseActions(Action* to, const Action* from, const Editable* e) {
  if (!to)
    return true;

  static const uint64 MAX_GROUP_TIME = 1000;
  bool isGroup = near(to->timestamp(), from->timestamp(), MAX_GROUP_TIME) &&
    equals(to->file(), from->file()) &&
    to->type_name() == from->type_name();

  if (isGroup) {
    to->set_timestamp(from->timestamp());
    to->mutable_operations()->Clear();
    Operation* op = to->mutable_operations()->add_operation();
    op->set_command(Operation::SET);
    ptr<Message> m(e->clone());
    op->add_value()->CopyFrom(Value(*m));
  }

  return isGroup;
}

}  // namespace data
}  // namespace rec
