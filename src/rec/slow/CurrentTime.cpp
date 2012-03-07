#include "rec/slow/CurrentTime.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

using widget::waveform::ZoomProto;

static const int PRELOAD = 10000;

static const double IDEAL_CURSOR_POSITION_RATIO = 0.05;
static const double MIN_CURSOR_RATIO_CHANGE = 0.95;
static const Samples<44100> MIN_ZOOM_TIME = 44100 / 2;

CurrentTime::CurrentTime(Instance* i)
    : HasInstance(i), time_(0), jumpTime_(-1), length_(0),
      followCursor_(false) {
}

void CurrentTime::startListening() {
  DataListener<LoopPointList>::startListening();
  DataListener<widget::waveform::ZoomProto>::startListening();
  GlobalDataListener<GuiSettings>::startListening();
}

void CurrentTime::operator()(Samples<44100> t) {
  return;
  Lock l(lock_);
  time_ = t;

  if (!followCursor_ || llabs(t - zoomTime_) < MIN_ZOOM_TIME || !isPlaying())
    return;

  zoomTime_ = t;

  // Now compute an ideal zoom for this time.
  Samples<44100> width = zoom_.end() - zoom_.begin();
  Samples<44100> off = static_cast<int64>(MIN_CURSOR_RATIO_CHANGE * width);
  if (t >= zoom_.begin() && t <= zoom_.begin() + off)
    return;
  ZoomProto z = zoom_;
  z.set_begin(t - static_cast<int64>(IDEAL_CURSOR_POSITION_RATIO * width));

  if (z.begin() + width > length_)
    z.set_begin(length_ - width);

  if (z.begin() < 0)
    z.set_begin(0);

  z.set_end(z.begin() + width);
  DataListener<ZoomProto>::setProto(z);
}

void CurrentTime::operator()(const ZoomProto& zoom) {
  Lock l(lock_);
  zoom_ = zoom;
}

void CurrentTime::operator()(const LoopPointList& loops) {
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

void CurrentTime::operator()(const GuiSettings& settings) {
  Lock l(lock_);
  followCursor_ = settings.follow_cursor();
}

void CurrentTime::setCursorTime(Samples<44100> t, int index, bool isTimeCursor) {
  if (isTimeCursor) {
    jumpToTime(t);
  } else {
    LoopPointList loops(data::getProto<LoopPointList>(file()));
    loops.mutable_loop_point(index)->set_time(t);
    data::setProto(loops, file());
  }
}

void CurrentTime::jumpToTime(Samples<44100> pos) {
  using audio::util::FillableFrameBuffer;
  {
    Lock l(lock_);
    if (isPlaying() &&
        !(timeSelection_.empty() || block::contains(timeSelection(), pos))) {
      return;
    }

    FillableFrameBuffer<short, 2>* buf =
      bufferFiller()->trackBuffer()->buffer();
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

