#ifndef __REC_TIME_SCALER
#define __REC_TIME_SCALER

#include "rec/base/base.h"
#include "rec/audio/stretch/TimeStretch.pb.h"
#include "rec/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

inline const char* Init(const TimeStretch &desc, AudioTimeScaler* s) {
  return s->Init(desc.time_scale(),
                 desc.sample_rate(),
                 desc.channels(),
                 desc.pitch_scale(),
                 desc.bands(),
                 desc.filter_overlap()) ? "error" : NULL;
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_TIME_SCALER
