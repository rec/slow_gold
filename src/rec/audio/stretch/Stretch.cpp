#include "rec/util/math.h"

#include "rec/audio/stretch/Stretch.h"

namespace rec {
namespace audio {
namespace stretch {

namespace {

const double NO_SCALE = 1.0;
const double PERCENT = 100.0;
const double OCTAVE = 2.0;
const double SEMITONES_PER_OCTAVE = 12.0;
const double CENTS_PER_SEMITONE = 100.0;
const double SEMITONE_LOG = SEMITONES_PER_OCTAVE / log(OCTAVE);

}

double timeScale(const Stretch& d) {
  if (!d.enabled() || d.time_disabled())
    return NO_SCALE;
  return d.time_scale() * PERCENT / d.time_percent();
}

double pitchScale(const Stretch& d) {
  if (!d.enabled() || d.pitch_disabled())
    return NO_SCALE;

  double semitones = d.semitone_shift() + d.detune_cents() / CENTS_PER_SEMITONE;
  return d.pitch_scale() * powl(OCTAVE, semitones / SEMITONES_PER_OCTAVE);
}

double pitchSemitones(const Stretch& d) {
  return SEMITONE_LOG * log(pitchScale(d));
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
