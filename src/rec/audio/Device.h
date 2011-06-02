#ifndef __REC_AUDIO_DEVICE2__
#define __REC_AUDIO_DEVICE2__

#include "rec/gui/audio/SetupPage.h"

namespace rec {
namespace audio {

class Device {
 public:
  Device() : setupPage_(this) { loadState();  }

  AudioDeviceManager manager_;
  gui::audio::SetupPage setupPage_;

  void saveState();

 private:
  void loadState();

  DISALLOW_COPY_AND_ASSIGN(Device);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_DEVICE__
