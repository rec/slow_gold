#include "rec/slow/app/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {
namespace app {

AudioTransportSourcePlayer::AudioTransportSourcePlayer(AudioDeviceManager* dm)
: Thread("AudioTransportSourcePlayer"), deviceManager_(dm) {
  deviceManager_->addAudioCallback(&player_);
  player_.setSource(this);
}

AudioTransportSourcePlayer::~AudioTransportSourcePlayer() {
  clear();
  deviceManager_->removeAudioCallback(&player_);
  setSource(NULL);
  player_.setSource(NULL);
}

void AudioTransportSourcePlayer::clear() {
  stop();
  setPosition(0);
  setSource(NULL);
}

void AudioTransportSourcePlayer::setPosition(double newPosition) {
  broadcast(newPosition);
  AudioTransportSource::setPosition(newPosition);
}

void AudioTransportSourcePlayer::setStart(bool isStart) {
  if (isStart) {
    startThread();
    AudioTransportSource::start();
  } else {
    signalThreadShouldExit();
    AudioTransportSource::stop();
  }
}

void AudioTransportSourcePlayer::run() {
  while (!threadShouldExit()) {
    float time = getNextReadPosition() / 44100.0f;
    broadcast(time);
    if (!threadShouldExit())
      wait(THREAD_WAIT);
  }
}

}  // namespace app
}  // namespace slow
}  // namespace rec
