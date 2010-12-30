#ifndef __REC_AUDIO_SOURCE_CLEAR__
#define __REC_AUDIO_SOURCE_CLEAR__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

inline void clear(const AudioSourceChannelInfo& i, int offset = 0) {
  i.buffer->clear(i.startSample + offset, i.numSamples - offset);
}

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CLEAR__
