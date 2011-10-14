#include <math.h>

#include "rec/slow/MouseListener.h"
#include "rec/audio/Audio.h"
#include "rec/slow/Components.h"
#include "rec/slow/Model.h"
#include "rec/slow/LoopCommands.h"
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
    : HasInstance(i), waveformDragStart_(0.0) {
  components()->waveform_.addMouseListener(this, true);
  Broadcaster<const MouseWheelEvent&> *w = &components()->waveform_;
  w->addListener(this);
}

namespace {

static const double WHEEL_RATIO = 1.0;
static const double POWER = 4.0;
static const double SMALL_RATIO = 0.1;
static const double BIG_RATIO = 2.0;
static const double ZOOM_INCREMENT = 0.3;

double zoomFunction(double increment) {
  return pow(POWER, -increment);
}

void zoom(Model* model, const MouseEvent& e, RealTime time, double increment) {
  DLOG(INFO) << "here!";
  const juce::ModifierKeys& k = e.mods;
  double s = k.isAltDown() ? SMALL_RATIO : k.isCommandDown() ? BIG_RATIO : 1.0;
  model->zoom(time, zoomFunction(s * increment));
}

}  // namespace

void MouseListener::operator()(const MouseWheelEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.event_->eventComponent == waveform) {
    double time = waveform->xToTime(e.event_->x);
    double inc = (e.xIncrement_ + e.yIncrement_) * WHEEL_RATIO;
    zoom(model(), *e.event_, time, inc);
  }
}


Mode::Action MouseListener::getClickAction(const MouseEvent& e) {
  juce::ModifierKeys k = e.mods;

  bool alt = k.isAltDown();
  bool cmd = k.isCommandDown();
  bool right = k.isPopupMenu();  // Right click or ctrl click.
  bool shift = k.isShiftDown();
  bool none = !(alt || cmd || right || shift);

  Mode::Action modeAction = mode_.click();
  if (none)
    return modeAction;

  if (modeAction == Mode::ZOOM_OUT)
    return shift ? Mode::ZOOM_IN : Mode::ZOOM_OUT;

  if (cmd || modeAction == Mode::ZOOM_IN)
    return shift ? Mode::ZOOM_OUT : Mode::ZOOM_IN;

  return right ? Mode::DRAW_LOOP_POINTS : (shift ? Mode::DRAG : Mode::SET_TIME);
}

void MouseListener::mouseDown(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform) {
    RealTime time = waveform->xToTime(e.x);
    Mode::Action action = getClickAction(e);
    // DLOG(INFO) << "Action: " << Mode::Action_Name(action);
    if (action == Mode::DRAG)
      waveformDragStart_ = DataListener<ZoomProto>::data_->get().begin();

    else if (action == Mode::DRAW_LOOP_POINTS)
      components()->loops_.addLoopPoint(time);

    else if (action == Mode::TOGGLE_SELECTION)
      toggleSelectionSegment(model()->file(), time);

    else if (action == Mode::SET_TIME)
      model()->jumpToTime(time);

    else if (action == Mode::ZOOM_IN)
      zoom(model(), e, time, ZOOM_INCREMENT);

    else if (action == Mode::ZOOM_OUT)
      zoom(model(), e, time, -ZOOM_INCREMENT);

    else
      DCHECK(false);

    waveform->grabKeyboardFocus();
    waveform->repaint();  // TODO: can remove now?
    // TODO: check to make sure they don't change shift during the drag...

  } else if (e.eventComponent->getName() == "Cursor") {
    Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent);
    int i = cursor->index();
    if (i >= 0) {
      LoopPointList loops = data::get<LoopPointList>(model()->file());
      cursorDrag_.begin_ = i ? loops.loop_point(i - 1).time() : 0.0;
      cursorDrag_.end_ = RealTime(loops.loop_point(i + 1).time());
    }
  }
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  if (e.eventComponent == waveform) {
    Mode::Action action = getClickAction(e);
    if (action == Mode::DRAG) {
      RealTime dt = e.getDistanceFromDragStartX() / waveform->pixelsPerSecond();
      ZoomProto zoom(DataListener<ZoomProto>::data_->get());
      RealTime length = player()->length();
      RealTime end = zoom.has_end() ? RealTime(zoom.end()) : length;
      RealTime size = end - zoom.begin();
      RealTime begin = std::max<double>(waveformDragStart_ - dt, 0.0);
      RealTime e2 = std::min(length, begin + size);
      zoom.set_begin(e2 - size);
      zoom.set_end(end);

      zoom.set_end(zoom.begin() + size);
      DataListener<ZoomProto>::data_->set(zoom);
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
  Cursor* timeCursor = components()->waveform_.timeCursor();
  if (timeCursor == e.eventComponent)
    timeCursor->setListeningToClock(true);

  // mouseDrag(e);
}

}  // namespace slow
}  // namespace rec
