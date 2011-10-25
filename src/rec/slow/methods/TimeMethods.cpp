#include "rec/slow/methods/TimeMethods.h"
#include "rec/slow/Model.h"

namespace rec {
namespace slow {
namespace methods {

void TimeMethods::jumpToTimeSelection(const block::BlockSet& ts,
                                      Samples<44100> time) {
  if (!ts.empty()) {
    block::BlockSet::const_iterator i = ts.begin();
    for (; i != ts.end(); ++i) {
      if (time < i->second) {
        if (time < i->first)
          model()->jumpToTime(i->first);
        return;
      }
    }
    model()->jumpToTime(ts.begin()->first);
  }
}

void TimeMethods::setCursorTime(int index, RealTime t, const VirtualFile& f) {
  if (index < 0) {
    model()->jumpToTime(t);
  } else {
    LoopPointList loops(data::get<LoopPointList>(f));
    loops.mutable_loop_point(index)->set_time(t);
    data::set(loops, f);
  }
}

}  // namespace methods
}  // namespace slow
}  // namespace rec
