#ifndef __REC_AUDIO_DEVICE2__
#define __REC_AUDIO_DEVICE2__

#include "rec/gui/audio/SetupPage.h"

namespace rec {
namespace audio {

class Device {
 public:
  typedef gui::audio::SetupPage SetupPage;

  Device();

  AudioDeviceManager manager_;
  ptr<SetupPage> setupPage_;

  void saveState();

 private:
  void loadState();

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Device);
};

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_DEVICE__
