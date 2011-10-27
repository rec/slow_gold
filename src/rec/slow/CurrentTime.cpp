#include "rec/slow/CurrentTime.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/slow/BufferFiller.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

const int PRELOAD = 10000;

void CurrentTime::onDataChange(const LoopPointList& loops) {
  timeSelection_ = audio::getTimeSelection(loops, player()->length());
  if (!timeSelection_.empty()) {
    block::BlockSet::const_iterator i = timeSelection_.begin();
    for (; i != timeSelection_.end(); ++i) {
      if (time_ < i->second) {
        if (time_ < i->first)
          jumpToTime(i->first);
        return;
      }
    }
    jumpToTime(timeSelection_.begin()->first);
  }
}

void CurrentTime::setCursorTime(int index, RealTime t) {
  if (index < 0) {
    jumpToTime(t);
  } else {
    LoopPointList loops(data::get<LoopPointList>(file()));
    loops.mutable_loop_point(index)->set_time(t);
    data::set(loops, file());
  }
}

void CurrentTime::jumpToTime(Samples<44100> pos) {
  using audio::util::FillableFrameBuffer;
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection(), pos)) {
      DLOG(ERROR) << "Tried to jump to position outside selection " << pos;
      return;
    }

    FillableFrameBuffer<short, 2>* buf =
      bufferFiller()->thumbnailBuffer()->buffer();
    jumpTime_ = pos;
    if (buf && !buf->hasFilled(block::Block(pos, pos + PRELOAD))) {
      buf->setNextFillPosition(pos);
      if (player()->state())
        return;
    }
    jumpTime_ = -1;
  }

	player()->setNextReadPosition(pos);
}

}  // namespace slow
}  // namespace rec

