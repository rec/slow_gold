#include "rec/data/Grouper.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"

namespace rec {
namespace data {

static const uint64 MAX_GROUP_TIME = 1000;


bool groupCloseActions(Action* to, const Action* from, const Editable* e) {
  uint64 ts = from ? from->timestamp() : juce::Time::currentTimeMillis();

  if (!near(to->timestamp(), ts, MAX_GROUP_TIME))
    return false;

  if (!from) {
    DLOG(INFO) << "isGroup true!!";
    return true;
  }

  bool isGroup = equals(to->file(), from->file()) &&
    to->type_name() == from->type_name();

  if (isGroup) {
    to->set_timestamp(from->timestamp());
    to->mutable_operations()->Clear();
    Operation* op = to->mutable_operations()->add_operation();
    op->set_command(Operation::SET);
    ptr<Message> m(e->clone());
    op->add_value()->CopyFrom(Value(*m));
  }

  DLOG(INFO) << "isGroup " << isGroup;
  return isGroup;
}

}  // namespace data
}  // namespace rec
