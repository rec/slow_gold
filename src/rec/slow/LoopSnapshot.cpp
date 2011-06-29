#include "rec/slow/LoopSnapshot.h"

#include "rec/audio/source/Player.h"
#include "rec/slow/Model.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(i->model_->loopPointList()),
    time_(i->player_->getNextReadPosition()),
    selection_(i->model_->timeSelection()),
    loopSize_(loops_.loop_point_size()),
    selectionCount_(0),
    segment_(-1) {

  for (int i = 0; loopSize_; ++i) {
    const LoopPoint& point = loops_.loop_point(i);
    if (time_ < point.time() && segment_ < 0)
      segment_ = i - 1;
    if (point.selected())
      selectionCount_++;
  }
  if (!selectionCount_)
    selectionCount_ = loopSize_ -1;

  next_ = segment_ + 1;
  if (next_ >= loopSize_)
    next_ = 0;
  previous_ = segment_ - 1;
  if (previous_ < 0)
    previous_ = loopSize_ - 1;
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

