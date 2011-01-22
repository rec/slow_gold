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

const CursorProto& Waveform::defaultTimeCursor() {
  static Defaulter<CursorProto> c(
      "widget {colors {color: {name: \"yellow\"}}}");
  return c.get();
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* thumbnail) {
  ScopedLock l(lock_);
  thumbnail_ = thumbnail;
  setTimeBounds(TimeBounds(0, thumbnail_ ? thumbnail_->getTotalLength() : 0));
  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  ScopedLock l(lock_);
  if (thumbnail_) {
    SelectionRange::iterator i = selection_.begin();
    Range<double> r = range_;
    while (r.size() > 0.0) {
      for (; i != selection_.end() && i->end_ <= r.begin_; ++i);
      bool selected = (i != selection_.end() && r.begin_ >= i->begin_);
      Range<double> draw = r;
      if (selected)
        r.end_ = i->end_;

      if (desc_.layout() == WaveformProto::PARALLEL) {
        p.setColor(1 + 2 * selected);
        thumbnail_->drawChannels(g, getLocalBounds(), draw.begin_, draw.end_, 1.0f);

      } else {
        for (int i = 0; i < thumbnail_->getNumChannels(); ++i) {
          p.setColor(i + 1 + 2 * selected);
          thumbnail_->drawChannel(g, getLocalBounds(), draw.begin_, draw.end_, i, 1.0f);
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

Waveform::~Waveform() {
  ScopedLock l(lock_);
  for (int i = getNumChildComponents(); i > 0; --i)
    delete getChildComponent(i - 1);
}

Cursor* Waveform::addCursor(const CursorProto& desc, double time) {
  ScopedLock l(lock_);
  Cursor* cursor = new Cursor(desc, this);
  addAndMakeVisible(cursor);
  return cursor;
}

void Waveform::setTimeBounds(const TimeBounds& bounds) {
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

const TimeBounds Waveform::getTimeBounds() const {
  ScopedLock l(lock_);
  return TimeBounds(range_.begin_, range_.end_);
}

void Waveform::resized() {
  ScopedLock l(lock_);
  for (int i = getNumChildComponents(); i > 0; --i) {
    Component* comp = getChildComponent(i - 1);
    if (comp->getName() == "Cursor")
      layoutCursor((Cursor*) comp);
  }
}

void Waveform::layoutCursor(Cursor *cursor) {
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
    event.time_ = e.x * (range_.end_ - range_.begin_) / getWidth();
  }

  broadcast(event);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
