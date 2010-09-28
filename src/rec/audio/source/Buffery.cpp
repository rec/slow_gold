#include <glog/logging.h>

#include "rec/audio/source/Buffery.h"
#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

void Buffery::resetFrom(int channels, int position) {
  ScopedLock l(lock_);
  int len = getTotalLength();
  if (buffer_) {
    buffer_->setSize(channels, len, false, false, true);
  } else {
    buffer_.reset(new AudioSampleBuffer(channels, len));
    sourceInfo_.buffer = buffer_.get();
  }

  filled_.reset(position, len);
  setNextReadPosition(position);
}

void Buffery::getNextAudioBlock(const AudioSourceChannelInfo& i) {
  AudioSourceChannelInfo info = i;
  int32 position;
  {
    ScopedLock l(lock_);
    int32 samples = available();
    if (samples < info.numSamples) {
      LOG_FIRST_N(ERROR, 10) << "Didn't have enough samples: "
                             << samples << ", " << info.numSamples;
      info.numSamples = samples;
    }

    position = position_;
  }

  int32 newPos = rec::audio::copyCircularSamples(*buffer_, position, info);

  {
    ScopedLock l(lock_);
    if (position_ == position)
      position_ = newPos;
    else {
      LOG_FIRST_N(ERROR, 10) << "Another thread changed position_";
    }
  }
}

int64 Buffery::available() const {
  ScopedLock l(lock_);
  return filled_.availableFrom(position_);
}

// Returns true if there is more to be filled.  Only call this from one
// thread please, it's likely the underlying source is not thread-safe.
bool Buffery::fillNext(int64 chunkSize) {
  {
    ScopedLock l(lock_);
    sourceInfo_.numSamples = std::min(chunkSize, filled_.remainingBlock());
    sourceInfo_.startSample = filled_.end();
  }

  source_->getNextAudioBlock(sourceInfo_);

  {
    ScopedLock l(lock_);
    // If the next read position has changed, we just throw away all our work.
    return (sourceInfo_.startSample != filled_.end()) ||
      filled_.fill(sourceInfo_.numSamples);
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec

