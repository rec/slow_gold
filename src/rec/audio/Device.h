#ifndef __REC_AUDIO_UTIL_DEVICE__
#define __REC_AUDIO_UTIL_DEVICE__

#include "rec/gui/audio/SetupPage.h"
#include "rec/audio/util/AudioDeviceSetup.h"

namespace rec {
namespace audio {

struct Device {
  AudioDeviceManager manager_;
  gui::audio::SetupPage setupPage_;
  persist::AudioDeviceSetupListener setupListener_;

  Device() : setupPage_(manager_), setupListener_(&manager_) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(Device);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_DEVICE__
