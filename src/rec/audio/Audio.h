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

static const float HALF_RANGE = 32768.0f;
static const float FULL_RANGE = (2.0f * HALF_RANGE - 1.0f);

inline void convertSample(const short& from, float* to) {
  *to = (from + HALF_RANGE) / FULL_RANGE * 2.0f - 1.0f;
  LOG_FIRST_N(INFO, 100) << from << " (" << &from << ") <<--- " << *to;
}

inline void convertSample(const float& from, short* to) {
  float f = FULL_RANGE * (1.0f + from) / 2.0f - HALF_RANGE;
  *to = std::min(floorf(f), HALF_RANGE - 1.0f);
  LOG_FIRST_N(INFO, 100) << from << " --->> " << *to << " (" << to << ")";
}

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
