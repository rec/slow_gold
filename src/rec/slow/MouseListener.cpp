#include <math.h>

#include "rec/slow/MouseListener.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/data/Data.h"
#include "rec/gui/audio/Loops.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Target.h"
#include "rec/util/Math.h"
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
  components()->waveform_->addMouseListener(this, true);
  Broadcaster<const MouseWheelEvent&> *w = components()->waveform_.get();
  w->addListener(this);
}

namespace {

void toggleSelectionSegment(const VirtualFile& file, RealTime time) {
  data::apply(file, &audio::toggleSelectionSegment, time);
}

static const double WHEEL_RATIO = 1.0;
static const double POWER = 4.0;
static const double SMALL_RATIO = 0.1;
static const double BIG_RATIO = 2.0;
static const double ZOOM_INCREMENT = 0.3;

double zoomFunction(double increment) {
  return pow(POWER, -increment);
}

void zoom(const Instance& instance, const MouseEvent& e,
          RealTime time, double increment) {
  const juce::ModifierKeys& k = e.mods;
  double s = k.isAltDown() ? SMALL_RATIO : k.isCommandDown() ? BIG_RATIO : 1.0;
  double z = zoomFunction(s * increment);
  widget::waveform::zoom(instance.file(), instance.length(), time, z);
}

}  // namespace

Mode::Action MouseListener::getClickAction() {
  bool alt = dragMods_.isAltDown();
  bool cmd = dragMods_.isCommandDown();
  bool right = dragMods_.isPopupMenu();  // Right click or ctrl click.
  bool shift = dragMods_.isShiftDown();
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

void MouseListener::operator()(const MouseWheelEvent& e) {
  Waveform* waveform = components()->waveform_.get();
  if (e.event_->eventComponent == waveform) {
    double time = waveform->xToTime(e.event_->x);
    double inc = (e.xIncrement_ + e.yIncrement_) * WHEEL_RATIO;
    zoom(*instance_, *e.event_, time, inc);
  }
}

void MouseListener::mouseDown(const MouseEvent& e) {
  Waveform* waveform = components()->waveform_.get();
  if (e.eventComponent == waveform) {
    RealTime time = waveform->xToTime(e.x);
    dragMods_ = e.mods;
    Mode::Action action = getClickAction();
    if (action == Mode::DRAG)
      waveformDragStart_ = DataListener<ZoomProto>::data()->get().begin();

    else if (action == Mode::DRAW_LOOP_POINTS)
      audio::addLoopPointToEditable(file(), time);

    else if (action == Mode::TOGGLE_SELECTION)
      toggleSelectionSegment(file(), time);

    else if (action == Mode::SET_TIME)
      currentTime()->jumpToTime(time);

    else if (action == Mode::ZOOM_IN)
      zoom(*instance_, e, time, ZOOM_INCREMENT);

    else if (action == Mode::ZOOM_OUT)
      zoom(*instance_, e, time, -ZOOM_INCREMENT);

    else
      DCHECK(false);

    waveform->grabKeyboardFocus();
    waveform->repaint();  // TODO: can remove now?
    // TODO: check to make sure they don't change shift during the drag...

  } else if (e.eventComponent->getName() == "Cursor") {
    Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent);
    int i = cursor->index();
    if (i >= 0) {
      LoopPointList loops = data::get<LoopPointList>(file());
      cursorDrag_.begin_ = i ? loops.loop_point(i - 1).time() : 0.0;
      cursorDrag_.end_ = (i == loops.loop_point_size()) ?
        RealTime(loops.loop_point(i + 1).time()) : RealTime(loops.length());
    }
  }
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = components()->waveform_.get();
  if (e.eventComponent == waveform) {
    Mode::Action action = getClickAction();
    if (action == Mode::DRAG) {
      RealTime dt = e.getDistanceFromDragStartX() / waveform->pixelsPerSecond();
      widget::waveform::ZoomProto zoom(DataListener<ZoomProto>::data()->get());
      RealTime len = length();
      RealTime end = zoom.has_end() ? RealTime(zoom.end()) : len;
      RealTime size = end - zoom.begin();
      RealTime begin = std::max<double>(waveformDragStart_ - dt, 0.0);
      RealTime e2 = std::min(len, begin + size);
      zoom.set_begin(e2 - size);
      zoom.set_end(end);

      zoom.set_end(zoom.begin() + size);
      DataListener<widget::waveform::ZoomProto>::data()->setValue(zoom);
    }

  } else if (e.eventComponent->getName() == "Cursor") {
    Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent);
    if (!near(cursor->getTime(), 0.0, 0.001)) {
      RealTime t = cursorDrag_.restrict(waveform->xToTime(e.x + cursor->getX()));
      cursor->setListeningToClock(false);
      cursor->setTime(t);
      currentTime()->setCursorTime(cursor->index(), t);
    }
  }
}

void MouseListener::mouseUp(const MouseEvent& e) {
  Cursor* timeCursor = components()->waveform_->timeCursor();
  if (timeCursor == e.eventComponent)
    timeCursor->setListeningToClock(true);

  // mouseDrag(e);
}

}  // namespace slow
}  // namespace rec
