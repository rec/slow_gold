#ifndef __REC_AUDIO_UTIL_GAIN__
#define __REC_AUDIO_UTIL_GAIN__

#include "rec/base/base.h"
#include "rec/audio/util/Gain.pb.h"

namespace rec {
namespace audio {

double getGain(const audio::Gain&);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_GAIN__
