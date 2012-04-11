#include "rec/util/math.h"

#include "rec/audio/stretch/Stretch.h"

namespace rec {
namespace audio {
namespace stretch {

double timeScale(const Stretch& d) {
  return (!d.enabled() || d.time_disabled()) ? 1.0 :
    (d.time_scale() * (100.0 / d.time_percent()));
}

double pitchScale(const Stretch& d) {
  if (!d.enabled() || d.pitch_disabled())
    return 1.0;

  double detune = (d.detune_cents() / 100.0 + d.semitone_shift()) / 12.0;
  return d.pitch_scale() * pow(2.0, detune);
}

double pitchSemitones(const Stretch& d) {
  return 12.0 * log2(pitchScale(d));
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
