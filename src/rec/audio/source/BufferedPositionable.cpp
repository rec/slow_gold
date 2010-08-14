#ifndef __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
#define __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__

#include <glog/logging.h>

#include "rec/audio/source/BufferedPositionable.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
BufferedPositionable<Source>::BufferedPositionable(int channels, Source* source)
    : PositionWrappy<Source>("BufferedPositionable", source),
      filled_(position, getTotalLength()),
      buffer_(channels, getTotalLength()) {
  sourceInfo_.buffer = &buffer_;
}

template <typename Source>
void BufferedPositionable<Source>::setNextReadPosition(int position) {
  ScopedLock l(lock_);
  PositionWrappy<Source>::setNextReadPosition(position);
  if (filled_.remaining(position) < 0)
    filled_.reset(position);
}

template <typename Source>
int64 BufferedPositionable<Source>::available() const {
  ScopedLock l(lock_);
  return filled_.availableFrom(position_);
}

template <typename Source>
void BufferedPositionable<Source>::getNextAudioBlock(const AudioSourceChannelInfo& i) {
  AudioSourceChannelInfo info = i;
  int32 position;
  {
    ScopedLock l(lock_);
    int32 available = remaining();
    if (available < info.numSamples) {
      LOG_FIRST_N(ERROR, 10) << "Didn't have enough samples: "
                             << available << ", " << info.numSamples;
      info.numSamples = available;
    }

    position = position_;
  }

  int32 newPos = rec::audio::copyCircularSamples(buffer_, position, info);

  {
    ScopedLock l(lock_);
    if (position_ == position)
      position_ = newPos;
    else
      LOG_FIRST_N(ERROR, 10) << "Another thread changed position_";
  }
}

// Returns true if there is more to be filled.  Only call this from one
// thread please, it's likely the underlying source is not thread-safe.
template <typename Source>
bool BufferedPositionable<Source>::fillNext(int chunkSize) {
  {
    ScopedLock l(lock_);
    sourceInfo_.numSamples = std::min(chunkSize, filled_.remainingBlock());
    sourceInfo_.startSample = filled.begin();
  }

  source->getNextAudioBlock(sourceInfo_);

  {
    ScopedLock l(lock_);
    // If the next read position has changed, we just throw away all our work.
    return (sourceInfo_.startSample != filled_.begin()) ||
      filled_.increment(sourceInfo_.numSamples);
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
