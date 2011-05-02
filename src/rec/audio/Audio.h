#ifndef __REC_AUDIO_AUDIO__
#define __REC_AUDIO_AUDIO__

#include "rec/util/Range.h"

namespace rec {
namespace audio {

typedef AudioSampleBuffer Buffer;
typedef AudioSourceChannelInfo Info;
typedef PositionableAudioSource Source;

namespace transport {

enum State {STOPPED, RUNNING};
inline State invert(State s) { return s ? STOPPED : RUNNING; }

}  // namespace transport

inline RealTime samplesToTime(SampleTime samples, RealTime rate = 44100.0) {
  return samples / rate;
}

inline SampleTime timeToSamples(RealTime time, double rate = 44100.0) {
  return static_cast<SampleTime>(time * rate);
}

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
