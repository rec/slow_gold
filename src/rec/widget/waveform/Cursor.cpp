#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {
namespace widget {
namespace waveform {

namespace {

typedef StateColors CursorStateColors[CursorProto::Type_ARRAYSIZE];

const CursorStateColors& getStateColors() {
  static CursorStateColors colors = {
    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // NONE

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // PLAYBACK_POSITION

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_START

    {
      makeColors(0x0, 0x0),  // NONE
      makeColors(0x0, 0x0),  // DOWN
      makeColors(0x0, 0x0),  // HOVERING
    },  // LOOP_END
  };

  return colors;
}

}  // namespace


Cursor::Cursor(const CursorProto& d, Waveform* waveform, float time)
    : Component("Cursor"), waveform_(waveform), desc_(d) {
  waveform->addChildComponent(this);
  setTime(time);
}

void Cursor::setTime(float time) {
  ScopedLock l(lock_);
  time_ = time;
  waveform_->layoutCursor(this);
}

void Cursor::paint(Graphics& g) {
  ScopedLock l(lock_);
  Painter p(desc_.widget(), &g);
  juce::Rectangle<int> bounds = getLocalBounds();

  float middle = bounds.getWidth() / 2.0f;
  float margin = desc_.widget().margin();
  float bottom = bounds.getHeight() - 2.0f * margin;

  DLOG(INFO) << middle << ", " << margin << ", " << middle << ", " << bottom;
  gui::drawLine(g, desc_.line(), middle, margin, middle, bottom);
}

float Cursor::getTime() const {
  ScopedLock l(lock_);
  return time_;
}

void Cursor::handleAsyncUpdate() {
  setBounds(bounds_);
}

void Cursor::setBoundsAsync(const juce::Rectangle<int>& bounds) {
  bounds_ = bounds;
  triggerAsyncUpdate();
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
