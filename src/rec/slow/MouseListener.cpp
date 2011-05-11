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
  RealTime time = waveform->xToTime(e.x);
  if (e.eventComponent == waveform) {
    if (e.mods.isShiftDown()) {
      waveformDragStart_ = model()->zoomLocker()->get().begin();
      DLOG(INFO) << "waveformDragStart_=" << waveformDragStart_;
    } else
      model()->setTriggerTime(timeToSamples(time));
    // TODO: check to make sure they don't change shift during the drag...
  }
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  RealTime time = waveform->xToTime(e.x);
  if (e.eventComponent == waveform) {
    if (e.mods.isShiftDown()) {
      RealTime dt = e.getDistanceFromDragStartX() / waveform->pixelsPerSecond();
      ZoomProto zoom(model()->zoomLocker()->get());
      RealTime end = zoom.has_end() ? zoom.end() : model()->realLength();
      RealTime size = end - zoom.begin();
      zoom.set_begin(waveformDragStart_ - dt);
      zoom.set_end(zoom.begin() + size);
      model()->zoomLocker()->set(zoom);
    } else {
      model()->setTriggerTime(timeToSamples(time));
    }
  } else if (e.eventComponent == waveform->timeCursor()) {
    model()->setTriggerTime(timeToSamples(waveform->xToTime(e.x)));
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
  mouseDrag(e);
}

void MouseListener::mouseDoubleClick(const MouseEvent& e) {
  if (!target()->invokeDirectly(command::Command::OPEN))
    LOG(ERROR) << "Unable to start open dialog";
  else
    DLOG(INFO) << "Opened a new file!";
}

#ifdef TODO

void PlaybackController::operator()(const Stretch& desc) {
  thread::callAsync(&stretchyController_,
                    &gui::StretchyController::enableSliders,
                    !desc.stretch().disabled());
  timeController_(desc);
}

int Cursor::getDragX(const MouseEvent& e) const {
  return getX() + e.x - mouseDragX_;
}

void Cursor::mouseDown(const MouseEvent& e) {
  dragging_ = true;
  mouseDragX_ = e.x;
  dragX_ = getX();
}

void Cursor::mouseDrag(const MouseEvent& e) {
  if (dragging_)
    setTopLeftPosition(getDragX(e), getY());
}

void Cursor::mouseUp(const MouseEvent& e) {
  if (dragging_) {
    dragging_ = false;
    int location = getDragX(e) + desc().component_width() / 2;
    waveform_->cursorDragged(index_, location);
  }
}

void Waveform::cursorDragged(int index, int x) {
  CursorTime ct;
  ct.cursor_ = index;
  ct.time_ = xToTime(x);
  Broadcaster<const CursorTime&>::broadcast(ct);
}


#endif
}  // namespace slow
}  // namespace rec
