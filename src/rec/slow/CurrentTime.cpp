#include "rec/slow/CurrentTime.h"

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/audio/util/Frame.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/slow/Components.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using audio::util::BufferedReader;
using widget::waveform::Zoom;
using namespace rec::widget::waveform;

static const double IDEAL_CURSOR_POSITION_RATIO = 0.05;
static const double MIN_CURSOR_RATIO_CHANGE = 0.80;

static const int PRELOAD = 10000;  // TODO:  duplicate code.

CurrentTime::CurrentTime(Instance* i)
    : HasInstance(i), time_(0), requestedTime_(-1), zoomTime_(0), length_(0),
      followCursor_(false) {
}

void CurrentTime::setTime(Samples<44100> t) {
  Viewport viewport;
  {
    Lock l(lock());
    time_ = t;

    if (!followCursor_ || llabs(t - zoomTime_) < MIN_ZOOM_TIME || !isPlaying())
      return;

    zoomTime_ = t;
    viewport = viewport_;
  }
  Zoom* zoom = viewport_.mutable_zoom();
  Samples<44100> end = zoom->has_end() ? Samples<44100>(zoom->end()) : length_;
  // Now compute an ideal zoom for this time.
  Samples<44100> width = end - zoom->begin();
  Samples<44100> off = static_cast<int64>(MIN_CURSOR_RATIO_CHANGE * width);
  if (t >= zoom->begin() && t <= zoom->begin() + off)
    return;
  zoom->set_begin(t - static_cast<int64>(IDEAL_CURSOR_POSITION_RATIO * width));

  if (zoom->begin() + width > length_)
    zoom->set_begin(length_ - width);

  if (zoom->begin() < 0)
    zoom->set_begin(0);

  zoom->set_end(zoom->begin() + width);
  DataListener<Viewport>::setProto(viewport, CANT_UNDO);
}

void CurrentTime::setViewport(const Viewport& viewport) {
  Samples<44100> time;
  bool jump = true;

  {
    Lock l(lock());
    viewport_ = viewport;
    const LoopPointList& loops = viewport_.loop_points();
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
  {
    Lock l(lock());
    followCursor_ = settings.follow_cursor();
  }

  bool show = settings.show_master_tune();
  components()->transformController_->showMasterTune(show);
}

void CurrentTime::setCursorTime(Samples<44100> t, int index, bool isTimeCursor) {
  if (isTimeCursor) {
    jumpToTime(t);
  } else {
    Viewport viewport(data::getProto<Viewport>(file()));
    viewport.mutable_loop_points()->mutable_loop_point(index)->set_time(t);
    data::setProto(viewport, file());
  }
}

void CurrentTime::jumpToTime(Samples<44100> time) {
  {
    Lock l(lock());
    if (isPlaying() &&
        !(timeSelection_.empty() || block::contains(timeSelection_, time))) {
      return;
    }

    BufferedReader* reader = bufferFiller()->reader();
    requestedTime_ = time;
    DCHECK(reader);  // TODO: remove
    if (reader && !reader->coversTime(time)) {
      reader->setNextFillPosition(time);
      if (player()->state())
        return;
    }
    requestedTime_ = -1;
  }

	player()->setNextReadPosition(time);
}

}  // namespace slow
}  // namespace rec

