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
static const int CAPTION_X_OFFSET = 2;
static const int CAPTION_Y_OFFSET = 5;

namespace widget {
namespace waveform {

namespace {

class OutlinedLabel : public gui::SimpleLabel {
 public:
  OutlinedLabel() {}
  virtual ~OutlinedLabel() {}

  static const float INSET = 1.0f;
  static const float CORNER = 2.0f;
  static const float LINE_WIDTH = 5.0f;

  virtual void paint(Graphics& g) {
  }

  virtual void paintOverChildren(Graphics& g) {

    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<float> b;
    b.setX(INSET);
    b.setY(INSET);
    b.setWidth(bounds.getWidth() - 2 * INSET);
    b.setHeight(bounds.getHeight() - 2 * INSET);

    g.setColour(juce::Colours::white);
    // g.setOpacity(0.5f);
    g.fillRoundedRectangle(b, CORNER);

    g.setColour(juce::Colours::black);
    g.setOpacity(1.0f);

    gui::SimpleLabel::paint(g);

    g.drawRoundedRectangle(b, INSET, LINE_WIDTH);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(OutlinedLabel);
};

}  // namespace


Cursor::Cursor(const CursorProto& d, Waveform* waveform, Samples<44100> t,
               int index, bool isTimeCursor)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d),
      index_(index),
      caption_(new OutlinedLabel) {
  desc_.mutable_widget()->set_transparent(true);
  waveform_->addAndMakeVisible(this, 0);
  waveform_->addAndMakeVisible(caption_.get(), 0);

  if (!isTimeCursor) {
    caption_->setEditable(true, false, false);
    caption_->addListener(this);
  }

  setTime(t);
  setRepaintsOnMouseActivity(true);
}

Cursor::~Cursor() {
  waveform_->removeChildComponent(this);
  waveform_->removeChildComponent(caption_.get());
}

void Cursor::labelTextChanged(juce::Label*) {
  waveform_->setCursorText(index_, caption_->getText());
  layout();
}

Samples<44100> Cursor::getTime() const {
  Lock l(lock_);
  return time_;
}

void Cursor::operator()(Samples<44100> time) {
  Lock l(lock_);
  if (!waveform_->isDraggingCursor())
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
  juce::Rectangle<int> b1 = getBounds();
  juce::Rectangle<int> b2 = caption_->getBounds();

  juce::Rectangle<int> bounds = waveform_->getLocalBounds();
  int componentWidth = desc().component_width();
  int x = 0;

  if (waveform_->getTimeRange().size() > SMALLEST_TIME_SAMPLES)
    x = waveform_->timeToX(getTime());

  bounds.setWidth(componentWidth);
  bounds.setX(x - (componentWidth - desc().width()) / 2);

  setBounds(bounds);
  int remains = waveform_->getCursorX(index_ + 1) - getX() - CAPTION_X_OFFSET;

  caption_->setBounds(bounds.getX() + componentWidth + CAPTION_X_OFFSET,
                      CAPTION_Y_OFFSET,
                      std::min(captionWidth_, remains), caption_->getHeight());

  waveform_->repaint(b1);
  waveform_->repaint(b2);
  waveform_->repaint(getBounds());
  waveform_->repaint(caption_->getBounds());
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

void Cursor::setCaption(const String& cap) {
  String c = cap.length() ? cap : String("---");
  caption_->setText(c, false);
  juce::Rectangle<int> bounds = caption_->getBounds();

  float height = caption_->getFont().getHeight() + CAPTION_PADDING * 2;
  bounds.setHeight(static_cast<int>(height));
  captionWidth_ = caption_->getFont().getStringWidth(caption_->getText());
  bounds.setWidth(captionWidth_);
  caption_->setBounds(bounds);
}


}  // namespace waveform
}  // namespace widget
}  // namespace rec
