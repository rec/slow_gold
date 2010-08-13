#ifndef __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
#define __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__

#include <vector>
#include <glog/logging.h>

#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class BufferedPositionable {
 public:
  typedef rec::util::Circular Circular;

  BufferedPositionable(int position, int channels,
                       PositionableAudioSource* source)
      : filled_(position, source->getTotalLength()),
        source_(source),
        buffer_(channels, source->getTotalLength()) {
    sourceInfo_.buffer = &buffer_;
  }

  // Thread-safe accessor.
  Circular filled() const {
    ScopedLock l(lock_);
    return filled_;
  }

  AudioSampleBuffer* buffer() { return buffer_; }

  // Returns true if there is more to be filled.  Only call this from one
  // thread, but thread-safe.
  bool fillNext(int chunkSize) {
    sourceInfo_.numSamples = std::min(chunkSize, filled_.remainingBlock());
    sourceInfo_.startSample = filled.begin();
    source->getNextAudioBlock(sourceInfo_);

    ScopedLock l(lock_);
    return filled_.increment(sourceInfo_.numSamples);
  }

 private:
  Circular filled_;
  PositionableAudioSource* source_;
  AudioSampleBuffer buffer_;
  CriticalSection lock_;
  AudioSourceChannelInfo sourceInfo_;

  DISALLOW_COPY_AND_ASSIGN(BufferedPositionable);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
