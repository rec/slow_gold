#ifndef __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
#define __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__

#include "rec/audio/source/BufferSource.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/GenericFillableBuffer.h"

namespace rec {
namespace audio {
namespace source {

template <typename Sample, int CHANNELS>
class GenericBufferSource : public SourceWithPosition {
 public:
  explicit GenericBufferSource(const Frames<Sample, CHANNELS>& b) : buffer_(b) {}
  virtual ~GenericBufferSource() {}

  virtual void getNextAudioBlock(const Info& info) {
    Info i = info;
    while (i.numSamples > 0) {
      SamplePosition copied = buffer_.getAudioBlock(i, position_);
      if (!copied) {
        LOG(DFATAL) << "No samples copied!";
        return;
      }
      i.numSamples -= copied;
      i.sampleOffset += copied;
      setNextReadPosition(position_ + copied);
    }
  }

  virtual int64 getTotalLength() const { return buffer_.length(); }

 private:
  const Frames<Sample, CHANNELS>& buffer_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericBufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
