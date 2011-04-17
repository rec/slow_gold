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

Waveform::Waveform(Instance *instance, const WaveformProto& d,
                   const CursorProto* timeCursor)
    : Component("Waveform"),
      instance_(instance),
      desc_(d),
      thumbnail_(NULL),
      zoomData_(this) {
  setName("Waveform");

  timeCursor_ = new Cursor(instance_, *timeCursor, this, 0.0f, -1);
  addAndMakeVisible(timeCursor_);
  // desc_.set_selection_frame_in_seconds(0);
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
    resized();
  }
  thread::runOnMessageThread(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  ScopedLock l(lock_);

  if (thumbnail_) {
    SelectionRange::iterator i = selection_.begin();
    TimeRange r = getTimeRange();
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

  } else {
    g.setFont(14.0f);
    g.drawFittedText("Drop a file here or double-click to open a new file",
                     0, 0, getWidth(), getHeight(), juce::Justification::centred, 0);
  }
}

int Waveform::timeToX(double t) const {
  TimeRange r = getTimeRange();
  return static_cast<int>(getWidth() * (t - r.begin_) / r.size());
}

double Waveform::xToTime(int x) const {
  TimeRange r = getTimeRange();
  return r.begin_ + (x *  r.size()) / getWidth();
}

void Waveform::addAllCursors(const gui::LoopPointList& loopPoints) {
  CursorSet cursors;
  int size = loopPoints.loop_point_size();
  for (int i = 0; i < size; ++i) {
    double time = loopPoints.loop_point(i).time();
    ptr<Cursor> c(new Cursor(instance_, CursorProto::default_instance(),
                             this, time, i));
    c->setCursorBounds(time);
    cursors.insert(c.get());
    addAndMakeVisible(c.transfer());
  }

  while (getNumChildComponents() > size + 1)
    delete removeChildComponent(1);

  setSelection(loopPoints);
}

void Waveform::setSelection(const gui::LoopPointList& loopPoints) {
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
  instance_->listeners_(selection_);

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
  ScopedLock l(lock_);
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

  return r;
}

void Waveform::doClick(const juce::MouseEvent& e, int clickCount) {
  TimeAndMouseEvent event;
  event.mouseEvent_ = &e;
  event.clickCount_ = clickCount;
  {
    ScopedLock l(lock_);
    event.time_ = xToTime(e.x);
  }

  instance_->listeners_(event);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
