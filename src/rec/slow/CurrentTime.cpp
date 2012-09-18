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
#include "rec/util/range/Contains.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using audio::util::BufferedReader;
using widget::waveform::Zoom;
using namespace rec::widget::waveform;

static const double IDEAL_CURSOR_POSITION_RATIO = 0.05;
static const double MIN_CURSOR_RATIO_CHANGE = 0.80;

static const int PRELOAD = 10000;  // TODO:  duplicate code.
static const int NO_SEGMENT = -1;

CurrentTime::CurrentTime(Instance* i)
    : HasInstance(i),
      time_(0),
      requestedTime_(-1),
      length_(0),
      followCursor_(false),
      loopingSegment_(NO_SEGMENT) {
}

void CurrentTime::setTime(SampleTime t) {
  {
    Lock l(lock());
    time_ = t;

    if (loopingSegment_ > NO_SEGMENT) {
      uint current = audio::getSegment(viewport_.loop_points(), time());
      if (static_cast<int>(current) == loopingSegment_) {
        LoopPointList* lpl = viewport_.mutable_loop_points();
        uint size = lpl->loop_point_size();
        for (uint i = 0; i < size; ++i)
          lpl->mutable_loop_point(i)->set_selected(i == current);
        setViewportProto(viewport_);
        loopingSegment_ = NO_SEGMENT;
      }
    }

    if (!(followCursor_  && isPlaying()))
      return;
  }
  zoomToTime(t);
}

void CurrentTime::setViewportProto(const Viewport& viewport) {
  DataListener<Viewport>::setProto(viewport, CANT_UNDO);
}

void CurrentTime::zoomToTime(SampleTime t) {
  Viewport viewport;
  {
    Lock l(lock());
    viewport = viewport_;
  }

  Zoom* zoom = viewport.mutable_zoom();
  SampleTime begin = zoom->begin();
  SampleTime end = zoom->has_end() ? SampleTime(zoom->end()) : length_;

  // Now compute an ideal zoom for this time.
  SampleTime width = end - begin;
  SampleTime off = static_cast<int64>(MIN_CURSOR_RATIO_CHANGE * width);
  if (t >= zoom->begin() && (t <= zoom->begin() + off))
    return;

  zoom->set_begin(t - static_cast<int64>(IDEAL_CURSOR_POSITION_RATIO * width));

  if (zoom->begin() + width > length_)
    zoom->set_begin(length_ - width);

  if (zoom->begin() < 0)
    zoom->set_begin(0);

  zoom->set_end(zoom->begin() + width);
  setViewportProto(viewport);
}

void CurrentTime::setViewport(const Viewport& viewport) {
  SampleTime time = 0;
  bool jump = true;

  {
    Lock l(lock());
    viewport_ = viewport;
    const LoopPointList& loops = viewport_.loop_points();
    length_ = loops.length();
    if (loops.has_length()) {
      timeSelection_ = audio::getTimeSelection(loops);
      if (!timeSelection_.empty()) {
        SampleRangeVector::const_iterator i = timeSelection_.begin();
        for (; i != timeSelection_.end(); ++i) {
          if (time_ < i->end_) {
            if (time_ < i->begin_)
              time = i->begin_;
            else
              jump = false;
            break;
          }
        }
        time = timeSelection_.begin()->begin_;
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

void CurrentTime::setCursorTime(SampleTime t, int index, bool isTimeCursor) {
  if (isTimeCursor) {
    jumpToTime(t);
  } else {
    Viewport viewport(DataListener<Viewport>::getDataValue());
    viewport.mutable_loop_points()->mutable_loop_point(index)->set_time(t);
    setViewportProto(viewport);
  }
}

void CurrentTime::reset() {
  {
    Lock l(lock());
    requestedTime_ = 0;
  }

  setTime(0);
}

void CurrentTime::jumpToTime(SampleTime time) {
  {
    Lock l(lock());
    if (empty() || !(timeSelection_.empty() || contains(timeSelection_, time)))
      return;

    BufferedReader* reader = bufferFiller()->reader();
    requestedTime_ = time;
    time_ = time;
    DCHECK(reader);  // TODO: remove
    if (reader && !reader->coversTime(time)) {
      reader->setNextFillPosition(time);
      if (player()->state()) {
        zoomToTime(time);
        return;
      }
    }
    requestedTime_ = -1;
  }

	player()->setNextReadPosition(time);
  zoomToTime(time);
}

void CurrentTime::setLoopingSegment(int segment) {
  Lock l(lock());
  loopingSegment_ = segment;
}

}  // namespace slow
}  // namespace rec

