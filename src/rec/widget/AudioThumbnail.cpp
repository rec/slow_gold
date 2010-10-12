#include "rec/widget/AudioThumbnail.h"
#include "rec/gui/Color.h"

using namespace juce;

namespace rec {
namespace widget {

AudioThumbnailWidget::AudioThumbnailWidget(const AudioThumbnailDesc& desc)
    : WidgetBase<Component, AudioThumbnailDesc>(desc),
      thumbnailCache_(description_.thumbnail_cache()),
      thumbnail_(description_.source_samples_per_thumbnail_sample(),
                 *AudioFormatManager::getInstance(), thumbnailCache_) {
  startTime_ = endTime_ = cursor_ = ratio_ = 0;
  thumbnail_.addChangeListener(this);
}

AudioThumbnailWidget::~AudioThumbnailWidget() {
  thumbnail_.removeChangeListener(this);
}

void AudioThumbnailWidget::setFile(const File& file) {
  ScopedLock l(lock_);
  thumbnail_.setSource(new FileInputSource(file));
  startTime_ = ratio_ = 0;
  endTime_ = thumbnail_.getTotalLength();
  cursor_ = (startTime_ + endTime_) / 2;
}

void AudioThumbnailWidget::setZoomFactor(double amount) {
  if (thumbnail_.getTotalLength() > 0) {
    double timeElapsed = thumbnail_.getTotalLength() - startTime_;
    double timeDisplayed = timeElapsed * (1.0 - jlimit(0.0, 1.0, amount));
    endTime_ = startTime_ + std::max(0.001, timeDisplayed);
    repaint();
  }
}

void AudioThumbnailWidget::mouseWheelMove(const MouseEvent& e,
                                             float incX, float incY) {
  return;
  // no idea what this does yet.  :-D
  if (thumbnail_.getTotalLength() > 0) {
    double newStart = startTime_ + (incX + incY) * (endTime_ - startTime_)
      / 10.0;
    newStart = jlimit(0.0, thumbnail_.getTotalLength() -
                      (endTime_ - startTime_), newStart);
    endTime_ = newStart + (endTime_ - startTime_);
    startTime_ = newStart;
    repaint();
  }
}

Rectangle<int> AudioThumbnailWidget::cursorRectangle() const {
  int margin = description_.widget().margin();
  int thickness = description_.cursor_thickness();

  double position = jlimit(startTime_, endTime_, cursor_);
  double ratio = (position - startTime_) / (endTime_ - startTime_);
  int width = (getWidth() - 2 * margin);
  int cursorX = (margin - thickness / 2) + width * ratio;

  return Rectangle<int>(cursorX, margin, thickness, getHeight() - margin);
}

bool AudioThumbnailWidget::within(int x) const {
  return x >= startTime_ && x <= endTime_;
}

void AudioThumbnailWidget::mouseUp(const MouseEvent& e) {
  int margin = description_.widget().margin();
  int width = getWidth() - 2 * margin;
  double ratio = (e.x - margin) / (1.0 * width);
  setCursor(ratio);
  sendChangeMessage(this);
}

void AudioThumbnailWidget::setCursor(double cursorRatio) {
  double cursor = cursorRatio * thumbnail_.getTotalLength();
  Rectangle<int> before, after;
  {
    ScopedLock l(lock_);
    ratio_ = cursorRatio;
    before = cursorRectangle();
    cursor_ = cursor;
    after = cursorRectangle();
  }

  if (before != after) {
    // TODO: fix cursor ghosting - expanding these rectangles doesn't do it!
    repaint(before);
    repaint(after);
  }
}

void AudioThumbnailWidget::paint(Graphics& g, const Rectangle<int>& bounds) {
  int margin = description_.widget().margin();

  if (thumbnail_.getTotalLength() > 0) {
    int heightPerChannel = (getHeight() - 2 * margin) /
      thumbnail_.getNumChannels();

    for (int i = 0; i < thumbnail_.getNumChannels(); ++i) {
      thumbnail_.drawChannel(g, margin, margin + heightPerChannel * i,
                             getWidth() - 2 * margin, heightPerChannel,
                             startTime_, endTime_,
                             i, 1.0f);
    }

    setColour(g, HIGHLIGHT);
    g.drawRect(cursorRectangle());

  } else {
    g.setFont(14.0f);
    g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                     Justification::centred, margin);
  }
}

int AudioThumbnailWidget::getCursor() const {
  ScopedLock l(lock_);
  return cursor_;
}

double AudioThumbnailWidget::ratio() const {
  ScopedLock l(lock_);
  return ratio_;
}

}  // namespace widget
}  // namespace rec

