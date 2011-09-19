#include "rec/widget/waveform/Waveform.h"

#include "rec/util/Defaulter.h"
#include "rec/util/Range.h"
#include "rec/util/Math.h"
#include "rec/util/FormatTime.h"
#include "rec/util/STL.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

Def<CursorProto> timeDesc(
"widget {colors {color: {name: \"pink\"}}}\n"
"line {thickness: 2.0}"
);

Def<CursorProto> defaultDesc(
"widget {colors {color: {name: \"yellow\"}}}\n"
"line {thickness: 2.0}"
);

}  // namespace

Waveform::Waveform(const WaveformProto& d, const CursorProto* timeCursor)
    : desc_(d),
      thumbnail_(NULL),
      empty_(true) {
  setName("Waveform");

  timeCursor_ = newCursor(*timeCursor, 0.0f, -1);
  desc_.set_selection_frame_in_seconds(0);  // TODO: what's this?

  setWantsKeyboardFocus(true);
}

Cursor* Waveform::newCursor(const CursorProto& d, double time, int index) {
	Cursor* cursor = new Cursor(d, this, time, index);
  addAndMakeVisible(cursor);
  return cursor;
}

Waveform::~Waveform() {
  for (int i = getNumChildComponents() - 1; i >= 0; --i)
    delete getChildComponent(i);
}

const CursorProto& Waveform::defaultTimeCursor() {
  return timeDesc.get();
}

void Waveform::setEmpty(bool empty) {
  ScopedLock l(lock_);
  empty_ = empty;
}

void Waveform::paint(Graphics& g) {
  {
    Painter p(desc_.widget(), &g);
    ScopedLock l(lock_);

    if (empty_) {
      g.setFont(14.0f);
      g.drawFittedText("Drop a file here or double-click to open a new file",
                       0, 0, getWidth(), getHeight(), juce::Justification::centred, 0);
    } else {
      SampleSelection::iterator i = selection_.begin();
      Range<RealTime> range = getTimeRange();
      block::Block r;
      r.first = SamplePosition(range.begin_);
      r.second = SamplePosition(range.end_);
      const juce::Rectangle<int>& bounds = getLocalBounds();
      int channels = thumbnail_->getNumChannels();

      while (block::getSize(r) > 0) {
        for (; i != selection_.end() && i->second <= r.first; ++i);
        bool selected = (i != selection_.end() && r.first >= i->first);
        block::Block draw = r;
        if (selected)
          draw.second = i->second;

        else if (i != selection_.end())
          draw.second = i->first;

        int x1 = timeToX(draw.first);
        int x2 = timeToX(draw.second);

        juce::Rectangle<int> b(x1, bounds.getY(), x2 - x1, bounds.getHeight());

        RealTime first = draw.first, second = draw.second;
        if (desc_.layout() == WaveformProto::PARALLEL) {
          p.setColor(1 + 2 * selected);
          thumbnail_->drawChannels(g, b, first, second, 1.0f);
        } else {
          for (int i = 0; i < channels; ++i) {
            p.setColor(selected ? i + 1 : i + 1 + channels);
            thumbnail_->drawChannel(g, b, first, second, i, 1.0f);
          }
        }
        r.first = draw.second;
      }
      drawGrid(g, range);
    }
  }
  paintFocus(g);
}

int Waveform::timeToX(RealTime t) const {
  return static_cast<int>((t - getTimeRange().begin_) * pixelsPerSecond());
}

double Waveform::xToTime(int x) const {
  return getTimeRange().begin_ + x / pixelsPerSecond();
}

double Waveform::pixelsPerSecond() const {
  return getWidth() / getTimeRange().size();
}

void Waveform::onDataChange(const LoopPointList& loopPoints) {
  SampleSelection selection = audio::getTimeSelection(loopPoints);
  {
    ScopedLock l(lock_);
    selection_ = selection;
  }

  resized();
  thread::callAsync(this, &Waveform::adjustCursors, loopPoints);
}

void Waveform::adjustCursors(const LoopPointList& loopPoints) {
  MessageManagerLock l;
  int size = loopPoints.loop_point_size() - 1;
  for (int i = 0; i < size; ++i) {
    double time = loopPoints.loop_point(i).time();
    bool needsNew = (i >= getNumChildComponents() - 1);
    Cursor* c;
    if (needsNew) {
      c = newCursor(CursorProto::default_instance(), time, i);
    } else {
      Component* comp = getChildComponent(i + 1);
      c = dynamic_cast<Cursor*>(comp);
    }
    c->setCursorBounds(time, getLocalBounds());
  }

  while (getNumChildComponents() > size + 1)
    delete removeChildComponent(size + 1);
}

