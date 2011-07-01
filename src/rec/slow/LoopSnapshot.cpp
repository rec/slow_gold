#include "rec/slow/LoopSnapshot.h"

#include "rec/audio/source/Player.h"
#include "rec/slow/Model.h"

namespace rec {
namespace slow {

#if 0
static int findUnselected(int loc, const LoopSnapshot* ls, int delta) {
  DCHECK(delta);
  int i = loc;
  while (true) {
    if (!ls->loops_.loop_point(i).selected())
      return i;
    i = ls->limit(i + delta);
    if (i == loc)
      return -1;
  }
}
#endif

int getSelectionCount(const LoopPointList& loops) {
  int count;
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (loops.loop_point(i).selected())
      ++count;
  }
  return count;
}

int getSegment(const LoopPointList& loops, RealTime time) {
  for (int i = 1; i < loops.loop_point_size(); ++i) {
    if (time < loops.loop_point(i).time())
      return i - 1;
  }
  return 0;
}

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(i->model_->loopPointList()),
    time_(i->player_->getNextReadPosition()),
    selection_(i->model_->timeSelection()),
    loopSize_(loops_.loop_point_size()),
    selectionCount_(getSelectionCount(loops_)),
    segment_(getSegment(loops_, time_)),
    previous_(limit(segment_ - 1)),
    next_(limit(segment_ + 1)),
    last_(loopSize_ - 1) {
}

bool LoopSnapshot::execute(Command cmd, const Map& snapMap) {
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

