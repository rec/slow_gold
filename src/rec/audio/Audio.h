#ifndef __REC_AUDIO_AUDIO__
#define __REC_AUDIO_AUDIO__

#include "rec/base/RealTime.h"
#include "rec/base/SamplePosition.h"
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

inline RealTime samplesToTime(SamplePosition samples) {
  return RealTime(samples.position_);
}

inline SamplePosition timeToSamples(RealTime time) {
  return SamplePosition(time);
}

static const float HALF_RANGE = 32768.0f;
static const float FULL_RANGE = (2.0f * HALF_RANGE - 1.0f);

inline void convertSample(const short& from, float* to) {
  *to = (from + HALF_RANGE) / FULL_RANGE * 2.0f - 1.0f;
  // LOG_FIRST_N(INFO, 100) << from << " (" << &from << ") <<--- " << *to;
}

inline void convertSample(const float& from, short* to) {
  float f = FULL_RANGE * (1.0f + from) / 2.0f - HALF_RANGE;
  *to = std::min(floorf(f), HALF_RANGE - 1.0f);
  // LOG_FIRST_N(INFO, 100) << from << " --->> " << *to << " (" << to << ")";
}

// A class to represent 24-bit integers.
typedef struct int24 {
  int value_;

  int24(int value) : value_(value) {}
  int24() {}

  operator int() const { return value_; }
  operator=(int value) { value_ = value; }
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
