#include "rec/slow/LoopSnapshot.h"

#include "rec/audio/source/Player.h"
#include "rec/slow/Model.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(i->model_->loopPointList()),
    time_(i->player_->getNextReadPosition()),
    selection_(i->model_->timeSelection()) {
}

bool LoopSnapshot::execute(command::Command::Type cmd, const Map& snapMap) {
  LoopSnapshot::Map::const_iterator i = snapMap.find(cmd);

  bool success = (i != snapMap.end() && (*(i->second))(this));
  if (success)
    persist::set(loops_, instance_->model_->file());
  else
    PlatformUtilities::beep();

  return success;
}


}  // namespace slow
}  // namespace rec

