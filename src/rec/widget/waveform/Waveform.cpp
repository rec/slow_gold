#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/util/Math.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace widget {
namespace waveform {

Waveform::Waveform(const WaveformProto& d)
  : desc_(d), thumbnail_(NULL), range_(0, 0) {
  setName("Waveform");
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* thumbnail) {
  ScopedLock l(lock_);
  thumbnail_ = thumbnail;
  setTimeBounds(0, thumbnail_->getTotalLength());
  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::paint(Graphics& g) {
  Painter p(desc_.widget(), &g);
  ScopedLock l(lock_);
  if (thumbnail_) {
    if (desc_.layout() == WaveformProto::PARALLEL) {
      thumbnail_->drawChannels(g, getLocalBounds(), range_.begin_, range_.end_, 1.0f);

    } else {
      for (int i = 0; i < thumbnail_->getNumChannels(); ++i) {
        p.setColor(i + 1);
        thumbnail_->drawChannel(g, getLocalBounds(), range_.begin_, range_.end_, i, 1.0f);
      }
    }

  } else {
    g.setFont(14.0f);
    g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                     juce::Justification::centred, 0);
  }
}

Waveform::~Waveform() {
  ScopedLock l(lock_);
  for (int i = getNumChildComponents(); i > 0; --i)
    delete getChildComponent(i - 1);
}

Cursor* Waveform::addCursor(const CursorProto& desc, float time) {
  ScopedLock l(lock_);
  Cursor* cursor = new Cursor(desc, this);
  addAndMakeVisible(cursor);
  return cursor;
}

void Waveform::setTimeBounds(float begin, float end) {
  {
    ScopedLock l(lock_);
    range_.begin_ = begin;
    range_.end_ = end;
  }
  layoutCursors();

  thread::callAsync(this, &Waveform::repaint);
}

void Waveform::operator()(const juce::AudioThumbnail&) {
  thread::callAsync(this, &Waveform::repaint);
}

const TimeBounds Waveform::getTimeBounds() const {
  ScopedLock l(lock_);
  return TimeBounds(range_.begin_, range_.end_);
}

void Waveform::layoutCursors() {
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
  if (!Math<float>::near(range_.begin_, range_.end_, 0.001))
    x = width * (cursor->getTime() - range_.begin_) / (range_.end_ - range_.begin_);

  bounds.setX(x - (displayWidth - cursor->desc().width()) / 2);
  cursor->setBoundsAsync(bounds);
}

void Waveform::mouseUp(const juce::MouseEvent& e) {
  float time;
  {
    ScopedLock l(lock_);
    time = e.x * (range_.end_ - range_.begin_) / getWidth();
  }
  const TimeAndMouseEvent event(time, &e);
  broadcast(event);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
