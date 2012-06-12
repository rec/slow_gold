#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {

struct BufferTime {
  Buffer* buffer_;
  SampleTime time_;

  BufferTime(Buffer* b, SampleTime t) : buffer_(b), time_(t) {}
  BufferTime() {}

 private:
  JUCE_LEAK_DETECTOR(BufferTime);
};

// Returns the number of samples actually copied.
SampleTime copy(const BufferTime& from, const BufferTime& to, SampleTime count);

// Clear samples.
void clear(const BufferTime& bt, SampleTime c);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
