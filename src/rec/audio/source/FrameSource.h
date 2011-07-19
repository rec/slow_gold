#ifndef __REC_AUDIO_SOURCE_FRAMESOURCE__
#define __REC_AUDIO_SOURCE_FRAMESOURCE__

#include "rec/audio/source/BufferSource.h"
#include "rec/audio/util/Frame.h"

namespace rec {
namespace audio {
namespace source {

template <typename Sample, int CHANNELS>
class FrameSource : public SourceWithPosition {
 public:
  explicit FrameSource(const Frames<Sample, CHANNELS>& b) : buffer_(b) {}
  virtual ~FrameSource() {}

  virtual void getNextAudioBlock(const Info& info) {
    Info i = info;
    while (i.numSamples > 0) {
      SamplePosition copied = buffer_.getAudioBlock(i, position_);
      if (!copied) {
        LOG(ERROR) << "No samples copied!";
        DCHECK(copied);
        return;
      }
      i.numSamples -= copied;
      i.startSample += copied;
      setNextReadPosition(position_ + copied);
    }
  }

  virtual int64 getTotalLength() const { return buffer_.length(); }

 private:
  const Frames<Sample, CHANNELS>& buffer_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FrameSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_FRAMESOURCE__
