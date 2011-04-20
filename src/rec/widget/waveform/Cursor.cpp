#include "rec/widget/waveform/Cursor.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {
namespace widget {
namespace waveform {

Cursor::Cursor(Instance* i, const CursorProto& d, Waveform* waveform,
               double time, int index)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d),
      index_(index),
      dragging_(false) {
  desc_.mutable_widget()->set_transparent(true);
  waveform_->addChildComponent(this);

  setTime(time);
  setRepaintsOnMouseActivity(true);
}

void Cursor::setTime(double time) {
  thread::runOnMessageThread(this, &Cursor::setCursorBounds, time);
}

double Cursor::getTime() const {
  ScopedLock l(lock_);
  return time_;
}

void Cursor::setCursorBounds(double time) {
  ScopedLock l(lock_);
  time_ = time;
  juce::Rectangle<int> bounds = waveform_->getLocalBounds();
  int componentWidth = desc().component_width();
  int x = 0;

  if (waveform_->getTimeRange().size() > 0.001)
    x = waveform_->timeToX(time);

  bounds.setWidth(componentWidth);
  bounds.setX(x - (componentWidth - desc().width()) / 2);

  setBounds(bounds);
}

void Cursor::paint(Graphics& g) {
  ScopedLock l(lock_);
  Painter p(desc_.widget(), &g);

  // TODO: some latent issue lurks in here, causing a pixel or two error for
  // larger cursors.
  juce::Rectangle<int> bounds = getLocalBounds();
  float displayWidth = desc().display_width();
  float componentWidth = desc().component_width();

  float middle = componentWidth / 2.0f;
  float top = static_cast<float>(desc_.widget().margin());
  float height = bounds.getHeight() - 2.0f * top;
  float offset = (componentWidth - displayWidth) / 2.0f;

  p.setColor(Painter::BACKGROUND);
  g.fillRect(offset, top, displayWidth, height);

  bool highlight = !isTimeCursor() && isMouseOverOrDragging();
  p.setColor(highlight ? Painter::HIGHLIGHT : Painter::FOREGROUND);

  gui::drawLine(g, desc_.line(), middle, top, middle, height);
}

int Cursor::getDragX(const MouseEvent& e) const {
  return getX() + e.x - mouseDragX_;
}

void Cursor::mouseDown(const MouseEvent& e) {
  dragging_ = true;
  mouseDragX_ = e.x;
  dragX_ = getX();
}

void Cursor::mouseDrag(const MouseEvent& e) {
  if (dragging_)
    setTopLeftPosition(getDragX(e), getY());
}

void Cursor::mouseUp(const MouseEvent& e) {
  if (dragging_) {
    dragging_ = false;
    waveform_.cursorDragged(index_, getDragX(e) + desc().component_width() / 2);
  }
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
