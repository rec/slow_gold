#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

struct BufferTime {
  Buffer* buffer_;
  SamplePosition time_;

  BufferTime(Buffer* b, SamplePosition t) : buffer_(b), time_(t) {}
  BufferTime() {}
};

// Returns the number of samples actually copied.
SamplePosition copy(const BufferTime& from, const BufferTime& to, SamplePosition count);

// Clear samples.
void clear(const BufferTime& bt, SamplePosition c);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
