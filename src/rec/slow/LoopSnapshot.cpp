#include "rec/slow/LoopSnapshot.h"

#include "rec/util/LoopPoint.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/BufferFiller.h"

namespace rec {
namespace slow {

LoopSnapshot::LoopSnapshot(Instance* i)
  : instance_(i),
    loops_(data::get<LoopPointList>(i->file())),
    time_(i->player_->getNextReadPosition()),
    selection_(audio::getTimeSelection(loops_)),
    selectionCount_(audio::getSelectionCount(loops_)),
    segment_(audio::getSegment(loops_, time_)) {
}

}  // namespace slow
}  // namespace rec

