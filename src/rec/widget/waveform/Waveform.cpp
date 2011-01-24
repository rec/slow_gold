#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace widget {
namespace waveform {

Waveform::Waveform(const WaveformProto& d, const CursorProto* cursor)
    : desc_(d), thumbnail_(NULL), range_(0, 0) {
  setName("Waveform");

  if (cursor)
    timeCursor_ = addCursor(*cursor, 0.0f);
}

Waveform::~Waveform() {
  ScopedLock l(lock_);
  for (int i = getNumChildComponents(); i > 0; --i)
    delete getChildComponent(i - 1);
}

static const Defaulter<CursorProto> timeDesc(
    "widget {colors {color: {name: \"pink\"}}}");

static const Defaulter<CursorProto> defaultDesc(
    "widget {colors {color: {name: \"yellow\"}}}");


const CursorProto& Waveform::defaultTimeCursor() {
  return timeDesc.get();
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* thumbnail) {
  ScopedLock l(lock_);
  thumbnail_ = thumbnail;
  setTimeRange(TimeRange(0, thumbnail_ ? thumbnail_->getTotalLength() : 0));
  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  ScopedLock l(lock_);

  if (thumbnail_) {
    SelectionRange::iterator i = selection_.begin();
    Range<double> r = range_;
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
          p.setColor(selected ? channels - i : i + 1);
          thumbnail_->drawChannel(g, b, draw.begin_, draw.end_, i, 1.0f);
        }
      }
      r.begin_ = draw.end_;
    }

  } else {
    g.setFont(14.0f);
    g.drawFittedText("Drop a file here or double-click to open a new file",
                     0, 0, getWidth(), getHeight(), juce::Justification::centred, 0);
  }
}

Cursor* Waveform::addCursor(const CursorProto& desc, double time, int zorder) {
  ScopedLock l(lock_);
  Cursor* cursor = new Cursor(desc, this, time);
  addAndMakeVisible(cursor, zorder);
  layoutCursor(cursor);
  return cursor;
}

void Waveform::setTimeRange(const TimeRange& bounds) {
  {
    ScopedLock l(lock_);
    range_ = bounds;
  }
  resized();

  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::operator()(const juce::AudioThumbnail&) {
  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::addAllCursors(const gui::LoopPointList& loopPoints) {
  ScopedLock l(lock_);
  for (int i = 0, c = 1; i < loopPoints.loop_point_size(); ) {
    double time = loopPoints.loop_point(i).time();
    if (c >= getNumChildComponents()) {
      addCursor(defaultDesc.get(), time);
      ++i;
      ++c;
    } else {
      Cursor* kid = dynamic_cast<Cursor*>(getChildComponent(c));
      double time2 = kid->getTime();
      if (Math<double>::near(time, time2, 0.001)) {
        ++i;
        ++c;
      } else if (time < time2) {
        addCursor(defaultDesc.get(), time, c);
        ++i;
      } else {
        removeChildComponent(c);
      }
    }
  }

  // Now set the selection range!
  selection_.clear();
  for (int i = 0, size = loopPoints.selected_size(); i < size; ) {
    for (; i < size && !loopPoints.selected(i); ++i);
    if (i < size) {
      int j = i;
      for (; j < size && loopPoints.selected(j); ++j);
      double begin = loopPoints.loop_point(i).time();
      double end = (j < size) ? loopPoints.loop_point(j).time() : range_.end_;
      selection_.insert(TimeRange(begin, end));
      i = j;
    }
  }

  repaint();
}

void Waveform::operator()(const gui::LoopPointList& loopPoints) {
  thread::callAsync(this, &Waveform::addAllCursors, loopPoints);
}

const TimeRange Waveform::getTimeRange() const {
  ScopedLock l(lock_);
  return range_;
}

void Waveform::resized() {
  ScopedLock l(lock_);
  for (int i = getNumChildComponents(); i > 0; --i) {
    Component* comp = getChildComponent(i - 1);
    if (comp->getName() == "Cursor")
      layoutCursor((Cursor*) comp);
  }
}

void Waveform::layoutCursor(Cursor *cursor) const {
  ScopedLock l(lock_);
  juce::Rectangle<int> bounds = getLocalBounds();
  int width = getLocalBounds().getWidth();
  int displayWidth = cursor->desc().display_width();
  bounds.setWidth(displayWidth);
  int x = 0;

  if (!Math<double>::near(range_.begin_, range_.end_, 0.001))
    x = width * (cursor->getTime() - range_.begin_) / (range_.end_ - range_.begin_);

  bounds.setX(x - (displayWidth - cursor->desc().width()) / 2);
  cursor->setBoundsAsync(bounds);
}

void Waveform::doClick(const juce::MouseEvent& e, int clickCount) {
  TimeAndMouseEvent event;
  event.mouseEvent_ = &e;
  event.clickCount_ = clickCount;
  {
    ScopedLock l(lock_);
    event.time_ = xToTime(e.x);
  }

  broadcast(event);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
