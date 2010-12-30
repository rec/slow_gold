#ifndef __REC_GUI_CACHEDTHUMBNAIL__
#define __REC_GUI_CACHEDTHUMBNAIL__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

class CachedThumbnail
  : public Listener<const AudioSourceChannelInfo&>,
    public Broadcaster<const juce::AudioThumbnail&> {
 public:
  CachedThumbnail(const File& file, int compression, int sampleLength);
  virtual ~CachedThumbnail();

  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

  void writeThumbnail(bool deferred);

  bool isFull() const { return written_; }

 private:
  const File file_;
  juce::AudioThumbnail thumbnail_;
  juce::AudioThumbnailCache cache_;
  bool written_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedThumbnail);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_CACHEDTHUMBNAIL__
