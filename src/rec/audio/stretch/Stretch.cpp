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
const double MIN_DETUNE_DIFFERENCE = 0.05;

double timeScale(const Stretch& d) {
  if (!(d.enabled() && d.time_enabled()))
    return NO_SCALE;
  return PERCENT / d.time_percent();
}

double pitchScale(const Stretch& d, double detuneCents) {
  bool pitchEnabled = d.enabled() && d.pitch_enabled();
  if (!pitchEnabled && near(detuneCents, 0.0, MIN_DETUNE_DIFFERENCE))
    return NO_SCALE;

  double cents = detuneCents;
  if (pitchEnabled)
    cents += d.detune_cents();

  double semitones = cents / CENTS_PER_SEMITONE;
  if (pitchEnabled)
    semitones += d.semitone_shift();

  double scale = powl(OCTAVE, semitones / SEMITONES_PER_OCTAVE);
  if (pitchEnabled)
    scale *= d.pitch_scale();

  return scale;
}

double sampleRateRatio(const StretchParameters& sp) {
  return sp.output_sample_rate() / sp.input_sample_rate();
}

}  // namespace

double timeScale(const StretchParameters& sp) {
  return timeScale(sp.stretch()) * sampleRateRatio(sp);
}

double pitchScale(const StretchParameters& sp) {
  return pitchScale(sp.stretch(), sp.master_tune()) / sampleRateRatio(sp);
}

double pitchSemitones(const StretchParameters& sp) {
  return SEMITONE_LOG * log(pitchScale(sp));
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
