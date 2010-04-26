#ifndef __REC_TIME_SCALER
#define __REC_TIME_SCALER

#include "rec/base/basictypes.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace timescaler {

struct Description {
  double timeScale;
  double sampleRate;
  int channels;
  double pitchScale;
  int bands;
  int filterOverlap;

  const char* Init(AudioTimeScaler* s) const {
    return s->Init(timeScale,
                   sampleRate,
                   channels,
                   pitchScale,
                   bands,
                   filterOverlap) ? "error" : NULL;
  }

  static const Description& Default() {
    static const Description dflt = {
      1.0,
      44100.0,
      2,
      1.0,
      MF_PITCHTIME_NBANDS,
      DEFAULT_FILTER_OVERLAP
    };
    return dflt;
  }
};

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_TIME_SCALER
