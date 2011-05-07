#include "rec/slow/MouseListener.h"
#include "rec/audio/Audio.h"
#include "rec/slow/Components.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace slow {

using namespace rec::audio;
using namespace rec::widget::waveform;
using namespace rec::util::block;

MouseListener::MouseListener(Instance* i) : HasInstance(i) {
  components()->waveform_.addMouseListener(this, true);
  listenTo(&components()->waveform_);
}

void MouseListener::mouseDown(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform)
    model()->setNextPosition(timeToSamples(waveform->xToTime(e.x)));
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  mouseDown(e);

  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform->timeCursor())
    model()->setNextPosition(timeToSamples(waveform->xToTime(e.x)));
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

void MouseListener::operator()(const MouseWheelEvent& e) {
  DLOG(INFO) << "Here: " << e.xIncrement_ << ", " << e.yIncrement_;
}

#ifdef TODO

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
