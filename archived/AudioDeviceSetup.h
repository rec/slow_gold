#ifndef __REC_PERSIST_AUDIODEVICESETUP__
#define __REC_PERSIST_AUDIODEVICESETUP__

#include "rec/base/base.h"

namespace rec {
namespace persist {

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
