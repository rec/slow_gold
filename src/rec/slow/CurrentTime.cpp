#include "rec/slow/CurrentTime.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using audio::util::BufferedReader;
using widget::waveform::Zoom;
using widget::waveform::MIN_ZOOM_TIME;

static const int PRELOAD = 10000;

static const double IDEAL_CURSOR_POSITION_RATIO = 0.05;
static const double MIN_CURSOR_RATIO_CHANGE = 0.80;

CurrentTime::CurrentTime(Instance* i)
    : HasInstance(i), time_(0), requestedTime_(-1), zoomTime_(0), length_(0),
      followCursor_(false) {
}

void CurrentTime::init() {
  DataListener<LoopPointList>::init();
  DataListener<widget::waveform::Zoom>::init();
  GlobalDataListener<GuiSettings>::init();
}

void CurrentTime::operator()(Samples<44100> t) {
  Zoom zoom;
  {
    Lock l(lock_);
    time_ = t;

    if (!followCursor_ || llabs(t - zoomTime_) < MIN_ZOOM_TIME || !isPlaying())
      return;

    zoomTime_ = t;
    zoom = zoom_;
  }

  Samples<44100> end = zoom.has_end() ? Samples<44100>(zoom.end()) : length_;
  // Now compute an ideal zoom for this time.
  Samples<44100> width = end - zoom.begin();
  Samples<44100> off = static_cast<int64>(MIN_CURSOR_RATIO_CHANGE * width);
  if (t >= zoom.begin() && t <= zoom.begin() + off)
    return;
  zoom.set_begin(t - static_cast<int64>(IDEAL_CURSOR_POSITION_RATIO * width));

  if (zoom.begin() + width > length_)
    zoom.set_begin(length_ - width);

  if (zoom.begin() < 0)
    zoom.set_begin(0);

  zoom.set_end(zoom.begin() + width);
  DataListener<Zoom>::setProto(zoom);
}

void CurrentTime::operator()(const Zoom& zoom) {
  if (zoom.has_end()) {
    Lock l(lock_);
    zoom_ = zoom;
  }
}

void CurrentTime::operator()(const LoopPointList& loops) {
  Samples<44100> time;
  bool jump = true;
  {
    Lock l(lock_);
    length_ = loops.length();
    if (loops.has_length()) {
      timeSelection_ = audio::getTimeSelection(loops);
      if (!timeSelection_.empty()) {
        block::BlockSet::const_iterator i = timeSelection_.begin();
        for (; i != timeSelection_.end(); ++i) {
          if (time_ < i->second) {
            if (time_ < i->first)
              time = i->first;
            else
              jump = false;
            break;
          }
        }
        time = timeSelection_.begin()->first;
      }
    } else {
      timeSelection_.clear();
      time = 0;
    }
  }
  if (jump)
    jumpToTime(time);
}

void CurrentTime::operator()(const GuiSettings& settings) {
  Lock l(lock_);
  followCursor_ = settings.follow_cursor();
}

void CurrentTime::jumpToTime(Samples<44100> pos) {
  {
    Lock l(lock_);
    if (isPlaying() &&
        !(timeSelection_.empty() || block::contains(timeSelection_, pos))) {
      return;
    }

    BufferedReader* reader = bufferFiller()->reader();
    requestedTime_ = pos;
    if (reader && !reader->hasFilled(block::Block(pos, pos + PRELOAD))) {
      reader->setNextFillPosition(pos);
      if (player()->state())
        return;
    }
    requestedTime_ = -1;
  }

	player()->setNextReadPosition(pos);
}

}  // namespace slow
}  // namespace rec

