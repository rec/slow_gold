#ifndef __REC_TIME_SCALER
#define __REC_TIME_SCALER

#include "rec/base/base.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace stretch {

class StretchyProto;

const char* Init(const StretchyProto &desc, AudioTimeScaler* s);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_TIME_SCALER
