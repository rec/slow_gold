#ifndef __REC_AUDIO_SOURCE_CIRCULARBUFFER__
#define __REC_AUDIO_SOURCE_CIRCULARBUFFER__

#include "rec/util/Range.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class CircularBuffer {
 public:
  CircularBuffer(Buffer* b) : filled_(b->getNumSamples()), buffer_(b) {}

  SampleTime fillFrom(const BufferTime&, SampleTime);
  SampleTime consumeTo(const BufferTime&, SampleTime);

 private:
  CriticalSection lock_;

  AudioSampleBuffer* buffer_;
  Circular<SampleTime> filled_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CircularBuffer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CIRCULARBUFFER__
