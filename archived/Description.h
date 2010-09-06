#ifndef __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
#define __REC_AUDIO_STRETCH_IN_BACKGROUND_H__

#include "rec/audio/stretch/TimeScaler.h"

class AudioSampleBuffer;

namespace rec {
namespace audio {
namespace stretch {

typedef rec::audio::timescaler::Description TimeScalerDescription;

// CircularSamples is multiple parallel samples, arranged as circular buffers.
template <typename Samples>
struct CircularSamples {
  Circular circular_;
  Range<Samples*> samples_;

  Samples getSamples(int channel) const {
    return samples_.begin_[channel] + circular_.position_;
  }
};

// Description is a complete description of a single time stretch operation.
template <typename Samples>
struct Description {
  TimeScalerDescription timescale_;
  CircularSamples<Samples> in_, out_;
};

// Given an AudioSampleBuffer, extracts all the channels of sample data as a
// Range.
Range<float**> makeRange(const AudioSampleBuffer& b);

// Given an input buffer with position and offset, an output buffer and
// timescale information, creates a Description, resizing the output buffer if
// necessary.
Description<float*> makeDescriptionAndResize(
    const TimeScalerDescription& timescale,
    const AudioBuffer& inBuf,
    int inPosition,
    int inSize,
    AudioBuffer* outBuf);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IN_BACKGROUND_H__
