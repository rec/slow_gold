#ifndef __REC_AUDIO_STRETCH_STRETCHY__
#define __REC_AUDIO_STRETCH_STRETCHY__

#include "rec/audio/stretch/Stretchy.pb.h"

namespace rec {
namespace audio {
namespace stretch {

inline double timeScale(const Stretch& d) {
  return d.disabled() ? 1.0 : (d.time_scale() * (100.0 / d.time_percent()));
}

inline double pitchScale(const Stretch& d) {
  if (d.disabled())
    return 1.0;
  double detune = d.detune_cents() / 100.0 + d.semitone_shift() / 12.0;
  return d.pitch_scale() * pow(2.0, detune);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_STRETCHY__
