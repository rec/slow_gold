#include <math.h>

#include "rec/slow/MouseListener.h"
#include "rec/audio/Audio.h"
#include "rec/slow/Components.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::audio;
using namespace rec::gui::audio;
using namespace rec::widget::waveform;
using namespace rec::util::block;

MouseListener::MouseListener(Instance* i)
    : HasInstance(i), waveformDragStart_(0) {
  components()->waveform_.addMouseListener(this, true);
  listenTo(&components()->waveform_);
}

static double const MAX_WHEEL = 0.50;
static double const RATIO = 4.0;

static double zoomFunction(double increment) {
  return pow(RATIO, -increment / MAX_WHEEL);
}

void MouseListener::operator()(const MouseWheelEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.event_->eventComponent == waveform) {
    const juce::ModifierKeys& k = e.event_->mods;
    double scale = k.isAltDown() ? 0.1 : k.isCommandDown() ? 2.0 : 1;
    model()->zoom(waveform->xToTime(e.event_->x),
                  zoomFunction(scale * e.yIncrement_));
  }
}

void MouseListener::mouseDown(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform) {
    RealTime time = waveform->xToTime(e.x);
    if (e.mods.isShiftDown())
      waveformDragStart_ = model()->zoomLocker()->get().begin();

    else if (e.mods.isAltDown())
      components()->loops_.addLoopPoint(time);

    else if (e.mods.isCommandDown())
      model()->toggleSelectionSegment(time);

    else
      model()->jumpToTime(time);

    waveform->grabKeyboardFocus();
    waveform->repaint();  // TODO: can remove now?
    // TODO: check to make sure they don't change shift during the drag...

  } else if (e.eventComponent->getName() == "Cursor") {
    Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent);
    int i = cursor->index();
    if (i >= 0) {
      LoopPointList loops = model()->loopPointList();
      cursorDrag_.begin_ = i ? loops.loop_point(i - 1).time() : 0.0;
      cursorDrag_.end_ = (i < loops.loop_point_size() - 1) ?
        RealTime(loops.loop_point(i + 1).time()) : player()->realLength();
    }
  }
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform) {
    RealTime time = waveform->xToTime(e.x);
    if (e.mods.isShiftDown()) {
      RealTime dt = e.getDistanceFromDragStartX() / waveform->pixelsPerSecond();
      ZoomProto zoom(model()->zoomLocker()->get());
      RealTime length = player()->realLength();
      RealTime end = zoom.has_end() ? RealTime(zoom.end()) : length;
      RealTime size = end - zoom.begin();
      RealTime begin = std::max<double>(waveformDragStart_ - dt, 0.0);
      RealTime e2 = std::min(length, begin + size);
      zoom.set_begin(e2 - size);
      zoom.set_end(end);

      zoom.set_end(zoom.begin() + size);
      model()->zoomLocker()->set(zoom);
    } else {
      model()->jumpToSamplePosition(timeToSamples(time));
    }

  } else if (e.eventComponent->getName() == "Cursor") {
    Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent);
    RealTime t = cursorDrag_.restrict(waveform->xToTime(e.x + cursor->getX()));
    cursor->setListeningToClock(false);
    cursor->setTime(t);
    model()->setCursorTime(cursor->index(), t);
  }
}

void MouseListener::mouseUp(const MouseEvent& e) {
#ifdef TODO
  if (e.mods.isShiftDown())
    zoomOut();

  else if (zoomProto() && zoomProto()->get().click_to_zoom())
    zoomIn(timeMouse);

  else if (timeMouse.mouseEvent_->mods.isCommandDown())
    zoomIn(timeMouse);

  else
#endif
  Cursor* timeCursor = components()->waveform_.timeCursor();
  if (timeCursor == e.eventComponent)
    timeCursor->setListeningToClock(true);
  // mouseDrag(e);
}

void MouseListener::mouseDoubleClick(const MouseEvent& e) {
  if (!target()->invokeDirectly(command::Command::OPEN))
    LOG(ERROR) << "Unable to start open dialog";

#if 0
  else
    DLOG(INFO) << "Opened a new file!";
#endif

}

#ifdef TODO

void PlaybackController::operator()(const Stretch& desc) {
  thread::callAsync(&stretchyController_,
                    &gui::StretchyController::enableSliders,
                    !desc.stretch().disabled());
  timeController_(desc);
}

#endif
}  // namespace slow
}  // namespace rec
