#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/STL.h"
#include "rec/util/thread/CallAsync.h"

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
      thumbnail_(NULL),
      range_(0, 0),
      zoomData_(this) {
  setName("Waveform");

  timeCursor_ = new Cursor(*timeCursor, this, 0.0f);
  addAndMakeVisible(timeCursor_);
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
    ScopedLock l(lock_);
    thumbnail_ = thumbnail;
    setTimeRange(TimeRange(0, thumbnail_ ? thumbnail_->getTotalLength() : 0));
    resized();
  }
  thread::runOnMessageThread(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  ScopedLock l(lock_);

  if (thumbnail_) {
    SelectionRange::iterator i = selection_.begin();
    Range<double> r = getTimeRange();
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

void Waveform::setTimeRange(const TimeRange& bounds) {
  {
    ScopedLock l(lock_);
    range_ = bounds;
#if 0
    if (!zoom_.has_begin())
      zoom_.set_begin(range_.begin_);

    if (!zoom_.has_end())
      zoom_.set_end(range_.end_);
#endif
  }

  resized();
}


int Waveform::timeToX(double t) const {
  return static_cast<int>(getWidth() * (t - range_.begin_) / range_.size());
}

double Waveform::xToTime(int x) const {
  return range_.begin_ + (x * range_.size()) / getWidth();
}

void Waveform::operator()(const juce::AudioThumbnail&) {
  thread::runOnMessageThread(this, &Waveform::repaint);
}

void Waveform::operator()(const ZoomProto& zp) {
  ScopedLock l(lock_);
  zoom_ = zp;
}

void Waveform::addAllCursors(const gui::LoopPointList& loopPoints) {
  CursorSet cursors;
  int size = loopPoints.loop_point_size();
  for (int i = 0; i < size; ++i) {
    double time = loopPoints.loop_point(i).time();
    ptr<Cursor> c(new Cursor(CursorProto::default_instance(), this, time));
    setCursorBounds(c.get());
    cursors.insert(c.get());
    addAndMakeVisible(c.transfer());
  }
  while (getNumChildComponents() > size + 1)
    delete removeChildComponent(1);

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
  selectionBroadcaster_.broadcast(selection_);
  repaint();
}

void Waveform::layoutCursors() {
  for (int i = getNumChildComponents(); i > 0; --i) {
    Component* comp = getChildComponent(i - 1);
    if (comp->getName() == "Cursor")
      setCursorBounds(dynamic_cast<Cursor*>(comp));
  }
  repaint();
}

void Waveform::operator()(const gui::LoopPointList& loopPoints) {
  thread::callAsync(this, &Waveform::addAllCursors, loopPoints);
}

const TimeRange Waveform::getTimeRange() const {
  ScopedLock l(lock_);
  return TimeRange(zoom_.has_begin() ? zoom_.begin() : 0,
                   zoom_.has_end() ? zoom_.end() :
                   thumbnail_ ? thumbnail_->getTotalLength() : 0);
}

void Waveform::resized() {
  thread::runOnMessageThread(this, &Waveform::layoutCursors);
}

void Waveform::setCursorBounds(Cursor *cursor) const {
  TimeRange range = getTimeRange();
  juce::Rectangle<int> bounds = getLocalBounds();
  int width = bounds.getWidth();
  int displayWidth = cursor->desc().display_width();
  int x = 0;

  if (!Math<double>::near(range.begin_, range.end_, 0.001))
    x = static_cast<int>(width * (cursor->getTime() - range.begin_) /
                         (range.end_ - range.begin_));

  bounds.setWidth(displayWidth);
  bounds.setX(x - (displayWidth - cursor->desc().width()) / 2);

  cursor->setBounds(bounds);
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
