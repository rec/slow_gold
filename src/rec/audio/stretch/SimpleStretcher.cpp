#include <vector>

#include "rec/audio/stretch/SimpleStretcher.h"
#include "rec/audio/stretch/StretchOnce.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

const int Simple::CHUNK_SIZE = 512;

bool Simple::requestRescale(const Description& desc,
                            const AudioSampleBuffer& inbuf,
                            scoped_ptr<AudioSampleBuffer> *outbuf) {
  {
    ScopedLock l(lock_);
    nextDescription_ = desc;
    scaleNeeded_ = true;
    if (duringScaleOperation_)
      return false;

    duringScaleOperation_ = true;
  }

  scoped_ptr<AudioSampleBuffer> buffer;
  while (true) {
    {
      ScopedLock l(lock_);
      if (!scaleNeeded_) {
        duringScaleOperation_ = false;
        outbuf->reset(buffer.transfer());
        return true;
      }
      description_ = nextDescription_;
      scaleNeeded_ = false;
    }
    buffer.reset(stretchOnce(description_, inbuf));
  }
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
