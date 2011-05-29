#include "rec/audio/util/Gain.h"

namespace rec {
namespace audio {

float getGain(const audio::Gain& gain) {
  if (gain.mute())
    return 0.0f;

  if (gain.dim())
    return gain.dim_level();

  return gain.level();
}

}  // namespace audio
}  // namespace rec
