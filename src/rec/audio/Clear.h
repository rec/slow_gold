#ifndef __REC_AUDIO_CLEAR__
#define __REC_AUDIO_CLEAR__

#include "rec/base/base.h"

namespace rec {
namespace audio {

inline void clear(const AudioSourceChannelInfo& i, int offset = 0) {
  i.buffer->clear(i.startSample + offset, i.numSamples - offset);
}

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_CLEAR__
