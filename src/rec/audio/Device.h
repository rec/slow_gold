#ifndef __REC_AUDIO_DEVICE2__
#define __REC_AUDIO_DEVICE2__

#include "rec/gui/audio/SetupPage.h"
#include "rec/audio/util/AudioDeviceSetup.h"

namespace rec {
namespace audio {

class Device {
 public:
  Device() : setupPage_(this), setupListener_(&manager_) { loadState(); }

  AudioDeviceManager manager_;
  gui::audio::SetupPage setupPage_;
  persist::AudioDeviceSetupListener setupListener_;

  void saveState();

 private:
  void loadState();

  DISALLOW_COPY_AND_ASSIGN(Device);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_DEVICE__
