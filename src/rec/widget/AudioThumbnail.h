#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include <set>

#include "rec/widget/AudioThumbnail.pb.h"
#include "rec/widget/Widget.h"

namespace rec {
namespace widget {

class AudioThumbnailWidget : public WidgetBase<Component, AudioThumbnailDesc>,
                             public ChangeListener,
                             public ChangeBroadcaster {
 public:
  AudioThumbnailWidget(const AudioThumbnailDesc& desc);
  ~AudioThumbnailWidget();

  void setFile(const File& file);
  void setZoomFactor(double amount);
  void mouseWheelMove(const MouseEvent& e, float incX, float incY);

  Rectangle<int> cursorRectangle() const;

  bool within(int x) const;

  virtual void mouseUp(const MouseEvent& e);

  // Ranges between 0 and 1.
  void setCursor(double cursorRatio);
  virtual void paint(Graphics& g, const Rectangle<int>& bounds);

  int getCursor() const;
  double ratio() const;

  // this method is called by the thumbnail when it has changed, so we should repaint it..
  virtual void changeListenerCallback(void*) { repaint(); }

 private:
  const AudioThumbnailDesc description_;

  AudioThumbnailCache thumbnailCache_;
  AudioThumbnail thumbnail_;
  double startTime_, endTime_, cursor_, ratio_;
  int cursorX_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(AudioThumbnailWidget);
};

}  // namespace widget
}  // namespace rec

#endif
