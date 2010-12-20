#ifndef __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__
#define __REC_SLOW_APP_TRANSPORTSOURCEPLAYER__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace slow {
namespace app {

class AudioTransportSourcePlayer
  : public AudioTransportSource,
    public Thread,
    public listener::Broadcaster<float> {
 public:
  static const int THREAD_WAIT = 40;

  AudioTransportSourcePlayer(AudioDeviceManager* dm) 
      : Thread("AudioTransportSourcePlayer"), deviceManager_(dm) {
    deviceManager_->addAudioCallback(&player_);
    player_.setSource(this);
  }

  ~AudioTransportSourcePlayer() {
    deviceManager_->removeAudioCallback(&player_);
    setSource(NULL);
    player_.setSource(NULL);
  }

  virtual void changeCallback(ChangeBroadcaster* thing) {}

  void start(bool isStart = true) {
    if (isStart) {
      startThread();
      AudioTransportSource::start();
    } else {
      signalThreadShouldExit();
      AudioTransportSource::stop();
    }
  }

  virtual void run() {
    while (!threadShouldExit()) {
      broadcast(getNextReadPosition() / 44100.0f);
      if (!threadShouldExit())
        wait(THREAD_WAIT);
    }
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
