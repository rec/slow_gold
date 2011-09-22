#include <math.h>

#include "rec/audio/util/Gain.h"

namespace rec {
namespace audio {

double getGain(const audio::Gain& gain) {
  if (gain.mute())
    return 0.0;

  if (gain.dim())
    return gain.dim_level();

  return powl(10.0, gain.gain() / 20.0) * gain.level();
}

}  // namespace audio
}  // namespace rec
