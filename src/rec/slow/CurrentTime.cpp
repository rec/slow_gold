#include "rec/slow/CurrentTime.h"
#include "rec/slow/Model.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

void CurrentTime::jumpToTimeSelection(const LoopPointList& loops,
                                      Samples<44100> time) {
  timeSelection_ = audio::getTimeSelection(loops, player()->length());
  if (!timeSelection_.empty()) {
    block::BlockSet::const_iterator i = timeSelection_.begin();
    for (; i != timeSelection_.end(); ++i) {
      if (time < i->second) {
        if (time < i->first)
          model()->jumpToTime(i->first);
        return;
      }
    }
    model()->jumpToTime(timeSelection_.begin()->first);
  }
}

void CurrentTime::setCursorTime(int index, RealTime t) {
  if (index < 0) {
    model()->jumpToTime(t);
  } else {
    LoopPointList loops(data::get<LoopPointList>(file()));
    loops.mutable_loop_point(index)->set_time(t);
    data::set(loops, file());
  }
}

}  // namespace slow
}  // namespace rec

