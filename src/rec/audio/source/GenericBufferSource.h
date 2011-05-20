#ifndef __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
#define __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__

#include "rec/audio/source/BufferSource.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/GenericFillableBuffer.h"

namespace rec {
namespace audio {
namespace source {

template <typename Sample = short, int CHANNELS = 2>
class GenericBufferSource : public BaseBufferSource {
 public:
  typedef util::GenericFillableBuffer<Sample, CHANNELS> FillableBuffer;

  explicit GenericBufferSource(const FillableBuffer& b) : buffer_(b) {}

  virtual void getNextAudioBlock(const Info& info) {
    for (SampleTime i = 0; i <  info.numSamples; ++i) {
      const util::Frame<Sample, CHANNELS>& frame = buffer_.frames()[position_];
      for (int c = 0; c < CHANNELS; ++c)
        convertSample(frame.sample_[c], info.buffer->getSampleData(c, i));

      setNextReadPosition(position_ + 1);
    }
  }

  virtual int64 getTotalLength() const { return buffer_.length(); }

 private:
  const FillableBuffer& buffer_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(GenericBufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GENERICBUFFERSOURCE__
