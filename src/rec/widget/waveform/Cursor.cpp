#include "rec/widget/waveform/Cursor.h"
#include "rec/audio/Audio.h"
#include "rec/base/Samples.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {

static const Samples<44100> SMALLEST_TIME_SAMPLES = 10000;
static const int CAPTION_OFFSET = 10000;
static const int CAPTION_PADDING = 2;
static const int CAPTION_X_OFFSET = 10;
static const int CAPTION_Y_OFFSET = 5;

namespace widget {
namespace waveform {

Cursor::Cursor(const CursorProto& d, Waveform* waveform, Samples<44100> t,
               int index)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d),
      index_(index),
      listeningToClock_(true) {
  desc_.mutable_widget()->set_transparent(true);
  waveform_->addAndMakeVisible(this, 0);
  waveform_->addAndMakeVisible(&caption_, 0);

  setTime(t);
  setRepaintsOnMouseActivity(true);
}

Cursor::~Cursor() {
  waveform_->removeChildComponent(this);
  waveform_->removeChildComponent(&caption_);
}

Samples<44100> Cursor::getTime() const {
  Lock l(lock_);
  return time_;
}

void Cursor::operator()(Samples<44100> time) {
  Lock l(lock_);
  if (listeningToClock_)
    thread::callAsync(this, &Cursor::setTime, time);
}

void Cursor::setTime(Samples<44100> time) {
  {
    Lock l(lock_);
    time_ = time;
  }
  layout();
}

void Cursor::layout() {
  juce::Rectangle<int> bounds = waveform_->getLocalBounds();
  int componentWidth = desc().component_width();
  int x = 0;

  if (waveform_->getTimeRange().size() > SMALLEST_TIME_SAMPLES)
    x = waveform_->timeToX(getTime());


  bounds.setWidth(componentWidth);
  bounds.setX(x - (componentWidth - desc().width()) / 2);

  setBounds(bounds);
#if 1
  caption_.setTopLeftPosition(bounds.getX(), CAPTION_Y_OFFSET);
#else
  int remains = waveform_->getCursorX(index_) - getX() - CAPTION_X_OFFSET;

  caption_.setBounds(bounds.getX(), CAPTION_Y_OFFSET,
                     std::min(captionWidth_, remains), caption_.getHeight());
#endif
  // repaint();
}

void Cursor::paint(Graphics& g) {
 juce::Rectangle<int> bounds;
  {
    Lock l(lock_);
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

  Lock l(lock_);

  p.setColor(highlight ? HIGHLIGHT : BACKGROUND);
  g.fillRect(offset, top, displayWidth, height);

  p.setColor(highlight ? BACKGROUND : FOREGROUND);
  gui::drawLine(g, desc_.line(), middle, top, middle, height);
}

void Cursor::setCaption(const String& c) {
  caption_.setText(c, false);
  juce::Rectangle<int> bounds = caption_.getBounds();

  bounds.setHeight(static_cast<int>(caption_.getFont().getHeight() + CAPTION_PADDING * 2));
  captionWidth_ = caption_.getFont().getStringWidth(caption_.getText());
  bounds.setWidth(captionWidth_);
  caption_.setBounds(bounds);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
