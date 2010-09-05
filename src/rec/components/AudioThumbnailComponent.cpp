#include "AudioThumbnailComponent.h"
#include "MainPageK.h"

namespace rec {
namespace gui {

AudioThumbnailComponent::AudioThumbnailComponent(MainPageK* mainPage)
    : mainPage_(mainPage),
      description_(rec::slow::getPreferences()->get().thumbnail()),
      thumbnailCache_(description_.thumbnail_cache()),
      thumbnail_(description_.source_samples_per_thumbnail_sample(),
                 *AudioFormatManager::getInstance(), thumbnailCache_) {
  startTime_ = endTime_ = cursor_ = 0;
  thumbnail_.addChangeListener(this);
}

namespace {

uint32 makeARGB(const Color& c) {
  if (c.has_argb())
    return c.argb();

  else if (c.has_rgb())
    return (c.alpha() << 24) | c.rgb();

  else
    return (c.alpha() << 24) | (c.red() << 16) | (c.green() << 8) | c.blue();
}

Colour makeColor(const Color& color) { return Colour(makeARGB(color)); }
void setColor(const Color& c, Graphics* g) { g->setColour(makeColor(c)); }

}


AudioThumbnailComponent::~AudioThumbnailComponent() {
  thumbnail_.removeChangeListener(this);
}

void AudioThumbnailComponent::setFile(const File& file) {
  ScopedLock l(lock_);
  thumbnail_.setSource(new FileInputSource(file));
  startTime_ = 0;
  endTime_ = thumbnail_.getTotalLength();
  cursor_ = (startTime_ + endTime_) / 2;
}

void AudioThumbnailComponent::setZoomFactor(double amount) {
  if (thumbnail_.getTotalLength() > 0) {
    double timeElapsed = thumbnail_.getTotalLength() - startTime_;
    double timeDisplayed = timeElapsed * (1.0 - jlimit(0.0, 1.0, amount));
    endTime_ = startTime_ + std::max(0.001, timeDisplayed);
    repaint();
  }
}

void AudioThumbnailComponent::mouseWheelMove(const MouseEvent& e, float incX, float incY) {
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

Rectangle<int> AudioThumbnailComponent::cursorRectangle() const {
  int margin = description_.margin();
  int thickness = description_.cursor_thickness();

  double position = jlimit(startTime_, endTime_, cursor_);
  double ratio = (position - startTime_) / (endTime_ - startTime_);
  int width = (getWidth() - 2 * margin);
  int cursorX = (margin - thickness / 2) + width * ratio;

  return Rectangle<int>(cursorX, margin, thickness, getHeight() - margin);
}

bool AudioThumbnailComponent::within(int x) const {
  return x >= startTime_ && x <= endTime_;
}

void AudioThumbnailComponent::mouseUp(const MouseEvent& e) {
  int margin = description_.margin();
  int width = getWidth() - 2 * margin;
  double ratio = (e.x - margin) / (1.0 * width);
  double position = startTime_ + ratio * (endTime_ - startTime_);
  mainPage_->setPosition(position);
}

void AudioThumbnailComponent::setCursor(double cursor) {
  ScopedLock l(lock_);
  Rectangle<int> before = cursorRectangle();
  cursor_ = cursor;
  Rectangle<int> after = cursorRectangle();

  if (before != after) {
    repaint(before);
    repaint(cursorRectangle());
  }
}

void AudioThumbnailComponent::paint(Graphics& g) {
  g.fillAll(makeColor(description_.background()));
  setColor(description_.foreground(), &g);
  int margin = description_.margin();

  if (thumbnail_.getTotalLength() > 0) {
    int heightPerChannel = (getHeight() - 2 * margin) /
      thumbnail_.getNumChannels();

    for (int i = 0; i < thumbnail_.getNumChannels(); ++i) {
      thumbnail_.drawChannel(g, margin, margin + heightPerChannel * i,
                            getWidth() - 2 * margin, heightPerChannel,
                            startTime_, endTime_,
                            i, 1.0f);
    }

    setColor(description_.cursor(), &g);
    g.drawRect(cursorRectangle());

  } else {
    g.setFont(14.0f);
    g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                     Justification::centred, margin);
  }
}

int AudioThumbnailComponent::getCursor() const {
  ScopedLock l(lock_);
  return cursor_;
}

// this method is called by the thumbnail when it has changed, so we should repaint it..
void AudioThumbnailComponent::changeListenerCallback(void*) {
  repaint();
}

}  // namespace gui
}  // namespace rec

