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
  for (int i = 0; i < loops.loop_point_size() - 1; ++i) {
    if (loops.loop_point(i).selected())
      ++count;
  }
  return count;
}

int getSegment(const LoopPointList& loops, RealTime time) {
  for (int i = 1; i < loops.loop_point_size() - 1; ++i) {
    if (time < loops.loop_point(i).time())
      return i - 1;
  }
  return 0;
}

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(data::get<LoopPointList>(i->file())),
    time_(i->player_->getNextReadPosition()),
    length_(i->player_->length()),
    selection_(audio::getTimeSelection(loops_, length_)),
    selectionCount_(getSelectionCount(loops_)),
    segment_(getSegment(loops_, time_)) {
}

}  // namespace slow
}  // namespace rec

