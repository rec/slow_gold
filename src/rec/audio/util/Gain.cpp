#include <math.h>

#include "rec/audio/util/Gain.h"

namespace rec {
namespace audio {

// Skin

static const double GAIN_FACTOR = 10.0;
static const double GAIN_EXPONENT = 20.0;

double getGain(const audio::Gain& gain) {
  if (gain.mute())
    return 0.0;

  if (gain.dim())
    return gain.dim_level();

  double g = gain.gain() / GAIN_EXPONENT;
  return static_cast<double>(pow(GAIN_FACTOR, g) * gain.level());
}

}  // namespace audio
}  // namespace rec
