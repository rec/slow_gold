#include "rec/audio/source/TimeScaler.h"

#include "rec/audio/source/Stretchy.pb.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace source {

const char* Init(const StretchyProto &desc, AudioTimeScaler* s) {
  return s->Init(desc.time_scale(),
                 desc.sample_rate(),
                 desc.channels(),
                 desc.pitch_scale(),
                 desc.bands(),
                 desc.filter_overlap()) ? "error" : NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
