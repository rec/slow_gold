#ifndef __REC_TIME_SCALER
#define __REC_TIME_SCALER

#include "rec/base/base.h"
#include "rec/audio/stretch/description.pb.h"
#include "rec/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

#if 0
struct Description {
  double timeScale_;
  double sampleRate_;
  int channels_;
  double pitchScale_;
  int bands_;
  int filterOverlap_;
  int chunkSize_;

  const char* Init(AudioTimeScaler* s) const {
    return s->Init(timeScale_,
                   sampleRate_,
                   channels_,
                   pitchScale_,
                   bands_,
                   filterOverlap_) ? "error" : NULL;
  }

  static const Description& Default() {
    static const Description dflt = {
      1.0,
      44100.0,
      2,
      1.0,
      MF_PITCHTIME_NBANDS,
      DEFAULT_FILTER_OVERLAP,
      512
    };
    return dflt;
  }
};
#else

inline const char* Init(const Description &desc, AudioTimeScaler* s) {
  return s->Init(desc.time_scale(),
                 desc.sample_rate(),
                 desc.channels(),
                 desc.pitch_scale(),
                 desc.bands(),
                 desc.filter_overlap()) ? "error" : NULL;
}




#endif


}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_TIME_SCALER
