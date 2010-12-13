#ifndef __THUMBNAIL_COMP
#define __THUMBNAIL_COMP

#include <set>

#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace widget {

using namespace rec::util::listener;

class AudioThumbnailWidget : public juce::Component,
                             public juce::ChangeListener,
                             public juce::ChangeBroadcaster,
                             public Broadcaster<double>,
                             public Broadcaster<const AudioThumbnailWidget&>,
                             public Listener<const AudioSourceChannelInfo&>,
                             public Listener<InputStream*> {
 public:
  AudioThumbnailWidget(const AudioThumbnailDesc& desc);
  virtual ~AudioThumbnailWidget();

  void setFile(const tree::VolumeFile& file);
  void setZoomFactor(double amount);
  void mouseWheelMove(const juce::MouseEvent& e, float incX, float incY);

  juce::Rectangle<int> cursorRectangle() const;

  bool within(int x) const;

  virtual void mouseUp(const juce::MouseEvent& e);
  virtual void operator()(const AudioSourceChannelInfo& info);
  virtual void operator()(InputStream* stream) { thumbnail_.loadFrom(*stream); }
  File getThumbnailFile();

  // Ranges between 0 and 1.
  void setCursor(double cursorRatio);
  virtual void paint(juce::Graphics& g);

  int getCursor() const;
  double ratio() const;

  // this method is called by the thumbnail when it has changed, so we should repaint it..
  virtual void changeListenerCallback(ChangeBroadcaster*) { repaint(); }
  bool thumbnailSet() const { return thumbnailSet_; }

 private:
  const AudioThumbnailDesc description_;

  juce::AudioThumbnailCache thumbnailCache_;
  juce::AudioThumbnail thumbnail_;
  double startTime_, endTime_, cursor_, ratio_;
  int cursorX_;
  CriticalSection lock_;
  tree::VolumeFile file_;
  bool thumbnailSet_;

  DISALLOW_COPY_AND_ASSIGN(AudioThumbnailWidget);
};

}  // namespace widget
}  // namespace rec

#endif