void Waveform::onDataChange(const ZoomProto& zp) {
  {
    ScopedLock l(lock_);
    zoom_ = zp;
    if (!zoom_.has_end())  // TODO:  get length properly.
      zoom_.set_end(thumbnail_ ? thumbnail_->getTotalLength() : 0);
  }

  resized();
}

const juce::MouseCursor::StandardCursorType getCursor(const Mode& mode) {
  using juce::MouseCursor;
  switch (mode.click()) {
    case Mode::DRAG:              return MouseCursor::DraggingHandCursor;
    case Mode::DRAW_LOOP_POINTS:  return MouseCursor::IBeamCursor;
    case Mode::SET_TIME:          return MouseCursor::CrosshairCursor;
    case Mode::TOGGLE_SELECTION:  return MouseCursor::PointingHandCursor;
    case Mode::ZOOM_IN:
    case Mode::ZOOM_OUT:          return MouseCursor::UpDownLeftRightResizeCursor;
    default:                      return MouseCursor::NormalCursor;
  }
}

void Waveform::onDataChange(const Mode& mode) {
  ScopedLock l(lock_);
  setMouseCursor(getCursor(mode));
}

void Waveform::layoutCursors() {
  {
    ScopedLock l(lock_);
    for (int i = getNumChildComponents(); i > 0; --i) {
      Component* comp = getChildComponent(i - 1);
      if (comp->getName() == "Cursor") {
        Cursor* c = dynamic_cast<Cursor*>(comp);
        c->setCursorBounds(c->getTime(), getLocalBounds());
      }
    }
  }
  repaint();
}

void Waveform::resized() {
  MessageManagerLock l;
  repaint();
  layoutCursors();
}

Range<RealTime> Waveform::getTimeRange() const {
  ScopedLock l(lock_);
  Range<RealTime> r;
  if (zoom_.zoom_to_selection() && !selection_.empty()) {
    r.begin_ = selection_.begin()->first;
    r.end_ = selection_.rbegin()->second;
    if (r.end_ == 0.0)
      r.end_ = zoom_.end();

    r.begin_ -= desc_.selection_frame_in_seconds();
    r.end_ += desc_.selection_frame_in_seconds();

    r.begin_ = std::max<RealTime>(r.begin_, 0.0);
    r.end_ = std::min<RealTime>(r.end_, zoom_.end());
  } else {
    r.begin_ = zoom_.begin();
    r.end_= zoom_.end();
  }

  if (r.size() < SMALLEST_TIME)
    r = Range<RealTime>(0, thumbnail_ ? thumbnail_->getTotalLength() : SMALLEST_TIME);

  return r;
}

void Waveform::mouseWheelMove(const MouseEvent& e, float xIncrement, float yIncrement) {
  MouseWheelEvent we;
  we.event_ = &e;
  we.xIncrement_ = xIncrement;
  we.yIncrement_ = yIncrement;
  Broadcaster<const MouseWheelEvent&>::broadcast(we);
}

void Waveform::drawGrid(Graphics& g, const Range<RealTime>& r) {
  RealTime width = r.size();
  if (width < SMALLEST_TIME)
    return;
  RealTime units = pow(10.0, floor(log10(width)));

  int b = static_cast<int>(ceil(r.begin_ / units));
  int e = static_cast<int>(r.end_ / units);
  int diff = e - b;

  if (diff <= 2)
    units /= 2.0;
  else if (diff > 15)
    units *= 5.0;

  if (units > 10.0)
    units *= 1.2;

  b = static_cast<int>(ceil(r.begin_ / units));
  e = static_cast<int>(floor(r.end_ / units));
  int h = getHeight();
  int decimals = 0;
  if (units < 0.01)
    decimals = 3;
  else if (units < 0.1)
    decimals = 2;
  else if (units < 1)
    decimals = 1;

  g.setFont(10);

  for (int i = b - 1; i <= e + 1; ++i) {
    RealTime time = i * units;
    int x = timeToX(time);
    g.setColour(juce::Colours::lightgreen.withAlpha(0.8f));
    g.drawVerticalLine(x, 0, h);
    String s = formatTime(time, false, false, false, decimals);
    static const int WIDTH = 50;
    static const int HEIGHT = 10;
    static const int PAD = 4;
    g.setColour(juce::Colours::black);
    g.drawText(s, i ? x - WIDTH / 2 : x - WIDTH / 4, h - PAD - HEIGHT, WIDTH, HEIGHT,
               Justification::centred, true);
  }
}


}  // namespace waveform
}  // namespace widget
}  // namespace rec
