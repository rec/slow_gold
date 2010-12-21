#ifndef __REC_PERSIST_AUDIODEVICESETUP__
#define __REC_PERSIST_AUDIODEVICESETUP__

#include "rec/base/base.h"
#include "rec/audio/AudioDeviceSetup.pb.h"

namespace rec {
namespace persist {

bool copy(const audio::AudioDeviceSetupProto& in, AudioDeviceSetup *out);
bool copy(const AudioDeviceSetup& in, audio::AudioDeviceSetupProto* out);
bool copy(AudioDeviceManager& in, AudioDeviceSetup *out);
bool copy(AudioDeviceManager& in, audio::AudioDeviceSetupProto *out);

class AudioDeviceSetupListener : public ChangeListener {
 public:
  AudioDeviceSetupListener(AudioDeviceManager* m);
  virtual ~AudioDeviceSetupListener();
  void changeListenerCallback(ChangeBroadcaster* manager);

 private:
  AudioDeviceManager* manager_;
  DISALLOW_COPY_AND_ASSIGN(AudioDeviceSetupListener);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_AUDIODEVICESETUP__
