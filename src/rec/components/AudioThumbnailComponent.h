#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include "juce_amalgamated.h"
#include "ThumbnailDescription.pb.h"

namespace rec {
namespace gui {

class AudioThumbnailComponent  : public Component, public ChangeListener {
 public:
  AudioThumbnailComponent(const ThumbnailDescription& d)
      : thumbnailCache_(d.thumbnail_cache()),
        thumbnail_(d.source_samples_per_thumbnail_sample(),
                   *AudioFormatManager::getInstance(), thumbnailCache_),
        description_(d) {
    startTime_ = endTime_ = cursor_ = 0;
    thumbnail_.addChangeListener(this);
  }

  static Colour makeColor(const Color& color) {
    return Colour((uint8) color.red(), (uint8) color.green(), 
                  (uint8) color.blue(), (uint8) color.alpha());
  }

  ~AudioThumbnailComponent() {
    thumbnail_.removeChangeListener(this);
  }

  void setFile(const File& file) {
    ScopedLock l(lock_);
    thumbnail_.setSource(new FileInputSource(file));
    startTime_ = 0;
    endTime_ = thumbnail_.getTotalLength();
    cursor_ = (startTime_ + endTime_) / 2;
  }

  void setZoomFactor(double amount) {
    if (thumbnail_.getTotalLength() > 0) {
      double timeElapsed = thumbnail_.getTotalLength() - startTime_;
      double timeDisplayed = timeElapsed * (1.0 - jlimit(0.0, 1.0, amount));
      endTime_ = startTime_ + std::max(0.001, timeDisplayed);
      repaint();
    }
  }

  void mouseWheelMove(const MouseEvent& e, float wheelIncrementX,
                      float wheelIncrementY) {
    if (thumbnail_.getTotalLength() > 0) {
      double newStart = startTime_ + (wheelIncrementX + wheelIncrementY) * (endTime_ - startTime_) / 10.0;
      newStart = jlimit(0.0, thumbnail_.getTotalLength() - (endTime_ - startTime_), newStart);
      endTime_ = newStart + (endTime_ - startTime_);
      startTime_ = newStart;
      repaint();
    }
  }

  Rectangle<int> cursorRectangle() const {
    int margin = description_.margin();
    int thickness = description_.cursor_thickness();

    int position = jlimit(startTime_, endTime_, cursor_);
    float ratio = (position - startTime_) / (endTime_ - startTime_);
    int width = (getWidth() - 2 * margin);
    int cursorX = (margin - thickness / 2) + width * ratio;

    return Rectangle<int>(cursorX, margin, thickness, getHeight() - margin);
  }

  bool within(int x) const { return x >= startTime_ && x <= endTime_; }

  void setCursor(float cursor) {
    ScopedLock l(lock_);
    Rectangle<int> before = cursorRectangle();
    float oldCursor = cursor_;
    cursor_ = cursor;

    if (!within(oldCursor) && !within(cursor_))
      return;

    repaint(before);
    repaint(cursorRectangle());
  }


  void paint(Graphics& g) {
    g.fillAll(makeColor(description_.background()));
    g.setColour(makeColor(description_.background()));
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

      g.drawRect(cursorRectangle());

    } else {
      g.setFont(14.0f);
      g.drawFittedText("(No audio file selected)", 0, 0, getWidth(), getHeight(),
                       Justification::centred, margin);
    }
  }

  int getCursor() const {
    ScopedLock l(lock_);
    return cursor_;
  }

  void drawCursor() {
    int cursor = getCursor();
    if (cursor >= startTime_ && cursor <= endTime_) {

    }
  }


  // this method is called by the thumbnail when it has changed, so we should repaint it..
  void changeListenerCallback(void*) {
    repaint();
  }

  AudioThumbnailCache thumbnailCache_;
  AudioThumbnail thumbnail_;
  double startTime_, endTime_, cursor_;
  int cursorX_;
  CriticalSection lock_;

  const ThumbnailDescription description_;
};

}  // namespace gui
}  // namespace rec

#endif
