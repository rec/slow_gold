#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include "rec/slow/Preferences.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace gui {

class AudioThumbnailComponent : public Component, public ChangeListener {
 public:
  AudioThumbnailComponent(ChangeListener* listener);
  ~AudioThumbnailComponent();

  void setFile(const File& file);
  void setZoomFactor(double amount);
  void mouseWheelMove(const MouseEvent& e, float incX, float incY);

  Rectangle<int> cursorRectangle() const;

  bool within(int x) const;

  virtual void mouseUp(const MouseEvent& e);

  // Ranges between 0 and 1.
  void setCursor(double cursorRatio);
  void paint(Graphics& g);
  int getCursor() const;
  double ratio() const { return ratio_; }

  // this method is called by the thumbnail when it has changed, so we should repaint it..
  void changeListenerCallback(void*);

 private:
  ChangeListener* listener_;
  const ThumbnailDescription description_;

  AudioThumbnailCache thumbnailCache_;
  AudioThumbnail thumbnail_;
  double startTime_, endTime_, cursor_, ratio_;
  int cursorX_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioThumbnailComponent);
};

}  // namespace gui
}  // namespace rec

#endif
