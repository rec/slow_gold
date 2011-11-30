#include "rec/widget/waveform/Cursor.h"
#include "rec/audio/Audio.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {
namespace widget {
namespace waveform {

Cursor::Cursor(const CursorProto& d, Waveform* waveform, RealTime t, int index)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d),
      index_(index),
      listeningToClock_(true) {
  desc_.mutable_widget()->set_transparent(true);
  waveform_->addChildComponent(this);

  setTime(t);
  setRepaintsOnMouseActivity(true);
}

double Cursor::getTime() const {
  ScopedLock l(lock_);
  return time_;
}

void Cursor::operator()(Samples<44100> t) {
  Lock l(lock_);
  if (listeningToClock_)
    setTime(t);
}

void Cursor::setTime(RealTime time) {
  {
    Lock l(lock_);
    time_ = time;
  }
  thread::callAsync(this, &Cursor::layout);
}


void Cursor::layout() {
  Lock l(lock_);

  juce::Rectangle<int> bounds = waveform_->getLocalBounds();
  int componentWidth = desc().component_width();
  int x = 0;

  if (waveform_->getTimeRange().size() > SMALLEST_TIME)
    x = waveform_->timeToX(time_);


  bounds.setWidth(componentWidth);
  bounds.setX(x - (componentWidth - desc().width()) / 2);
  setBounds(bounds);
}

void Cursor::paint(Graphics& g) {
  juce::Rectangle<int> bounds;
  {
    ScopedLock l(lock_);
    bounds = getLocalBounds();
  }

  Painter p(desc_.widget(), &g);

  // TODO: some latent issue lurks in here, causing a pixel or two error for
  // larger cursors.
  float displayWidth = desc().display_width();
  float componentWidth = desc().component_width();

  float middle = componentWidth / 2.0f;
  float top = static_cast<float>(desc_.widget().margin());
  float height = bounds.getHeight() - 2.0f * top;
  float offset = (componentWidth - displayWidth) / 2.0f;
  bool highlight = !isTimeCursor() && isMouseOverOrDragging();

  ScopedLock l(lock_);

  p.setColor(highlight ? HIGHLIGHT : BACKGROUND);
  g.fillRect(offset, top, displayWidth, height);

  p.setColor(highlight ? BACKGROUND : FOREGROUND);
  gui::drawLine(g, desc_.line(), middle, top, middle, height);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
