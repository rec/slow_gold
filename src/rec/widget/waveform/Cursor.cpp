#include "rec/widget/waveform/Cursor.h"
#include "rec/audio/Audio.h"
#include "rec/base/Samples.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Proto.h"
#include "rec/widget/waveform/OutlinedCursorLabel.h"

using namespace rec::gui;
using namespace rec::gui::color;

namespace rec {

static const Samples<44100> SMALLEST_TIME_SAMPLES = 10000;
static const int CAPTION_PADDING_INTERNAL = 10;
static const int CAPTION_OFFSET = 10000;
static const int CAPTION_PADDING = 2;
static const int CAPTION_X_OFFSET = -3;
static const int CAPTION_Y_OFFSET = 6;
static const int REMAINS_FUDGE = 8;
static const int SELECTION_BUTTON_PADDING = -2;

static const int GRID_TEXT_HEIGHT = 9;  // from Waveform.cpp

namespace widget {
namespace waveform {

namespace {

class WaveformListener : public GlobalDataListener<WaveformProto> {
 public:
  WaveformListener(Cursor* parent) : parent_(parent) {}
  virtual void operator()(const WaveformProto& p) { (*parent_)(p); }

 private:
  Cursor* const parent_;
};

}

Cursor::Cursor(const CursorProto& d, Waveform* waveform, Samples<44100> t,
               int index, bool isTimeCursor)
    : Component("Cursor"),
      waveform_(waveform),
      desc_(d),
      index_(index),
      isTimeCursor_(isTimeCursor) {
  Lock l(lock_);
  caption_.reset(new OutlinedCursorLabel(this));
  desc_.mutable_widget()->set_transparent(true);
  waveform_->addAndMakeVisible(this, 0);

  if (!isTimeCursor) {
    waveform_->addAndMakeVisible(caption_.get(), 0);
    caption_->addListener(this);
  }

  setTime(t);
  setRepaintsOnMouseActivity(true);
  waveformListener_.reset(new WaveformListener(this));

  setMouseCursor(juce::MouseCursor::DraggingHandCursor);
}

Cursor::~Cursor() {
  waveformListener_.reset();
  waveform_->removeChildComponent(this);
  waveform_->removeChildComponent(caption_.get());
}

void Cursor::startListening() {
  caption_->startListening();
  waveformListener_->startListening();
}

Component* Cursor::getCaption() {
  return caption_.get();
}

void Cursor::labelTextChanged(juce::Label*) {
  setText(caption_->getText());
}

void Cursor::setText(const String& s) {
  waveform_->setCursorText(index_, s);
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

bool Cursor::setDragTime(Samples<44100> t) {
  Lock l(lock_);

  if (!isTimeCursor()) {
    if (index_ == 0 || t < SMALLEST_TIME_SAMPLES)
      return false;

    CursorList& cursors = *waveform_->getCursorsMutable();

    int next = -1;
    int size = static_cast<int>(cursors.size());
    if (index_ > 1 && cursors[index_ - 1]->getTime() > t)
      next = index_ - 1;

    else if (index_ < size - 1 && cursors[index_ + 1]->getTime() < t)
      next = index_ + 1;

    if (next >= 0) {
      cursors[index_] = cursors[next];
      cursors[next] = this;
      LoopPointList lpl = waveform_->DataListener<LoopPointList>::getProto();
      lpl.mutable_loop_point(index_)->set_time(t);
      lpl.mutable_loop_point()->SwapElements(index_, next);
      waveform_->DataListener<LoopPointList>::setProto(lpl);
      waveform_->adjustCursors(lpl, block::BlockSet());
    }
  }

  setTime(t);
  return true;
}

void Cursor::setTime(Samples<44100> time) {
  {
    Lock l(lock_);
    time_ = time;
  }
  layout();
  if (index_ > 1)
    waveform_->getCursors()[index_ - 1]->adjustCaption();
}

void Cursor::layout() {
  juce::Rectangle<int> before = getBounds();

  juce::Rectangle<int> boundsBefore = waveform_->getLocalBounds();
  juce::Rectangle<int> bounds = boundsBefore;
  int componentWidth = desc().component_width();
  int x = 0;

  if (waveform_->getTimeRange().size() > SMALLEST_TIME_SAMPLES)
    x = waveform_->timeToX(getTime());

  bounds.setWidth(componentWidth);
  bounds.setX(x - (componentWidth - desc().width()) / 2);

  if (bounds == boundsBefore)
    return;

  setBounds(bounds);
  adjustCaption();

  if (isTimeCursor_)
    return;
  juce::Rectangle<int> after = getBounds();
  if (before != after) {
    waveform_->repaint(before);
    waveform_->repaint(after);
  }
}

void Cursor::adjustCaption() {
  juce::Rectangle<int> before = caption_->getBounds();

  int remains = waveform_->getCursorX(index_ + 1) - getX() -
    CAPTION_X_OFFSET - REMAINS_FUDGE;
  int captionHeight = caption_->getHeight();
  int dy = ((waveDesc_.show_times_at_top() == waveDesc_.show_labels_at_top()) ?
            GRID_TEXT_HEIGHT : 0) + CAPTION_Y_OFFSET;

  int y = waveDesc_.show_labels_at_top() ? dy :
    (getHeight() - dy - captionHeight);
  int x = getX() + desc().component_width() + CAPTION_X_OFFSET;
  caption_->setBounds(x, y, std::min(captionWidth_, remains), captionHeight);

  if (!isTimeCursor_) {
    juce::Rectangle<int> after = caption_->getBounds();
    if (before != after) {
      waveform_->repaint(before);
      waveform_->repaint(after);
    }
  }
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
  float displayWidth = static_cast<float>(desc().display_width());
  float componentWidth = static_cast<float>(desc().component_width());
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
  if (!caption_->isBeingEdited()) {
    String c = cap.length() ? cap : String("---");
    caption_->setText(c, false);
  }
  resizeCaption();
}

void Cursor::resizeCaption() {
  juce::Rectangle<int> bounds = caption_->getBounds();

  int height = static_cast<int>(caption_->getFont().getHeight() + CAPTION_PADDING * 2);
  bounds.setHeight(height);
  captionWidth_ = caption_->getFont().getStringWidth(caption_->getText()) +
    CAPTION_PADDING_INTERNAL;

  if (caption_->getNumChildComponents())
    captionWidth_ += (height + SELECTION_BUTTON_PADDING);

  bounds.setWidth(captionWidth_);
  caption_->setBounds(bounds);
}

void Cursor::setSelected(bool sel) {
  caption_->setSelected(sel);
}

void Cursor::selectButtonPressed(bool select) {
  waveform_->setSelected(index_, select);
}

void Cursor::operator()(const WaveformProto& wp) {
  Lock l(lock_);

  waveDesc_ = wp;
  thread::callAsync(this, &Cursor::layout);
}

void Cursor::setTooltip(const String& t) {
  SettableTooltipClient::setTooltip(t);
  caption_->setTooltip("Loop Point Name: Edit the Loop Point's name "
                       "by clicking here.");
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
