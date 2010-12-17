#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/base/base.h"

namespace rec {
namespace slow {
namespace app {

class AudioTransportSourcePlayer : public AudioTransportSource {
 public:
  AudioTransportSourcePlayer(AudioDeviceManager* dm) : deviceManager_(dm) {
    deviceManager_->addAudioCallback(&player_);
    player_.setSource(this);
  }

  ~AudioTransportSourcePlayer() {
    deviceManager_->removeAudioCallback(&player_);
    setSource(NULL);
    player_.setSource(NULL);
  }

  void start(bool isStart = true) {
    if (isStart)
      AudioTransportSource::start();
    else
      AudioTransportSource::stop();
  }

  void toggle() { start(!isPlaying()); }

 private:
  AudioSourcePlayer player_;
  AudioDeviceManager* deviceManager_;

  DISALLOW_COPY_AND_ASSIGN(AudioTransportSourcePlayer);
};

}  // namespace app
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
