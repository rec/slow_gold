#ifndef __REC_AUDIO_AUDIODEVICESETUP__
#define __REC_AUDIO_AUDIODEVICESETUP__

#include "rec/base/base.h"
#include "rec/audio/AudioDeviceSetup.pb.h"

namespace rec {
namespace persist {

bool copy(const audio::AudioDeviceSetupProto& in, AudioDeviceSetup *out);
bool copy(const AudioDeviceSetup& in, audio::AudioDeviceSetupProto* out);

}  // namespace persist
}  // namespace rec

#endif  // __REC_AUDIO_AUDIODEVICESETUP__
