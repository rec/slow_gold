#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

struct BufferTime {
  Buffer* buffer_;
  Samples<44100> time_;

  BufferTime(Buffer* b, Samples<44100> t) : buffer_(b), time_(t) {}
  BufferTime() {}

 private:
  JUCE_LEAK_DETECTOR(BufferTime);
};

// Returns the number of samples actually copied.
Samples<44100> copy(const BufferTime& from, const BufferTime& to, Samples<44100> count);

// Clear samples.
void clear(const BufferTime& bt, Samples<44100> c);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
