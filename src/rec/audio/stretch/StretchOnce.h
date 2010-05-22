#ifndef __REC_STRETCH_ONCE
#define __REC_STRETCH_ONCE

#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace timescaler {

AudioSampleBuffer* stretchOnce(const Description& desc,
                               const AudioSampleBuffer& inbuf);

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCH_ONCE
