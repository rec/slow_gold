#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"

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

Cursor::Cursor(const CursorProto& d, Waveform* waveform, double time)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d) {
  waveform_->addChildComponent(this);
  setTime(time);
}

void Cursor::setTime(double time) {
  ScopedLock l(lock_);
  time_ = time;
  thread::runOnMessageThread(waveform_, &Waveform::setCursorBounds, this);
}

void Cursor::paint(Graphics& g) {
  ScopedLock l(lock_);
  Painter p(desc_.widget(), &g);

  juce::Rectangle<int> bounds = getLocalBounds();

  double middle = bounds.getWidth() / 2.0f;
  double margin = static_cast<double>(desc_.widget().margin());
  double bottom = bounds.getHeight() - 2.0f * margin;

  gui::drawLine(g, desc_.line(), middle, margin, middle, bottom);
}

double Cursor::getTime() const {
  ScopedLock l(lock_);
  return time_;
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
