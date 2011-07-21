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

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_AUDIO__
