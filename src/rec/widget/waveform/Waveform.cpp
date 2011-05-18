#include "rec/widget/waveform/Waveform.h"

#include "rec/gui/Focusable.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/FormatTime.h"
#include "rec/util/STL.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/MouseWheelEvent.h"

using namespace rec::gui::audio;

namespace rec {
namespace widget {
namespace waveform {

namespace {

Def<CursorProto> timeDesc("widget {colors {color: {name: \"pink\"}}}");
Def<CursorProto> defaultDesc("widget {colors {color: {name: \"yellow\"}}}");

}  // namespace

Waveform::Waveform(const WaveformProto& d, const CursorProto* timeCursor)
    : Component("Waveform"),
      desc_(d),
      thumbnail_(NULL) {
  setName("Waveform");  // TODO:  delete?

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

void Waveform::setAudioThumbnail(juce::AudioThumbnail* thumbnail) {
  {
    // ScopedLock l(lock_);
    if (thumbnail_ != thumbnail) {
      thumbnail_ = thumbnail;
      resized();
    }
  }
  thread::runOnMessageThread(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  // ScopedLock l(lock_);

  if (thumbnail_) {
    TimeSelection::iterator i = selection_.begin();
    TimeRange range = getTimeRange();
    TimeRange r = range;
    const juce::Rectangle<int>& bounds = getLocalBounds();
    int channels = thumbnail_->getNumChannels();

    while (r.size() > 0.0) {
      for (; i != selection_.end() && i->end_ <= r.begin_; ++i);
      bool selected = (i != selection_.end() && r.begin_ >= i->begin_);
      Range<double> draw = r;
      if (selected)
        draw.end_ = i->end_;

      else if (i != selection_.end())
        draw.end_ = i->begin_;

      int x1 = timeToX(draw.begin_);
      int x2 = timeToX(draw.end_);

      juce::Rectangle<int> b(x1, bounds.getY(), x2 - x1, bounds.getHeight());

      if (desc_.layout() == WaveformProto::PARALLEL) {
        p.setColor(1 + 2 * selected);
        thumbnail_->drawChannels(g, b, draw.begin_, draw.end_, 1.0f);

      } else {
        for (int i = 0; i < channels; ++i) {
          p.setColor(selected ? i + 1 : i + 1 + channels);
          thumbnail_->drawChannel(g, b, draw.begin_, draw.end_, i, 1.0f);
        }
      }
      r.begin_ = draw.end_;
    }
    drawGrid(g, range);

  } else {
    g.setFont(14.0f);
    g.drawFittedText("Drop a file here or double-click to open a new file",
                     0, 0, getWidth(), getHeight(), juce::Justification::centred, 0);
  }

  gui::paintFocus(g, this);
}

int Waveform::timeToX(double t) const {
  return static_cast<int>((t - getTimeRange().begin_) * pixelsPerSecond());
}

double Waveform::xToTime(int x) const {
  return getTimeRange().begin_ + x / pixelsPerSecond();
}

double Waveform::pixelsPerSecond() const {
  return getWidth() / getTimeRange().size();
}

void Waveform::addAllCursors(const LoopPointList& loopPoints) {
  int size = loopPoints.loop_point_size();
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
    c->setCursorBounds(time);
  }

  while (getNumChildComponents() > size + 1)
    delete removeChildComponent(size + 1);

  setSelection(loopPoints);
}

void Waveform::setSelection(const LoopPointList& loopPoints) {
  selection_.clear();
  for (int i = 0, size = loopPoints.selected_size(); i < size; ) {
    for (; i < size && !loopPoints.selected(i); ++i);
    if (i < size) {
      int j = i;
      for (; j < size && loopPoints.selected(j); ++j);
      double begin = loopPoints.loop_point(i).time();
      double end = (j < size) ? loopPoints.loop_point(j).time() :
        getTimeRange().end_;
      selection_.insert(TimeRange(begin, end));
      i = j;
    }
  }
  Broadcaster<const TimeSelection&>::broadcast(selection_);
  resized();
}

void Waveform::operator()(const LoopPointList& loops) {
  thread::callAsync(this, &Waveform::addAllCursors, loops);
}

void Waveform::operator()(const ZoomProto& zp) {
  ScopedLock l(lock_);
  zoom_ = zp;
  if (!zoom_.has_end())  // TODO:  get length properly.
    zoom_.set_end(thumbnail_ ? thumbnail_->getTotalLength() : 0);

  resized();
}

void Waveform::layoutCursors() {
  for (int i = getNumChildComponents(); i > 0; --i) {
    Component* comp = getChildComponent(i - 1);
    if (comp->getName() == "Cursor") {
      Cursor* c = dynamic_cast<Cursor*>(comp);
      c->setCursorBounds(c->getTime());
    }
  }
  repaint();
}

void Waveform::resized() {
  thread::runOnMessageThread(this, &Waveform::layoutCursors);
}

TimeRange Waveform::getTimeRange() const {
  // ScopedLock l(lock_);
  TimeRange r;
  if (zoom_.zoom_to_selection() && !selection_.empty()) {
    r.begin_ = selection_.begin()->begin_;
    r.end_ = selection_.rbegin()->end_;
    if (r.end_ == 0.0)
      r.end_ = zoom_.end();

    r.begin_ -= desc_.selection_frame_in_seconds();
    r.end_ += desc_.selection_frame_in_seconds();

    r.begin_ = juce::jmax(r.begin_, 0.0);
    r.end_ = juce::jmin(r.end_, zoom_.end());
  } else {
    r.begin_ = zoom_.begin();
    r.end_= zoom_.end();
  }

  if (r.size() < SMALLEST_TIME)
    r = TimeRange(0, thumbnail_ ? thumbnail_->getTotalLength() : SMALLEST_TIME);

  return r;
}

void Waveform::mouseWheelMove(const MouseEvent& e, float xIncrement, float yIncrement) {
  MouseWheelEvent we;
  we.event_ = &e;
  we.xIncrement_ = xIncrement;
  we.yIncrement_ = yIncrement;
  Broadcaster<const MouseWheelEvent&>::broadcast(we);
}

void Waveform::drawGrid(Graphics& g, const TimeRange& r) {
  RealTime width = r.size();
  if (width < SMALLEST_TIME)
    return;
  RealTime units = pow(10.0, floor(log10(width)));

  int b = ceil(r.begin_ / units), e = r.end_ / units, diff = e - b;

  if (diff <= 2)
    units /= 2.0;
  else if (diff > 15)
    units *= 5.0;

  if (units > 10.0)
    units *= 1.2;

  b = ceil(r.begin_ / units);
  e = floor(r.end_ / units);
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
