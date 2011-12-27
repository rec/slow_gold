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
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"
#include "rec/widget/waveform/OutlinedCursorLabel.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

static const Samples<44100> DRAG_PAD = audio::CLOSE_LOOPS;
static const int DRAG_TWEAK = 5;

using namespace rec::audio;
using namespace rec::gui::audio;
using namespace rec::widget::waveform;
using namespace rec::util::block;

MouseListener::MouseListener(Instance* i)
    : HasInstance(i), waveformDragStart_(0) {
  components()->waveform_->addMouseListener(this, true);
  Broadcaster<const MouseWheelEvent&> *w = components()->waveform_.get();
  w->addListener(this);
}

namespace {

typedef widget::waveform::OutlinedCursorLabel Label;

void toggleSelectionSegment(const VirtualFile& file, Samples<44100> time) {
  data::Opener<LoopPointList> opener(data::getData<LoopPointList>(&file));
  audio::toggleSelectionSegment(opener.mutable_get(), time);
}

static const double WHEEL_RATIO = 4.0;
static const double SMALL_RATIO = 0.1;
static const double BIG_RATIO = 2.0;

void zoom(const Instance& instance, const MouseEvent& e,
          Samples<44100> time, double increment) {
  const juce::ModifierKeys& k = e.mods;
  double s = k.isAltDown() ? SMALL_RATIO : k.isCommandDown() ? BIG_RATIO : 1.0;
  widget::waveform::zoom(instance.file(), instance.length(), time, s * increment);
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
    Samples<44100> time = waveform->xToTime(e.event_->x);
    double inc = (e.xIncrement_ + e.yIncrement_) * WHEEL_RATIO;
    zoom(*instance_, *e.event_, time, inc);
  }
}

void MouseListener::addLoopPoint(Samples<44100> time) {
  audio::addLoopPointToData(file(), time);
  toggleAddLoopPointMode();
}

void MouseListener::clickWaveform(const MouseEvent& e, Waveform* waveform) {
  Samples<44100> time = waveform->xToTime(e.x);
  dragMods_ = e.mods;
  Mode::Action action = getClickAction();
  if (action == Mode::DRAG)
    waveformDragStart_ = DataListener<ZoomProto>::getProto().begin();

  else if (action == Mode::DRAW_LOOP_POINTS)
    addLoopPoint(time);

  else if (action == Mode::TOGGLE_SELECTION)
    toggleSelectionSegment(file(), time);

  else if (action == Mode::SET_TIME)
    currentTime()->jumpToTime(time);

  else if (action == Mode::ZOOM_IN)
    zoom(*instance_, e, time, 1);

  else if (action == Mode::ZOOM_OUT)
    zoom(*instance_, e, time, -1);

  else
    DCHECK(false);

  waveform->grabKeyboardFocus();
  // TODO: check to make sure they don't change shift during the drag...
}

void MouseListener::mouseDown(const MouseEvent& e) {
  Waveform* waveform = components()->waveform_.get();
  if (e.eventComponent == waveform)
    clickWaveform(e, waveform);

  else if (Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent))
    clickCursor(cursor);

  else if (Label* label = dynamic_cast<Label*>(e.eventComponent))
    clickCursor(label->getCursor());
}

void MouseListener::clickCursor(widget::waveform::Cursor* cursor) {
  if (cursor->isTimeCursor()) {
    cursorRestrict_.begin_ = 0;
    cursorRestrict_.end_ = length();
  } else {
    int i = cursor->index();
    cursorDragStart_ = cursor->getX();
    LoopPointList loops = data::getProto<LoopPointList>(file());
    cursorRestrict_.begin_ = (i ? loops.loop_point(i - 1).time() : 0) + DRAG_PAD;
    cursorRestrict_.end_ = -DRAG_PAD + ((i == loops.loop_point_size() - 1) ?
                                        loops.length() : loops.loop_point(i + 1).time());
  }
}

void MouseListener::dragCursor(const MouseEvent& e,
                               widget::waveform::Cursor* cursor) {
  Waveform* waveform = cursor->waveform();
  components()->waveform_->setIsDraggingCursor(true);
  if (!near(cursor->getTime(), 0, 44)) {
    int cursorX = e.getDistanceFromDragStartX() + cursorDragStart_ + DRAG_TWEAK;
    Samples<44100> t = cursorRestrict_.restrict(waveform->xToTime(cursorX));
    if (cursor->setDragTime(t))
      currentTime()->setCursorTime(t, cursor->index(), cursor->isTimeCursor());
  }
}

void MouseListener::dragWaveform(const MouseEvent& e, Waveform* waveform) {
  Mode::Action action = getClickAction();
  if (action == Mode::DRAG) {
    Samples<44100> dt = static_cast<int64>(e.getDistanceFromDragStartX() /
                                           waveform->pixelsPerSample());
    widget::waveform::ZoomProto zoom(DataListener<ZoomProto>::getProto());
    Samples<44100> len = length();
    Samples<44100> end = zoom.has_end() ? Samples<44100>(zoom.end()) : len;
    Samples<44100> size = end - zoom.begin();
    Samples<44100> begin = std::max(waveformDragStart_ - dt, Samples<44100>(0));
    Samples<44100> e2 = std::min(len, begin + size);
    zoom.set_begin(e2 - size);
    zoom.set_end(end);

    zoom.set_end(zoom.begin() + size);
    DataListener<widget::waveform::ZoomProto>::setProto(zoom);
  }
}

void MouseListener::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = components()->waveform_.get();
  if (e.eventComponent == waveform)
    dragWaveform(e, waveform);

  else if (Cursor* cursor = dynamic_cast<Cursor*>(e.eventComponent))
    dragCursor(e, cursor);

  else if (Label* label = dynamic_cast<Label*>(e.eventComponent))
    dragCursor(e, label->getCursor());
}

void MouseListener::mouseUp(const MouseEvent& e) {
  components()->waveform_->setIsDraggingCursor(false);
}

void MouseListener::toggleAddLoopPointMode() {
#ifdef DRAW_LOOP_POINTS_IS_ONE_CLICK
  if (mode_.click() == Mode::DRAW_LOOP_POINTS) {
    mode_ = previousMode_;
  } else {
    previousMode_ = mode_;
    mode_.set_click(Mode::DRAW_LOOP_POINTS);
  }
  GlobalDataListener<Mode>::setProto(mode_);
#endif
}

}  // namespace slow
}  // namespace rec
