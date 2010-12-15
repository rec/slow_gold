#include "rec/widget/waveform/Waveform.h"
#include "rec/util/Math.h"

namespace rec {
namespace widget {
namespace waveform {

Waveform::Waveform(const WaveformProto& d)
    : Component("Waveform"),
      desc_(d),
      thumbnail_(NULL),
      begin_(0),
      end_(0) (
}

void Waveform::setAudioThumbnail(juce::AudioThumbnail* thumbnail) {
  ScopedLock l(lock_);
  thumbnail_ = thumbnail;
  setTimeBounds(0, thumbnail_->getTotalLength());
}

void Waveform::paint(Graphics& g) {
  Painter p(description_.widget(), &g);
  ScopedLock l(lock_);
  if (thumbnail_) {
    if (desc_.layout() == WaveformProto::PARALLEL) {
      thumbnail_->drawChannels(g, getLocalBounds(), begin_, end_, 1.0f);

    } else {
      for (int i = 0; i < thumbnail_.getNumChannels(); ++i) {
        p.setColor(i + 1);
        thumbnail_->drawChannel(g, getLocalBounds(), begin_, end_, i, 1.0f);
      }
    }

  } else {
    g.setFont(14.0f);
    g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                     Justification::centred, margin);
  }
}

Waveform::~Waveform() {
  for (int i = getNumChildComponents(); i > 0; --i)
    delete getChildComponent(i - 1);
}

Cursor* Waveform::addCursor(const CursorProto& desc, float time) {
  Cursor* cursor = new Cursor(desc);
  addChildComponent(cursor);
  moveCursor(cursor, time);
  return cursor;
}

void Waveform::moveCursor(Cursor* cursor, float time) {
  cursor->setTime(time);
  layoutCursor(cursor);
}

void Waveform::setTimeBounds(float begin, float end) {
  ScopedLock l(lock_);
  begin_ = begin;
  end_ = end;
  repaint();
  layoutCursors();
}

void Waveform::layoutCursors() {
  for (int i = getNumChildComponents(); i > 0; --i) {
    Component* comp = getChildComponent(i);
    if (comp->getName() == "Cursor")
      layoutCursor((Cursor) comp);
  }
}

void Waveform::layoutCursor(Cursor *cursor) {
  ScopedLock l(lock_);
  juce::Rectangle<int> bounds = getLocalBounds();
  int width = getLocalBounds().getWidth();
  int displayWidth = cursor->desc()->display_width();
  bounds.setWidth(displayWidth);
  int x = 0;
  if (!Math::near(begin_, end_, 0.001))
    x = width * (cursor->getTime() - begin_) / (end_ - begin_);

  bounds.setX(x - (displayWidth - cursor.desc().width()) / 2);
}

void Waveform::mouseUp(const MouseEvent& e) {
  broadcast(e.x * (end_ - begin_) / getWidth());
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
