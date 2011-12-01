#include "rec/slow/CurrentTime.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/slow/BufferFiller.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

using widget::waveform::ZoomProto;

const int PRELOAD = 10000;

static const double IDEAL_CURSOR_POSITION_RATIO = 0.10;
static const double MAX_CURSOR_POSITION_RATIO_CHANGE = 0.005;

CurrentTime::CurrentTime(Instance* i)
    : HasInstance(i), time_(0), jumpTime_(-1), length_(0),
      followCursor_(false) {
}

void CurrentTime::operator()(Samples<44100> t) {
  Lock l(lock_);
  time_ = t;

  // Now compute an ideal zoom for this time.
  ZoomProto z = zoom_;
  Samples<44100> w = z.end() - z.begin();
  Samples<44100> off = static_cast<int64>(IDEAL_CURSOR_POSITION_RATIO * w);
  z.set_begin(t - off);
  z.set_end(t + w - off);

  if (static_cast<int64>(z.end()) >= length_) {
    z.set_begin(z.begin() - (z.end() - length_));
    z.set_end(length_);
  }

  if (z.begin() < 0) {
    z.set_end(z.end() - z.begin());
    z.set_begin(0);
  }

  DataListener<ZoomProto>::setProto(z);
}

void CurrentTime::onDataChange(const ZoomProto& zoom) {
  Lock l(lock_);
  zoom_ = zoom;
}

void CurrentTime::onDataChange(const LoopPointList& loops) {
  Lock l(lock_);
  length_ = loops.length();
  if (loops.has_length()) {
    timeSelection_ = audio::getTimeSelection(loops);
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
  } else {
    timeSelection_.clear();
    jumpToTime(0);
  }
}

void CurrentTime::onDataChange(const GuiSettings& settings) {
  Lock l(lock_);
  followCursor_ = settings.follow_cursor();
}

void CurrentTime::setCursorTime(int index, Samples<44100> t) {
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
    Lock l(lock_);
    if (!block::contains(timeSelection(), pos)) {
      LOG(ERROR) << "Tried to jump to position outside selection " << pos;
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

