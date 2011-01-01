#include <math.h>

#include "rec/audio/source/TimeScaler.h"

#include "rec/audio/source/Stretchy.pb.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace source {

const char* Init(const StretchyProto &d, AudioTimeScaler* s) {
  double detune = d.detune_cents() / 100.0 + d.semitone_shift() / 12.0;
  return s->Init(d.time_scale(),
                 d.sample_rate(),
                 d.channels(),
                 d.pitch_scale() * pow(2.0, detune),
                 d.bands(),
                 d.filter_overlap()) ? "error" : NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
