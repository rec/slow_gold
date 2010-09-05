#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include "rec/slow/Preferences.h"
#include "juce_amalgamated.h"
#include "ThumbnailDescription.pb.h"

class MainPageK;

namespace rec {
namespace gui {

class AudioThumbnailComponent  : public Component, public ChangeListener {
 public:
  AudioThumbnailComponent(MainPageK* mainPage);

  ~AudioThumbnailComponent();

  void setFile(const File& file);
  void setZoomFactor(double amount);
  void mouseWheelMove(const MouseEvent& e, float incX, float incY);

  Rectangle<int> cursorRectangle() const;

  bool within(int x) const;

  virtual void mouseUp(const MouseEvent& e);

  void setCursor(double cursor);
  void paint(Graphics& g);
  int getCursor() const;

  // this method is called by the thumbnail when it has changed, so we should repaint it..
  void changeListenerCallback(void*);

  MainPageK* mainPage_;
  const ThumbnailDescription description_;

  AudioThumbnailCache thumbnailCache_;
  AudioThumbnail thumbnail_;
  double startTime_, endTime_, cursor_;
  int cursorX_;
  CriticalSection lock_;
};

}  // namespace gui
}  // namespace rec

#endif
