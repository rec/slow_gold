#ifndef __REC_AUDIO_SOURCE_BUFFERYTHUMBNAIL__
#define __REC_AUDIO_SOURCE_BUFFERYTHUMBNAIL__

#include "rec/audio/source/AudioThumbnail.h"
#include "rec/audio/source/Buffery.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class BufferyThumbnail
  : public Buffery,
    public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  BufferyThumbnail(const widget::tree::VolumeFile& file, int blockSize);
  ~BufferyThumbnail();

  virtual void operator()(const AudioSourceChannelInfo& info);

 private:
  const File thumbnailCacheFile_;
  AudioThumbnail thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferyThumbnail);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYTHUMBNAIL__
