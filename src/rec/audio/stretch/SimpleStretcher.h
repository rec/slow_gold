#ifndef __REC_SIMPLE_STRETCHER
#define __REC_SIMPLE_STRETCHER

#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace timescaler {

class Simple {
 public:
  Simple() : duringScaleOperation_(false), scaleNeeded_(false) {}

  bool requestRescale(const Description& desc,
                      const AudioSampleBuffer& inbuf,
                      scoped_ptr<AudioSampleBuffer>* outbuf);

  const static int CHUNK_SIZE;

 private:
  CriticalSection lock_;
  bool duringScaleOperation_;
  bool scaleNeeded_;
  Description description_;
  Description nextDescription_;

  DISALLOW_COPY_AND_ASSIGN(Simple);
};

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_SIMPLE_STRETCHER
