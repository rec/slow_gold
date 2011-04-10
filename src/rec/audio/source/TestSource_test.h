#ifndef __REC_AUDIO_SOURCE_TESTSOURCE__
#define __REC_AUDIO_SOURCE_TESTSOURCE__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

void testSource(PositionableAudioSource* source,
                int numSamples = 32,
                int readOffset = 0,
                int writeOffset = 0);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TESTSOURCE__
