#ifndef __REC_TIME_SCALER
#define __REC_TIME_SCALER

#include "rec/base/base.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace source {

class StretchyProto;

}  // namespace source


namespace stretch {


const char* Init(const source::StretchyProto &desc, AudioTimeScaler* s);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_TIME_SCALER
