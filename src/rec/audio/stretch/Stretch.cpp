#include "rec/util/math.h"

#include "rec/audio/stretch/Stretch.h"

namespace rec {
namespace audio {
namespace stretch {

double timeScale(const Stretch& d) {
  return d.disabled() ? 1.0 : (d.time_scale() * (100.0 / d.time_percent()));
}

double pitchScale(const Stretch& d) {
  if (d.disabled())
    return 1.0;

  double detune = d.detune_cents() / 100.0 + d.semitone_shift() / 12.0;
  return d.pitch_scale() * pow(2.0, detune);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
