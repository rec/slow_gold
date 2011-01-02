#include <math.h>

#include "rec/audio/source/TimeScaler.h"

#include "rec/audio/source/Stretchy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace source {

const char* Init(const StretchyProto &d, AudioTimeScaler* s) {
  return s->Init(timeScale(d),
                 d.sample_rate(),
                 d.channels(),
                 pitchScale(d),
                 d.bands(),
                 d.filter_overlap()) ? "error" : NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
